#pragma once
#include "Source.h"

class Figure
{
public:
    virtual int getType()=0;
    virtual ~Figure() {}

    virtual void OnPaint(HDC hdc) {}

    virtual void OnMButtonDown(int x, int y, BOOL& isDown) {}

    virtual void OnMouseMove(int x, int y) {}

    virtual void  OnMButtonUp(int x, int y, BOOL& isDown, Figure* fg, std::vector<Figure*>& myfigures) {}

    virtual void OnDClick(int x, int y, BOOL& isDown, Figure* fg, std::vector<Figure*>& myfigures) {}

    virtual void OnChar(WPARAM wParam, BOOL& isDown, Figure* fg, std::vector<Figure*>& myfigures) {}
};

