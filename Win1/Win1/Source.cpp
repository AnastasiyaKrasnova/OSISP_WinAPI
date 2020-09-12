#include "Source.h"

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)

{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
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
            _T("Windows Desktop Guided Tour"),NULL);
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
            _T("Windows Desktop Guided Tour"),NULL);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL OnCreate(HWND hwnd,LPCREATESTRUCT lpcs)
{
    return TRUE;
}

void OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}

void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    HPEN hPen = CreatePen(PS_DASHDOTDOT, 2, NULL);
    SelectObject(hdc, hPen);
    Ellipse(hdc, 100, 200, 400, 400);
    Ellipse(hdc, 300, 300, 500, 510);

    DeleteObject(hPen);
    EndPaint(hWnd, &ps);
}

