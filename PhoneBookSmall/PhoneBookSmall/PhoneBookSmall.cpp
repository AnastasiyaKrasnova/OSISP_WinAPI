#include "framework.h"

const wchar_t* headers[] = {
        { L"Telephone" },
        { L"First name" },
        { L"Last name" },
        { L"Middle name" },
        { L"Street" },
        { L"House" },
        { L"Flat" }
};


#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];          

ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HWND, int);
void UpdateList(HWND);

typedef struct TMainWindow {
    HWND hWnd;
    HWND hListView;
    HWND hTel;
    HWND hFn;
    HWND hMn;
    HWND hLn;
    HWND hHs;
    HWND hHsng;
    HWND hFlt;
    HWND hStr;
    HWND hSearch;

}TMainWindow, * PMainWindow;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PHONEBOOKSMALL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    /*INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof icc;
    icc.dwICC = ICC_COOL_CLASSES | ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icc);*/

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHONEBOOKSMALL));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHONEBOOKSMALL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PHONEBOOKSMALL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {
        PMainWindow pSelf;
        pSelf = (PMainWindow)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TMainWindow));
        if (pSelf != NULL) {
            pSelf->hWnd = hWnd;
            pSelf->hListView = CreateListView(hWnd, 7);
            pSelf->hTel = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                3, 3, 95, 20, hWnd, IDC_TELEDIT, hInst, NULL);
            pSelf->hFn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                103, 3, 95, 20, hWnd, IDC_FNEDIT, hInst, NULL);
            pSelf->hMn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                203, 3, 95, 20, hWnd, IDC_MNEDIT, hInst, NULL);
            pSelf->hLn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                303, 3, 95, 20, hWnd, IDC_LNEDIT, hInst, NULL);
            pSelf->hStr = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                403, 3, 95, 20, hWnd, IDC_FLTEDIT, hInst, NULL);
            pSelf->hHs = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
                503, 3, 95, 20, hWnd, IDC_HSEDIT, hInst, NULL);
            pSelf->hHsng = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
                603, 3, 95, 20, hWnd, IDC_HSNGEDIT, hInst, NULL);
            pSelf->hFlt = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
                703, 3, 75, 20, hWnd, IDC_FLTEDIT, hInst, NULL);
            pSelf->hSearch = CreateWindow(WC_BUTTON, TEXT("Search"), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | BS_CENTER,
                3, 25, 774, 23, hWnd, IDC_SEARCHBTN, hInst, NULL);
            UpdateList(pSelf->hListView);
            break;
        }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
        return 0;
    }
}

HWND CreateListView(HWND parent, int columns) {

    RECT rcClient;
    GetClientRect(parent, &rcClient);

    HWND hWndListView = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS | WS_EX_CLIENTEDGE, 0, rcClient.top + 50,
        rcClient.right - rcClient.left, rcClient.bottom - rcClient.top - 50, parent, IDC_LISTVIEW, hInst, NULL);

    LVCOLUMN c = { 0 };
    c.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    for (int i = 0; i < columns; i++) {
        c.fmt = LVCFMT_LEFT;
        c.pszText = (LPWSTR)headers[i];
        c.iSubItem = i;
        c.cx = 100;
        ListView_InsertColumn(hWndListView, i, &c);
    }
    return hWndListView;
}

void UpdateList(HWND hListView) {
    ListView_DeleteAllItems(hListView);
    LVITEM item;
    ZeroMemory(&item, sizeof(LVITEM));
    item.mask = LVIF_TEXT | LVIF_STATE;
        ListView_InsertItem(hListView, &item);
        ListView_SetItemText(hListView, 0, 0, (LPWSTR)L"HUI");
        ListView_SetItemText(hListView, 0, 1, (LPWSTR)L"HUI");
        ListView_SetItemText(hListView, 0, 2, (LPWSTR)L"ZALOOPA");
        ListView_SetItemText(hListView, 0, 3, (LPWSTR)L"HER");
        ListView_SetItemText(hListView, 0, 4, (LPWSTR)L"SUKA");
        ListView_SetItemText(hListView, 0, 5, (LPWSTR)L"lol");
        ListView_SetItemText(hListView, 0, 6, (LPWSTR)L"kek");
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
