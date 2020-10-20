#include "pch.h"
#include "framework.h"
#include "CriticalSectionDll.h"
#include <iostream>


BOOL lockSpinlock(MY_LPCRITICAL_SECTION lpCriticalSection) {
    DWORD spinCount = 0;
    SHORT sl = 1;
    while (spinCount < lpCriticalSection->SpinCount) {
    //while (true) {
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
        lpCriticalSection->isInitialized = true;
        lpCriticalSection->SpinCount = dwSpinCount;
        lpCriticalSection->LockMutex = CreateMutex(NULL, FALSE, TEXT("MyCoolMutex"));
        return true;
    }
    return false;
}

void EnterMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {
   // std::cout << "Nachinayu shturm\n";
    bool f = lockSpinlock(lpCriticalSection);
    OpenMutex(
        MUTEX_ALL_ACCESS,            // request full access
        FALSE,                       // handle not inheritable
        TEXT("MyCoolMutex"));  // object name
    //WaitForSingleObject(lpCriticalSection->LockMutex, INFINITE);
    /*if (f) {
        std::cout << "SpinLock Uhvachen\n";
    }
    else {
        std::cout << "Hui Uhvachen\n";
    }*/
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
    //std::cout << "Section left\n";
    ReleaseMutex(lpCriticalSection->LockMutex);
    //SetEvent(lpCriticalSection->LockMutex);
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


