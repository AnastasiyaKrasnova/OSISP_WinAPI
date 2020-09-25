#pragma once
#include "Source.h"


class Line
{
public:

    int x0, y0, x1, y1;

    void OnPaint(HDC hdc) {
        if (this !=NULL) {
            MoveToEx(hdc, x0, y0, NULL);
            LineTo(hdc, x1, y1);
        }
           
    }

    void OnMButtonDown(int x,int y, BOOL& isDown) {
        x0 = x;
        y0 = y;
        isDown = true;
    }

    void OnMouseMove(int x, int y) {
        x1 = x;
        y1 = y;
    }

    void OnMButtonUp(int x, int y, BOOL& isDown, Line* fg, std::vector<Line*> &myfigures) {
        myfigures.push_back(fg);
        isDown = false;
    }

    void OnDClick(int x, int y, BOOL& isDown, Line* fg, std::vector<Line*>& myfigures) {}

    void OnChar(WPARAM wParam, BOOL& isDown, Line* fg, std::vector<Line*>& myfigures) {}
};

