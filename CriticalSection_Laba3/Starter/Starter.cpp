#include <iostream>
#include <Windows.h>


using namespace std;
int main()
{
    CRITICAL_SECTION critical_section;
    TCHAR szName[] = TEXT("MySharedMemory");
    HANDLE hFileMapping;
    LPCTSTR buf;

    InitializeCriticalSectionAndSpinCount(&critical_section, 50000);
    
    hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(CRITICAL_SECTION), szName);

    if (hFileMapping == NULL)
    {
        cout << "Couldn't create FileMapping Object"<<endl;
        return 1;
    }

    buf = (LPTSTR)MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CRITICAL_SECTION));

    if (buf == NULL)
    {
        cout << "Couldn't map view of file" << endl;
        CloseHandle(hFileMapping);
        return 1;
    }

    CopyMemory((PVOID)buf, &critical_section, sizeof(CRITICAL_SECTION));

    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;

    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;

    STARTUPINFO si3;
    PROCESS_INFORMATION pi3;


    wstring Process1(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection_Laba3\\Debug\\Process1.exe");
    wstring Process2(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection_Laba3\\Debug\\Process2.exe");
    wstring Process3(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection_Laba3\\Debug\\Process3.exe");


    LPWSTR path1 = &Process1[0];
    LPWSTR path2 = &Process2[0];
    LPWSTR path3 = &Process3[0];

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    ZeroMemory(&si3, sizeof(si3));
    si3.cb = sizeof(si3);
    ZeroMemory(&pi3, sizeof(pi3));


    if (!CreateProcess(NULL, path1, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
    {
        cout << "Couldn't create process 1" << endl;
        return 1;
    }

    if (!CreateProcess(NULL, path2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
    {
        cout << "Couldn't create process 2" << endl;
        return 1;
    }

    if (!CreateProcess(NULL, path3, NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3))
    {
        cout << "Couldn't create process 3" << endl;
        return 1;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    WaitForSingleObject(pi3.hProcess, INFINITE);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);
    CloseHandle(pi3.hProcess);
    CloseHandle(pi3.hThread);


    UnmapViewOfFile(&critical_section);
    CloseHandle(hFileMapping);
    getchar();
    return 0;
}
