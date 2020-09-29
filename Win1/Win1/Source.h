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
#include "Figure.h"
//#include "Creators.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("myPaint");
static TCHAR szMenu[] = _T("ID_MENU");
HMENU hMenu;
HINSTANCE hInst;
HDC hdc;
PAINTSTRUCT ps;
HPEN Pen;

BOOL isDown = FALSE;
std::vector<Figure*> myfigures;

void createEntity();
void onBtnDwn(LPARAM lp, WPARAM wp);
void onMouseMove(LPARAM lp, WPARAM wp);
void onBtnUp(LPARAM lp, WPARAM wp);
void onPt(int type, Figure* fg, HDC hdc);
void onDCl(LPARAM lp, WPARAM wp);
void onChr(LPARAM lp, WPARAM wp);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

