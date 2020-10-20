#include <tchar.h>
#include <iostream>
#include "CriticalSectionDll.h"



void _tmain(int argc, TCHAR* argv[])
{
    MY_CRITICAL_SECTION critical_section;
    InitializeMyCriticalSectionAndSpinCount(&critical_section, 500000000000000);
    TCHAR szName[] = TEXT("MyFileMappingObject");
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MY_CRITICAL_SECTION), szName);

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MY_CRITICAL_SECTION));

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return;
    }

    SIZE_T datasize = sizeof(MY_CRITICAL_SECTION);

    CopyMemory((PVOID)pBuf, &critical_section, datasize);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;

    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;


    std::wstring Process1(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection\\Debug\\Process1.exe");
    std::wstring Process2(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection\\Debug\\Process2.exe");
    //std::wstring Process3(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\CriticalSection\\Debug\\Process3.exe");


    LPWSTR path1 = &Process1[0];
    LPWSTR path2 = &Process2[0];
   // LPWSTR path3 = &Process3[0];

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));


    if (!CreateProcess(NULL, path1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    if (!CreateProcess(NULL, path2, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    /*if (!CreateProcess(NULL, path3, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }*/

    WaitForSingleObject(pi.hProcess, INFINITE);
    WaitForSingleObject(pi1.hProcess, INFINITE);
    //WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    //CloseHandle(pi2.hProcess);
    //CloseHandle(pi2.hThread);


    UnmapViewOfFile(&critical_section);
    CloseHandle(hMapFile);
    getchar();
}