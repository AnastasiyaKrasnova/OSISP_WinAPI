#include "Source.h"

Line* currFigure;
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)

{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW| CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    hInst = hInstance; 

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,_T("Call to RegisterClassEx failed!"),
            _T("MyPaint"),NULL);
        return 1;
    }
 
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        700, 700,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,_T("Call to CreateWindow failed!"),
            _T("MyPaint"),NULL);
        return 1;
    }

    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        Pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
        currFigure = new Line();
        break;

    case WM_DESTROY:
        DeleteObject(Pen);
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDOWN:
    {
       if (!isDown)
           currFigure = new Line();
        currFigure->OnMButtonDown(LOWORD(lParam), HIWORD(lParam),isDown);
        break;
    }

    case WM_MOUSEMOVE:
        if (isDown)
        {
            currFigure->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_LBUTTONUP:
        currFigure->OnMButtonUp(LOWORD(lParam), HIWORD(lParam),isDown,currFigure,myfigures);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_LBUTTONDBLCLK:
        if (isDown)
        {
            currFigure->OnDClick(LOWORD(lParam), HIWORD(lParam), isDown, currFigure, myfigures);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(hwnd, &ps);
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP hBM = CreateCompatibleBitmap(hdc, 1000, 1000);
        HANDLE hOld = SelectObject(memDC, hBM);
        RECT r;
        SetRect(&r, 0, 0, 1000, 1000);
        FillRect(memDC, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

        HPEN OldPen = (HPEN)SelectObject(memDC, Pen);
            for (size_t i = 0; i < myfigures.size(); ++i) {
                Line* fg = myfigures[i];
                fg->OnPaint(memDC);
            }
            currFigure->OnPaint(memDC);

        BitBlt(hdc, 0, 0, 1000, 1000, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, hOld);
        DeleteObject(hBM);
        DeleteDC(memDC);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_ERASEBKGND:
        InvalidateRect(hwnd, NULL, FALSE);
        break;

    case WM_CHAR:
        currFigure->OnChar(wParam, isDown, currFigure, myfigures);
        InvalidateRect(hwnd, NULL, TRUE);
     break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}





