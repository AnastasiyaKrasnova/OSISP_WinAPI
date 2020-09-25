#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include "Rect.h"
#include "Line.h"
#include "Ellips.h"
#include "Curvy.h"
#include "Polyline.h"
#include "Text.h"
#include "Polygone.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("myPaint");
HINSTANCE hInst;
HDC hdc;
PAINTSTRUCT ps;
HPEN Pen;

typedef enum {CLINE,SLINE,FRECT,NRECT,TEXT,ELLIPS} TFigure ;
BOOL isDown = FALSE;
std::vector<Line*> myfigures;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

