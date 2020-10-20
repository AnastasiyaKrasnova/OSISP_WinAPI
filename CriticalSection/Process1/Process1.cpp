#include <tchar.h>
#include <iostream>
#include "CriticalSectionDll.h"

TCHAR szName[] = TEXT("MyFileMappingObject");

int _tmain()
{
    HANDLE hMapFile;
    MY_LPCRITICAL_SECTION critical_section;

    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }

    critical_section = (MY_LPCRITICAL_SECTION)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MY_CRITICAL_SECTION));

    if (critical_section == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }

    EnterMyCriticalSection(critical_section);
    std::cout << 1 << std::endl;
    std::cout << 2 << std::endl;
    std::cout << 3 << std::endl;
    std::cout << 4 << std::endl;
    std::cout << 5 << std::endl;
    std::cout << 6 << std::endl;
    LeaveMyCriticalSection(critical_section);

    UnmapViewOfFile(critical_section);

    CloseHandle(hMapFile);
    getchar();

    return 0;
}