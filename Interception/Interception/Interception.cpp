#include <iostream>
#include <windows.h>

STARTUPINFO psi;
PROCESS_INFORMATION pi;

int main()
{
    std::wstring path = L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\Interception\\x64\\Debug\\InterceptionConsole.exe";
    std::wstring dll = L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\Interception\\x64\\Debug\\InterceptionDll.dll";

    CreateProcess(path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &psi, &pi);

    void* loadLibraryW = GetProcAddress(GetModuleHandle(L"Kernel32"), "LoadLibraryW");
    LPVOID hMem = VirtualAllocEx(pi.hProcess, NULL, dll.size() * sizeof(wchar_t) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(pi.hProcess, hMem, dll.c_str(), dll.size() * sizeof(wchar_t) + 1, NULL);

    HANDLE hRemoteThread = CreateRemoteThread(pi.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryW, hMem, NULL, NULL);
    WaitForSingleObject(hRemoteThread, INFINITE);
    CloseHandle(hRemoteThread);

    ResumeThread(pi.hThread);
    WaitForSingleObject(pi.hProcess, INFINITE);

    VirtualFreeEx(pi.hProcess, hMem, 0, MEM_RELEASE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
