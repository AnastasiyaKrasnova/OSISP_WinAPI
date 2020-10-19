#include "CriticalSection.h"


BOOL lockSpinlock(MY_LPCRITICAL_SECTION lpCriticalSection) {
    DWORD spinCount = 0;
    SHORT sl=1;
    while (spinCount < lpCriticalSection->SpinCount) {
        if (lpCriticalSection->slock==0) {
            sl = InterlockedExchange16(&lpCriticalSection->slock,sl);
            if (sl == 0) {
                lpCriticalSection->OwningThread = GetCurrentThread();
                lpCriticalSection->OwningProcess = GetCurrentProcess();
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
    if (OpenThread(STANDARD_RIGHTS_ALL, FALSE, GetCurrentThreadId()) == lpCriticalSection->OwningThread && GetCurrentProcess() == lpCriticalSection->OwningProcess) {
        return;
    }
    lockSpinlock(lpCriticalSection);
    WaitForSingleObject(lpCriticalSection->LockMutex, INFINITE);
    return;
}

void LeaveMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {
    if (!ReleaseMutex(lpCriticalSection->LockMutex)) {
        unlockSpinlock(lpCriticalSection);
    }
    lpCriticalSection->OwningThread = NULL;
    lpCriticalSection->OwningProcess = NULL;

}

void DeleteMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
) {

}