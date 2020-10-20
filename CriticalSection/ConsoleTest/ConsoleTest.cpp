#include <iostream>
#include "CriticalSectionDll.h"

MY_LPCRITICAL_SECTION criticalSection = new _MY_CRITICAL_SECTION();

DWORD WINAPI ThreadProc1(LPVOID lpParam) {
    EnterMyCriticalSection(criticalSection);
    std::cout << 1 << std::endl;
    std::cout << 2 << std::endl;
    std::cout << 3 << std::endl;
    //Sleep(1000);
    std::cout << 4 << std::endl;
    std::cout << 5 << std::endl;
    std::cout << 6 << std::endl;
    LeaveMyCriticalSection(criticalSection);
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam) {
    EnterMyCriticalSection(criticalSection);
    std::cout << 7 << std::endl;
    std::cout << 8 << std::endl;
    std::cout << 9 << std::endl;
    //Sleep(1000);
    std::cout << 10 << std::endl;
    std::cout << 11 << std::endl;
    std::cout << 12 << std::endl;
    LeaveMyCriticalSection(criticalSection);
    return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParam) {
    EnterMyCriticalSection(criticalSection);
    std::cout << 13 << std::endl;
    std::cout << 14 << std::endl;
    std::cout << 15 << std::endl;
    //Sleep(1000);
    std::cout << 16 << std::endl;
    std::cout << 17 << std::endl;
    std::cout << 18 << std::endl;
    LeaveMyCriticalSection(criticalSection);
    return 0;
}

int main() {

    InitializeMyCriticalSectionAndSpinCount(criticalSection, 500000);
    CreateThread(NULL, 0, &ThreadProc1, NULL, 0, NULL);
    CreateThread(NULL, 0, &ThreadProc2, NULL, 0, NULL);
    CreateThread(NULL, 0, &ThreadProc3, NULL, 0, NULL);
    getchar();
}