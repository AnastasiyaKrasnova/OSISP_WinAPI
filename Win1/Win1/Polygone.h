#pragma once
#include "Source.h"


class Poligone : public Figure
{
public:
    POINT pt[5];

    int getType()
    {
        return 6;
    } 

    void OnPaint(HDC hdc) {
        if (this != NULL) {
            Polygon(hdc,pt,5);
        }

    }

    void OnMButtonDown(int x, int y, BOOL& isDown) {
        pt[0].x = x;
        pt[0].y = y;
        pt[1].x = pt[0].x + 40;
        pt[1].y = pt[0].y + 40;
        pt[2].x = pt[1].x + 40;
        pt[2].y = pt[0].y;
        pt[3].x = pt[2].x;
        pt[3].y = pt[2].y-40;
        pt[4].x = pt[0].x;
        pt[4].y = pt[3].y;
        isDown = true;
    }

    void OnMouseMove(int x, int y) {
        pt[2].x = x;
        pt[2].y = y;
        pt[1].x = pt[0].x+abs(pt[2].x-pt[0].x);
        pt[1].y = y + 40;
        pt[3].x = pt[2].x;
        pt[3].y = pt[2].y - 40;
        pt[4].x = pt[0].x;
        pt[4].y = pt[3].y;
    }

    void  OnMButtonUp(int x, int y, BOOL& isDown, Poligone* fg, std::vector<Figure*>& myfigures) {
        myfigures.push_back(fg);
        isDown = false;
    }

    void OnDClick(int x, int y, BOOL& isDown, Poligone* fg, std::vector<Figure*>& myfigures) {}

    void OnChar(WPARAM wParam, BOOL& isDown, Poligone* fg, std::vector<Figure*>& myfigures) {}
};