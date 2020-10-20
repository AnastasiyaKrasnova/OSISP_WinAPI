#include <tchar.h>
#include <iostream>
#include "CriticalSectionDll.h"



void _tmain(int argc, TCHAR* argv[])
{
    MY_CRITICAL_SECTION critical_section;
    InitializeMyCriticalSectionAndSpinCount(&critical_section, 500000);
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

    /*STARTUPINFO si;
    PROCESS_INFORMATION pi;


    std::wstring CommandLineFirst(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\TestFileMapping\\Debug\\Process1.exe");


    LPWSTR lpwCmdLineFirst = &CommandLineFirst[0];

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));


    if (!CreateProcess(NULL, lpwCmdLineFirst, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }



    WaitForSingleObject(pi.hProcess, INFINITE);


    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


    UnmapViewOfFile(&critical_section);
    CloseHandle(hMapFile);*/
    getchar();
}