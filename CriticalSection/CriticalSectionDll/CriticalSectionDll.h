#pragma once
#ifdef CRITICALSECTIONDLL_EXPORTS
#define CRITICALSECTIONDLL_API __declspec(dllexport)
#else
#define CRITICALSECTIONDLL_API __declspec(dllimport)
#endif

#include <Windows.h>
extern "C" CRITICALSECTIONDLL_API typedef struct _MY_CRITICAL_SECTION {

    LONG LockCount = 0;
    LONG RecursionCount = 0;
    DWORD OwningThreadId;
    DWORD OwningProcessId;
    HANDLE LockMutex;
    LONG SpinCount = 100;
    BOOL isInitialized = FALSE;
    SHORT slock = 0;

} MY_CRITICAL_SECTION, * MY_LPCRITICAL_SECTION;

extern "C" CRITICALSECTIONDLL_API BOOL InitializeMyCriticalSectionAndSpinCount(
    MY_LPCRITICAL_SECTION lpCriticalSection,
    DWORD              dwSpinCount
);

extern "C" CRITICALSECTIONDLL_API void EnterMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);

extern "C" CRITICALSECTIONDLL_API void LeaveMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);

extern "C" CRITICALSECTIONDLL_API void DeleteMyCriticalSection(
    MY_LPCRITICAL_SECTION lpCriticalSection
);