#include "pch.h"
#include "framework.h"
#include "PhoneBookSmallDLL.h"

TCHAR currentDirectory[1024];


PHONEBOOKSMALLDLL_API IPhoneBook* _cdecl CreatePhoneBookObject() {
    return new PhoneBook();
}

Indexer<wchar_t[20]>* telephoneIndex, * lastNameIndex, * firstNameIndex, * fatherNameIndex, * streetIndex;
Indexer<wchar_t[5]>* houseIndex, * flatIndex;

void PhoneBook::InitPhoneBook() {
    GetCurrentDirectory(sizeof(currentDirectory), currentDirectory);
	smallPhoneBook = ReadFromDBFile((std::wstring)currentDirectory + L"\\phonebook.db");
	CreateIndex(smallPhoneBook);
}

std::vector<PhonebookRecord*> PhoneBook::GetPhonebook()
{
    return smallPhoneBook;
}



void PhoneBook::CreateIndex(std::vector<PhonebookRecord*> phoneBook)
{
    telephoneIndex = new Indexer<wchar_t[20]>(phoneBook, offsetof(PhonebookRecord, telephone));
    lastNameIndex = new Indexer<wchar_t[20]>(phoneBook, offsetof(PhonebookRecord, lastName));
    firstNameIndex = new Indexer<wchar_t[20]>(phoneBook, offsetof(PhonebookRecord, firstName));
    fatherNameIndex = new Indexer<wchar_t[20]>(phoneBook, offsetof(PhonebookRecord, fatherName));
    streetIndex = new Indexer<wchar_t[20]>(phoneBook, offsetof(PhonebookRecord, street));
    houseIndex = new Indexer<wchar_t[5]>(phoneBook, offsetof(PhonebookRecord, house));
    flatIndex = new Indexer<wchar_t[5]>(phoneBook, offsetof(PhonebookRecord, flat));
}

std::vector<PhonebookRecord*> PhoneBook::Search(PhonebookRecord searchParam)
{
    bool isEmpty = true;
    std::vector<PhonebookRecord*> result;

    if (!((std::wstring)searchParam.telephone).empty()) {
        result = IntersectResult(result, telephoneIndex->Search(telephoneIndex->root, searchParam.telephone));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.lastName).empty()) {
        result = IntersectResult(result, lastNameIndex->Search(lastNameIndex->root, searchParam.lastName));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.firstName).empty()) {
        result = IntersectResult(result, firstNameIndex->Search(firstNameIndex->root, searchParam.firstName));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.fatherName).empty()) {
        result = IntersectResult(result, fatherNameIndex->Search(fatherNameIndex->root, searchParam.fatherName));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.street).empty()) {
        result = IntersectResult(result, streetIndex->Search(streetIndex->root, searchParam.street));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.house).empty()) {
        result = IntersectResult(result, houseIndex->Search(houseIndex->root, searchParam.house));
        isEmpty = false;
    }
    if (!((std::wstring)searchParam.flat).empty()) {
        result = IntersectResult(result, flatIndex->Search(flatIndex->root, searchParam.flat));
        isEmpty = false;
    }

    if (!isEmpty)
        return result;
    else
        return smallPhoneBook;
}

std::vector<PhonebookRecord*> PhoneBook::IntersectResult(std::vector<PhonebookRecord*> first, std::vector<PhonebookRecord*> second)
{
    std::vector<PhonebookRecord*> result;

    if (!first.empty()) {
        std::sort(first.begin(), first.end());
        std::sort(second.begin(), second.end());

        std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), back_inserter(result));
    }
    else
        result = second;

    return result;
}

std::vector<PhonebookRecord*> PhoneBook::ReadFromDBFile(std::wstring filePath)
{
    std::vector<PhonebookRecord*> result;
    std::wstring line;
    std::wifstream file(filePath);
    if (file.is_open()) {
        while (getline(file, line)) {
            result.push_back(ParseLine(line));
        }
    }

    file.close();
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

template <typename T>
TreeNode* Indexer<T>::Insert(TreeNode* ptr, PhonebookRecord* value)
{
    if (ptr == nullptr) {
        ptr = new TreeNode(value, nullptr);
    }
    else {
        std::wstring first = ToString(*(T*)((int)value + offset));
        std::wstring second = ToString(*(T*)((int)ptr->data[0] + offset));

        if (first < second)
            ptr->left = Insert(ptr->left, value);
        else if (first > second)
            ptr->right = Insert(ptr->right, value);
        else
            ptr->data.push_back(value);
    }
    return ptr;
}

template <typename T>
Indexer<T>::Indexer(std::vector<PhonebookRecord*> phoneBook, int offset)
{
    this->offset = offset;
    for (int i = 0; i < phoneBook.size(); i++) {
        root = Insert(root, phoneBook[i]);
    }
}

template <typename T>
std::wstring Indexer<T>::ToString(T value)
{
    std::wstring wss(value);
    return wss;
}

template <typename T>
std::vector<PhonebookRecord*> Indexer<T>::Search(TreeNode* ptr, T value)
{
    if (ptr != nullptr) {
        std::wstring first = ToString(value);
        std::wstring second = ToString(*(T*)((int)ptr->data[0] + offset));

        if (first == second)
            return ptr->data;
        else if (first < second)
            return Search(ptr->left, value);
        else
            return Search(ptr->right, value);
    }

    return {};
}

