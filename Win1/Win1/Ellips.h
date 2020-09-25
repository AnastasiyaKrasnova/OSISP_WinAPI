#pragma once
#include "Source.h"


class Ellips
{
public:
    int x0, y0, x1, y1;

    void OnPaint(HDC hdc) {
        if (this != NULL) {
            Ellipse(hdc, x0, y0, x1, y1);
        }

    }

    void OnMButtonDown(int x, int y, BOOL& isDown) {
        x0 = x;
        y0 = y;
        isDown = true;
    }

    void OnMouseMove(int x, int y) {
        x1 = x;
        y1 = y;
    }

    void  OnMButtonUp(int x, int y, BOOL& isDown,Ellips* fg, std::vector<Ellips*>& myfigures) {
        isDown = false;
        myfigures.push_back(fg);
    }
};

