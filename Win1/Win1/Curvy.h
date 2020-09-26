#pragma once
#include "Source.h"


class Curvy: public Figure
{
public:

    typedef std::vector<POINT> TPoints;
    TPoints points;

    int getType()
    {
        return 2;
    }

    void OnPaint(HDC hdc) {
        if (this != NULL && points.size() > 0) {
            MoveToEx(hdc, points[0].x, points[0].y, NULL);
            for (size_t i = 1; i < points.size(); ++i) {
                LineTo(hdc, points[i].x, points[i].y);
            }
        }

    }

    void OnMButtonDown(int x, int y, BOOL& isDown) {
        points.clear();
        POINT pt;
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
        isDown = true;
    }

    void OnMouseMove(int x, int y) {
        POINT pt;
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
    }

    void OnMButtonUp(int x, int y, BOOL& isDown, Curvy* fg, std::vector<Figure*>& myfigures) {
        isDown = false;
        myfigures.push_back(fg);
    }

    void OnDClick(int x, int y, BOOL& isDown, Curvy* fg, std::vector<Figure*>& myfigures) {}

    void OnChar(WPARAM wParam, BOOL& isDown, Curvy* fg, std::vector<Figure*>& myfigures) {}
};
