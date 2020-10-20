#include "pch.h"
#include "framework.h"
#include "CriticalSectionDll.h"
#include <iostream>


BOOL lockSpinlock(MY_LPCRITICAL_SECTION lpCriticalSection) {
    DWORD spinCount = 0;
    SHORT sl = 1;
    while (spinCount < lpCriticalSection->SpinCount) {
        if (lpCriticalSection->slock == 0) {
            sl = InterlockedExchange16(&lpCriticalSection->slock, sl);
            if (sl == 0) {
                lpCriticalSection->OwningThreadId = GetCurrentThreadId();
                lpCriticalSection->OwningProcessId = GetCurrentProcessId();
                return TRUE;
            }
        }
        spinCount++;
    }
    return FALSE;
}

void unlockSpinlock(MY_LPCRITICAL_SECTION lpCriticalSection) {
    SHORT sl = 0;
    InterlockedExchange16(&lpCriticalSection->slock, sl);

}


BOOL InitializeMyCriticalSectionAndSpinCount(
    MY_LPCRITICAL_SECTION lpCriticalSection,
    DWORD              dwSpinCount
) {
    if (!lpCriticalSection->isInitialized) {
        lpCriticalSection->isInitialized = false;
        lpCriticalSection->SpinCount = dwSpinCount;
        lpCriticalSection->LockMutex = CreateMutex(NULL, FALSE, TEXT("MyMutex"));
        return true;
    }
    return false;
}

void EnterMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {
    if (GetCurrentThreadId() == lpCriticalSection->OwningThreadId && GetCurrentProcessId() == lpCriticalSection->OwningProcessId) {
        return;
    }
    std::cout << "Nachinayu shturm\n";
    bool f = lockSpinlock(lpCriticalSection);
    WaitForSingleObject(lpCriticalSection->LockMutex, INFINITE);
    if (f) {
        std::cout << "SpinLock Uhvachen\n";
    }
    else {
        std::cout << "Mutex Uhvachen\n";
    }
    /*if (lpCriticalSection->OwningThreadId == GetCurrentThreadId())
    {
        InterlockedIncrement(&lpCriticalSection->RecursionCount);
        return;
    }
    if (InterlockedIncrement(&lpCriticalSection->LockCount) == 1)
        InterlockedExchange(&lpCriticalSection->RecursionCount, 0);
    else
        WaitForSingleObject(lpCriticalSection->LockMutex, INFINITE);

    lpCriticalSection->OwningThreadId = GetCurrentThreadId();*/
    return;
}

void LeaveMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {
    std::cout << "Section left\n";
    ReleaseMutex(lpCriticalSection->LockMutex);
    unlockSpinlock(lpCriticalSection);
    lpCriticalSection->OwningThreadId = 0;
    lpCriticalSection->OwningProcessId = 0;

    /*if (lpCriticalSection->OwningThreadId != GetCurrentThreadId())
        return;

    if (lpCriticalSection->RecursionCount == 0)
    {
        if (InterlockedDecrement(&lpCriticalSection->LockCount) > 0)
        {
            ReleaseMutex(lpCriticalSection->LockMutex);
        }
    }
    else
    {
        InterlockedDecrement(&lpCriticalSection->RecursionCount);
    }*/

}

void DeleteMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {

}


