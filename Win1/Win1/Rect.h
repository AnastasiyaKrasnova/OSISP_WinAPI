#pragma once
#include "Source.h"
#include "Figure.h"


class Rectngl : public Figure
{
public:
    int x0, y0, x1, y1;

    int getType()
    {
        return 4;
    }

    void OnPaint(HDC hdc) {
        if (this != NULL ) {
            Rectangle(hdc, x0, y0, x1, y1);
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

    void  OnMButtonUp(int x, int y, BOOL& isDown, Rectngl* fg, std::vector<Figure*>& myfigures) {
        myfigures.push_back(fg);
        isDown = false;
    }

    void OnDClick(int x, int y, BOOL& isDown, Rectngl* fg, std::vector<Figure*>& myfigures) {}

    void OnChar(WPARAM wParam, BOOL& isDown, Rectngl* fg, std::vector<Figure*>& myfigures) {}
};

