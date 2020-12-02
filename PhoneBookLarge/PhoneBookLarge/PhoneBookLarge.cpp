#include "PhoneBookLarge.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PHONEBOOKLARGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHONEBOOKLARGE));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHONEBOOKLARGE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PHONEBOOKLARGE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {

        InitDll(hWnd);
        pSelf = (PMainWindow)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TMainWindow));
        if (pSelf != NULL) {
            pSelf->hWnd = hWnd;
            pSelf->hListView = CreateListView(hWnd, 7);
            pSelf->hTel = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                3, 3, 95, 20, hWnd, IDC_TELEDIT, hInst, NULL);
            pSelf->hFn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                103, 3, 95, 20, hWnd, IDC_FNEDIT, hInst, NULL);
            pSelf->hLn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                203, 3, 95, 20, hWnd, IDC_MNEDIT, hInst, NULL);
            pSelf->hMn = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                303, 3, 95, 20, hWnd, IDC_LNEDIT, hInst, NULL);
            pSelf->hStr = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                403, 3, 95, 20, hWnd, IDC_FLTEDIT, hInst, NULL);
            pSelf->hHs = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
                503, 3, 95, 20, hWnd, IDC_HSEDIT, hInst, NULL);
            pSelf->hFlt = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
                603, 3, 75, 20, hWnd, IDC_FLTEDIT, hInst, NULL);
            pSelf->hSearch = CreateWindow(WC_BUTTON, TEXT("Search"), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | BS_CENTER,
                3, 25, 774, 23, hWnd, IDC_SEARCHBTN, hInst, NULL);
            pSelf->hPrev = CreateWindow(WC_BUTTON, TEXT("Previous"), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | BS_CENTER,
                25, 50, 200, 23, hWnd, IDC_PREVBTN, hInst, NULL);
            pSelf->hNext = CreateWindow(WC_BUTTON, TEXT("Next"), WS_CHILD | WS_OVERLAPPED | WS_EX_CLIENTEDGE | WS_VISIBLE | WS_BORDER | BS_CENTER,
                825, 50, 200, 23, hWnd, IDC_NEXTBTN, hInst, NULL);
        }
        break;
    }
    case WM_COMMAND:
    {
        switch (HIWORD(wParam)) {
        case BN_CLICKED:
            switch (LOWORD(wParam)) {
            case (int)IDC_SEARCHBTN: {
                PhonebookRecord searchParam = MakeSearchParam();
                UpdateListView(pSelf->hListView, phoneBookLoader->Search(searchParam));
                break;
            }
            case (int)IDC_NEXTBTN:
            {
                    PhonebookRecord searchParam = MakeSearchParam();
                    auto result = phoneBookLoader->SearchFrom(searchParam);
                    if (result.size() != 0)
                        UpdateListView(pSelf->hListView, result);
                    break;
            }
            case (int)IDC_PREVBTN:
            {
                    PhonebookRecord searchParam = MakeSearchParam();
                    phoneBookLoader->PrevPage();
                    auto result = phoneBookLoader->SearchFrom(searchParam);
                    if (result.size() != 0)
                        UpdateListView(pSelf->hListView, result);
                    break;
            }
            break;
            }

            switch (LOWORD(wParam))
            {
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
        phoneBookLoader->DestroyPhoneBook();
        FreeLibrary(hDLL);
        PostQuitMessage(0);
        break;

    case WM_NOTIFY:
    {
        NMLVDISPINFO* plvdi;

        switch (((LPNMHDR)lParam)->code)
        {
        case LVN_GETDISPINFO:

            plvdi = (NMLVDISPINFO*)lParam;

            switch (plvdi->item.iSubItem)
            {
            case 0:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->telephone;
                break;
            case 1:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->firstName;
                break;
            case 2:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->lastName;
                break;
            case 3:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->fatherName;
                break;
            case 4:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->street;
                break;
            case 5:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->house;
                break;
            case 6:
                plvdi->item.pszText = phoneBook[plvdi->item.iItem]->flat;
                break;

            default:
                break;
            }

            break;
        }
    }
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

HWND CreateListView(HWND parent, int columns) {

    RECT rcClient;
    GetClientRect(parent, &rcClient);

    HWND hWndListView = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS | WS_EX_CLIENTEDGE, 0, rcClient.top + 100,
        rcClient.right - rcClient.left, rcClient.bottom - rcClient.top - 100, parent, IDC_LISTVIEW, hInst, NULL);

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

void UpdateListView(HWND hListView, std::vector<PhonebookRecord*> book) {
    ListView_DeleteAllItems(hListView);

    LVITEM lvI;

    lvI.mask = LVIF_TEXT;
    lvI.pszText = LPSTR_TEXTCALLBACK;
    lvI.iSubItem = 0;

    phoneBook = book;

    for (int i = 0; i < book.size(); i++) {
        lvI.iItem = i;
        ListView_InsertItem(hListView, &lvI);
    }
}

std::wstring GetText(HWND hEdit)
{
    WCHAR buffer[512];
    GetWindowText(hEdit, buffer, sizeof(buffer));
    return buffer;
}

void InitDll(HWND hWnd) {
    hDLL = LoadLibrary(L"C:\\Users\\home\\Desktop\\Labs\\Третий Сем\\ОСиСП\\PhoneBookLarge\\Debug\\PhoneBookLargeDLL.dll");

    if (hDLL == NULL) {
        MessageBox(hWnd, TEXT("Error loading dll"), NULL, NULL);
        GetLastError();
    }
    else {
        PHONE_BOOK pEntryFunction = (PHONE_BOOK)GetProcAddress(hDLL, "CreatePhoneBookObject");
        phoneBookLoader = pEntryFunction();
        if (phoneBookLoader) {
            phoneBookLoader->InitPhoneBook();
        }
    }
}

PhonebookRecord MakeSearchParam() {
    PhonebookRecord searchParam;
    ZeroMemory(&searchParam, sizeof(searchParam));

    if (pSelf != NULL) {
        std::wstring text = GetText(pSelf->hFn);
        text = GetText(pSelf->hTel);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.telephone));

        text = GetText(pSelf->hFn);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.firstName));

        text = GetText(pSelf->hLn);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.lastName));

        text = GetText(pSelf->hMn);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.fatherName));

        text = GetText(pSelf->hStr);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.street));

        text = GetText(pSelf->hHs);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.house));

        text = GetText(pSelf->hFlt);
        std::copy(std::begin(text), std::end(text), std::begin(searchParam.flat));
    }
    return searchParam;
}
