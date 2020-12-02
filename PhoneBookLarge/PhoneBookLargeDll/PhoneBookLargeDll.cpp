#include "pch.h"
#include "framework.h"
#include "PhoneBookLargeDll.h"



PHONEBOOKLARGEDLL_API IPhoneBook* _cdecl CreatePhoneBookObject() {
    return new PhoneBook();
}

void PhoneBook::InitPhoneBook() {
    GetSystemInfo(&sysinfo);
    GetCurrentDirectory(sizeof(currentDirectory), currentDirectory);
    dbFile = CreateFile(((std::wstring)currentDirectory + L"\\phonebook.db").c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    fileSize = GetFileSize(dbFile, NULL);
    hMapObject = CreateFileMapping(dbFile, NULL, PAGE_READONLY, 0, 0, L"PhonebookLarge");
    hFilePointer = SetFilePointer(hMapObject, NULL, 0);
    offset = 0;
}

void PhoneBook::DestroyPhoneBook() {
    UnmapViewOfFile(hFilePointer);
    CloseHandle(dbFile);
    CloseHandle(hMapObject);
}


std::vector<PhonebookRecord*> PhoneBook::GetPhoneBook()
{
    std::vector<PhonebookRecord*> result;
    std::wstring line;

    offset = 0;
    offsetStack.clear();
    offsetStack.push_back(offset);

    for (int i = 0; i < 20; i++) {
            line.clear();
            line = ReadLine(&offset);
            PhonebookRecord* temp = ParseLine(line);
            result.push_back(temp);
    }

    return result;
}


std::vector<PhonebookRecord*> PhoneBook::Search(PhonebookRecord searchParam)
{
    offset = 0;
    offsetStack.clear();
    return SearchFrom(searchParam);
}

std::vector<PhonebookRecord*> PhoneBook::SearchFrom(PhonebookRecord searchParam)
{
    std::vector<PhonebookRecord*> result;
    std::wstring line;

    if (offset < fileSize)
        offsetStack.push_back(offset);

    while (offset < fileSize) {
        line.clear();
        line = ReadLine(&offset);
        PhonebookRecord* temp = ParseLine(line);

        if (!((std::wstring)searchParam.telephone).empty() && (std::wstring)temp->telephone != (std::wstring)searchParam.telephone ||
            !((std::wstring)searchParam.firstName).empty() && (std::wstring)temp->firstName != (std::wstring)searchParam.firstName ||
            !((std::wstring)searchParam.lastName).empty() && (std::wstring)temp->lastName != (std::wstring)searchParam.lastName ||
            !((std::wstring)searchParam.fatherName).empty() && (std::wstring)temp->fatherName != (std::wstring)searchParam.fatherName ||
            !((std::wstring)searchParam.street).empty() && (std::wstring)temp->street != (std::wstring)searchParam.street ||
            !((std::wstring)searchParam.house).empty() && (std::wstring)temp->house != (std::wstring)searchParam.house ||
            !((std::wstring)searchParam.flat).empty() && (std::wstring)temp->flat != (std::wstring)searchParam.flat) continue;

        result.push_back(temp);
        if (result.size() == 20) break;
    }

    return result;
}

void PhoneBook::PrevPage() {
    if (offsetStack.size() == 0)
        offset = 0;
    else if (offsetStack.size() == 1) {
        offsetStack.pop_back();
        offset = 0;
    }
    else {
        offsetStack.pop_back();
        offset = offsetStack.back();
        offsetStack.pop_back();
    }
}

HANDLE PhoneBook::SetFilePointer(HANDLE hMap, HANDLE prevFilePointer, DWORD offset)
{
    HANDLE result;
    if (prevFilePointer != NULL)
        UnmapViewOfFile(prevFilePointer);

    result = MapViewOfFile(hMap, FILE_MAP_READ, 0, offset, sysinfo.dwAllocationGranularity);
    if (result == NULL)
        result = MapViewOfFile(hMap, FILE_MAP_READ, 0, offset, 0);
    return result;
}

BYTE PhoneBook::ReadByte(DWORD offset) {
    if (offset % 65536 == 0)
        hFilePointer = SetFilePointer(hMapObject, hFilePointer, offset);
    return *(BYTE*)((DWORD)hFilePointer + (offset % 65536));
}

wchar_t PhoneBook::ReadEncoding(DWORD* offset)
{
    short first = ReadByte(*offset);

    *offset += 1;
    if ((first >> 6) == 3) {
        short second = ReadByte(*offset);
        *offset += 1;
        if ((second >> 6) == 2) {
            return ((first & 0x003F) << 6) + (second & 0x003F);
        }
    }
    return first;
}

std::wstring PhoneBook::ReadLine(DWORD* offset)
{
    wchar_t symbol;
    std::wstring result = L"";

    do {
        symbol = ReadEncoding(offset);
        result += symbol;
    } while (symbol != L'\n');

    return result;
}

PhonebookRecord* PhoneBook::ParseLine(std::wstring line)
{
    PhonebookRecord* item = new PhonebookRecord();
    ZeroMemory(item, sizeof(PhonebookRecord));
    std::vector<std::wstring> tokens;

    int pos = 0;
    std::wstring token;
    while ((pos = line.find(L";")) != std::string::npos) {
        token = line.substr(0, pos);
        if (token != L"")
            tokens.push_back(token);
        else
            tokens.push_back(NULL);
        line.erase(0, pos + 1);
    }

    std::copy(std::begin(tokens[0]), std::end(tokens[0]), std::begin(item->telephone));
    std::copy(std::begin(tokens[1]), std::end(tokens[1]), std::begin(item->lastName));
    std::copy(std::begin(tokens[2]), std::end(tokens[2]), std::begin(item->firstName));
    std::copy(std::begin(tokens[3]), std::end(tokens[3]), std::begin(item->fatherName));
    std::copy(std::begin(tokens[4]), std::end(tokens[4]), std::begin(item->street));
    std::copy(std::begin(tokens[5]), std::end(tokens[5]), std::begin(item->house));
    std::copy(std::begin(tokens[6]), std::end(tokens[6]), std::begin(item->flat));

    return item;
}