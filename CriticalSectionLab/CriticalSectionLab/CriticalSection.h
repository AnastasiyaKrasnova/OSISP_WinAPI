#pragma once
#include <Windows.h>
typedef struct _MY_CRITICAL_SECTION {
    
    LONG LockCount = 0;
    LONG RecursionCount=1;
    HANDLE OwningThread=NULL;   
    HANDLE OwningProcess=NULL;
    HANDLE LockMutex;
    LONG SpinCount=100;
    BOOL isInitialized=FALSE;
    SHORT slock = 0;

} MY_CRITICAL_SECTION, *MY_LPCRITICAL_SECTION;

BOOL InitializeMyCriticalSectionAndSpinCount(
    MY_LPCRITICAL_SECTION lpCriticalSection,
    DWORD              dwSpinCount
);

void EnterMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);

void LeaveMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);

void DeleteMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);