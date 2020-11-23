#pragma once
#include "framework.h"

#define MAX_LOADSTRING 100

const wchar_t* headers[] = {
        { L"Telephone" },
        { L"First name" },
        { L"Last name" },
        { L"Father name" },
        { L"Street" },
        { L"House" },
        { L"Flat" }
};

typedef struct TMainWindow {
    HWND hWnd;
    HWND hListView;
    HWND hTel;
    HWND hFn;
    HWND hMn;
    HWND hLn;
    HWND hHs;
    HWND hFlt;
    HWND hStr;
    HWND hSearch;

}TMainWindow, * PMainWindow;


HINSTANCE hInst;
HINSTANCE hDLL;
PMainWindow pSelf;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HWND, int);
void UpdateListView(HWND, std::vector<PhonebookRecord*>);
std::wstring GetText(HWND);
void InitDll(HWND);


IPhoneBook* phoneBookLoader;
std::vector<PhonebookRecord*> phoneBook;


