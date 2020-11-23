#include <iostream>
#include <cstring>
#include <Windows.h>
#include "C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\PhoneBookSmall\\PhoneBookSmallDLL\\PhoneBookSmallDLL.h"

int main()
{
    HINSTANCE hDLL = LoadLibrary(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\PhoneBookSmall\\Debug\\PhoneBookSmallDLL.dll");

    if (hDLL == NULL) {
        std::cout << GetLastError();
    }
    else {
        PHONE_BOOK pEntryFunction = (PHONE_BOOK)GetProcAddress(hDLL, "CreatePhoneBookObject");
        IPhoneBook* phoneBook = pEntryFunction();
        if (phoneBook) {
            phoneBook->InitPhoneBook();
            PhonebookRecord rc;
            wcsncpy_s(rc.telephone, L"+375447290007",20);
            wcsncpy_s(rc.lastName, L"", 20);
            wcsncpy_s(rc.firstName, L"", 20);
            wcsncpy_s(rc.fatherName, L"", 20);
            wcsncpy_s(rc.street, L"", 20);
            wcsncpy_s(rc.house, L"", 5);
            wcsncpy_s(rc.flat, L"", 5);
            std::vector<PhonebookRecord*> smallPhoneBook = phoneBook->GetPhonebook();
            std::wcout <<smallPhoneBook[1]->lastName << std::endl;
            std::vector<PhonebookRecord*> res = phoneBook->Search(rc);
            std::wcout << res[0]->firstName << std::endl;

        }
        FreeLibrary(hDLL);
    }
    std::cin.get();
    return 0;
}

