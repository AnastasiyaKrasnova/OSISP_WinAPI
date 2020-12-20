#include <iostream>
#include <windows.h>

#define REG_PATH L"Software\\TestApplication"

int main()
{
    HANDLE hFile = CreateFile(L"C:\\Users\\home\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    std::string data = "Test dll interception for file crearing, writing, reading and deleting";
    WriteFile(hFile, data.c_str(), data.size(), NULL, NULL);
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

    char buf[100];
    DWORD bufSize = sizeof(buf);
    ZeroMemory(&buf, sizeof(buf));
    ReadFile(hFile, buf, data.size(), NULL, NULL);

    DeleteFile(L"C:\\Users\\home\\Desktop\\test.txt");

    CloseHandle(hFile);

    

    HKEY result;
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Python", &result);
    RegCloseKey(result);

    HKEY createResult;
    RegCreateKey(HKEY_CURRENT_USER, REG_PATH, &createResult);
    LPCWSTR lpData = L"test-data";
    RegSetValue(HKEY_CURRENT_USER, REG_PATH, REG_SZ, lpData, sizeof(wchar_t) * (wcslen(lpData) + 1));

    ZeroMemory(&buf, sizeof(buf));
    RegGetValue(HKEY_CURRENT_USER, REG_PATH, NULL, RRF_RT_ANY, NULL, buf, &bufSize);
    RegCloseKey(createResult);
    RegDeleteKey(HKEY_CURRENT_USER, REG_PATH);

    std::cout << "test application marker\n";
}