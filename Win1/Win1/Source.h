#pragma once
#include <windowsX.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpcs);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hWnd);
