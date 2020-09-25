#pragma once
#include "Source.h"


class Poliline
{
public:

    typedef std::vector<POINT> TPoints;
    TPoints points;
    int currPos=-1;
    int x0, y0, x1, y1;

    void OnPaint(HDC hdc) {
        if (this != NULL && points.size() > 0) {
            for (int i = 1; i < points.size(); i++) {
                MoveToEx(hdc, points[i - 1].x, points[i - 1].y, NULL);
                LineTo(hdc, points[i].x, points[i].y);
            }
          }

    }

    void OnMButtonDown(int x, int y, BOOL& isDown) {
        isDown = true;
        POINT pt;
        pt.x = x;
        pt.y = y;
        currPos++;
        points.push_back(pt);
        
    }

    void OnMouseMove(int x, int y) {
        if (points.size()>1)
            points.pop_back();
        POINT pt;
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
    }

    void OnMButtonUp(int x, int y, BOOL& isDown, Poliline* fg, std::vector<Poliline*>& myfigures) {
        POINT pt;
        points.pop_back();
        pt.x = x;
        pt.y = y;
        points.push_back(pt);
    }

    void OnDClick(int x, int y, BOOL& isDown, Poliline* fg, std::vector<Poliline*>& myfigures) {
        isDown = false;
        POINT pt;
        pt.x = x;
        pt.y = y;
        currPos++;
        points.push_back(pt);
        myfigures.push_back(fg);

    }

};

