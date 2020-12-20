#include <iostream>
#include <windows.h>


int main()
{
    HANDLE hFile = CreateFile(L"C:\\Users\\home\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    std::string text = "Test dll interception for file crearing, writing, reading and deleting";
    WriteFile(hFile, text.c_str(), text.size(), NULL, NULL);
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

    char buffer[100];
    DWORD size = sizeof(buffer);
    ZeroMemory(&buffer, sizeof(buffer));
    ReadFile(hFile, buffer, text.size(), NULL, NULL);
    DeleteFile(L"C:\\Users\\home\\Desktop\\test.txt");
    CloseHandle(hFile);

    HKEY reg;
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Silk", &reg);
    RegCloseKey(reg);

    RegCreateKey(HKEY_CURRENT_USER, L"Software\\InterceptionCheck", &reg);
    LPCWSTR reg_text = L"interception check";
    RegSetValue(HKEY_CURRENT_USER, L"Software\\InterceptionCheck", REG_SZ, reg_text, sizeof(wchar_t) * (wcslen(reg_text) + 1));

    ZeroMemory(&buffer, sizeof(buffer));
    RegGetValue(HKEY_CURRENT_USER, L"Software\\InterceptionCheck", NULL, RRF_RT_ANY, NULL, buffer, &size);
    RegCloseKey(reg);
    RegDeleteKey(HKEY_CURRENT_USER, L"Software\\InterceptionCheck");

}