#include "Source.h"

Figure* currFigure;

int FT = 1;
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
        createEntity();
        break;

    case WM_DESTROY:
        DeleteObject(Pen);
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDOWN:
    {
       if (!isDown)
           createEntity();
       onBtnDwn(lParam,wParam);
       break;
    }

    case WM_MOUSEMOVE:
        if (isDown)
        {
            onMouseMove(lParam, wParam);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_LBUTTONUP:
        onBtnUp(lParam, wParam);
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONDBLCLK:
        if (isDown)
        {
            onDCl(lParam, wParam);
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
                Figure* fg = myfigures[i];
                onPt(fg->getType(), fg, memDC);
            }
            onPt(currFigure->getType(), currFigure, memDC);

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
        onChr(lParam, wParam);
        InvalidateRect(hwnd, NULL, TRUE);
     break;

    case WM_KEYDOWN:
        switch (wParam) {
            case 0x31:  FT = 1; break;
            case 0x32:  FT = 2; break;
            case 0x33:  FT = 3; break;
            case 0x34:  FT = 4; break;
            case 0x35:  FT = 5; break;
            case 0x36:  FT = 6; break;
            case 0x37:  FT = 7; break;
        }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;

   
}


void createEntity() {
    switch (FT) {
    case 1: currFigure = new Line(); break;
    case 2: currFigure = new Curvy(); break;
    case 3: currFigure = new Poliline(); break;
    case 4: currFigure = new Rectngl(); break;
    case 5: currFigure = new Ellips(); break;
    case 6: currFigure = new Poligone(); break;
    case 7: currFigure = new Text(); break;
    }
}

void onPt(int type,Figure* fg, HDC hdc) {
    switch (type) {
    case 1: dynamic_cast<Line*>(fg)->OnPaint(hdc); break;
    case 2: dynamic_cast<Curvy*>(fg)->OnPaint(hdc); break;
    case 3: dynamic_cast<Poliline*>(fg)->OnPaint(hdc); break;
    case 4: dynamic_cast<Rectngl*>(fg)->OnPaint(hdc); break;
    case 5: dynamic_cast<Ellips*>(fg)->OnPaint(hdc); break;
    case 6: dynamic_cast<Poligone*>(fg)->OnPaint(hdc); break;
    case 7: dynamic_cast<Text*>(fg)->OnPaint(hdc); break;
    }
}


void onBtnDwn(LPARAM lp, WPARAM wp) {
    switch (FT) {
    case 1: dynamic_cast<Line*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 2: dynamic_cast<Curvy*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 3: dynamic_cast<Poliline*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 4: dynamic_cast<Rectngl*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 5: dynamic_cast<Ellips*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 6: dynamic_cast<Poligone*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    case 7: dynamic_cast<Text*>(currFigure)->OnMButtonDown(LOWORD(lp), HIWORD(lp), isDown); break;
    }
}

void onMouseMove(LPARAM lp, WPARAM wp) {
    switch (FT) {
    case 1: dynamic_cast<Line*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 2: dynamic_cast<Curvy*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 3: dynamic_cast<Poliline*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 4: dynamic_cast<Rectngl*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 5: dynamic_cast<Ellips*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 6: dynamic_cast<Poligone*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    case 7: dynamic_cast<Text*>(currFigure)->OnMouseMove(LOWORD(lp), HIWORD(lp)); break;
    }
}

void onBtnUp(LPARAM lp, WPARAM wp) {
    switch (FT) {
    case 1: dynamic_cast<Line*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Line*>(currFigure), myfigures); break;
    case 2: dynamic_cast<Curvy*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Curvy*>(currFigure), myfigures); break;
    case 3: dynamic_cast<Poliline*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Poliline*>(currFigure), myfigures); break;
    case 4: dynamic_cast<Rectngl*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Rectngl*>(currFigure), myfigures); break;
    case 5: dynamic_cast<Ellips*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Ellips*>(currFigure), myfigures); break;
    case 6: dynamic_cast<Poligone*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Poligone*>(currFigure), myfigures); break;
    case 7: dynamic_cast<Text*>(currFigure)->OnMButtonUp(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Text*>(currFigure), myfigures); break;
    }
}

void onDCl(LPARAM lp, WPARAM wp) {
    switch (FT) {
    case 1: dynamic_cast<Line*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Line*>(currFigure), myfigures); break;
    case 2: dynamic_cast<Curvy*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Curvy*>(currFigure), myfigures); break;
    case 3: dynamic_cast<Poliline*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Poliline*>(currFigure), myfigures); break;
    case 4: dynamic_cast<Rectngl*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Rectngl*>(currFigure), myfigures); break;
    case 5: dynamic_cast<Ellips*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Ellips*>(currFigure), myfigures); break;
    case 6: dynamic_cast<Poligone*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Poligone*>(currFigure), myfigures); break;
    case 7: dynamic_cast<Text*>(currFigure)->OnDClick(LOWORD(lp), HIWORD(lp), isDown, dynamic_cast<Text*>(currFigure), myfigures); break;
    }
}

void onChr(LPARAM lp, WPARAM wp) {
    switch (FT) {
    case 1: dynamic_cast<Line*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Line*>(currFigure), myfigures); break;
    case 2: dynamic_cast<Curvy*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Curvy*>(currFigure), myfigures); break;
    case 3: dynamic_cast<Poliline*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Poliline*>(currFigure), myfigures); break;
    case 4: dynamic_cast<Rectngl*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Rectngl*>(currFigure), myfigures); break;
    case 5: dynamic_cast<Ellips*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Ellips*>(currFigure), myfigures); break;
    case 6: dynamic_cast<Poligone*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Poligone*>(currFigure), myfigures); break;
    case 7: dynamic_cast<Text*>(currFigure)->OnChar(wp, isDown, dynamic_cast<Text*>(currFigure), myfigures); break;
    }
}


