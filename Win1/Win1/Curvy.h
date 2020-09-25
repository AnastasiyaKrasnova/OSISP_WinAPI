#pragma once
#include "Source.h"


class Curvy
{
public:

    typedef std::vector<POINT> TPoints;
    TPoints points;
    int x0, y0, x1, y1;

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
        x0 = x;
        y0 = y;
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
        isDown = true;
    }

    void OnMouseMove(int x, int y) {
        POINT pt;
        x1 = x;
        y1 = y;
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
    }

    void OnMButtonUp(int x, int y, BOOL& isDown, Curvy* fg, std::vector<Curvy*>& myfigures) {
        isDown = false;
        myfigures.push_back(fg);
    }
};
