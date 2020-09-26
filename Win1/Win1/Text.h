#pragma once
#include "Source.h"


class Text : public Figure
{
public:

    RECT rectPlace;
    HFONT hFont;
    PTCHAR text;
    int size = 0;

    int getType()
    {
        return 7;
    } 

    void OnPaint(HDC hdc) {
        if (this != NULL) {
          DrawText(hdc,(LPCWSTR)text,size, &rectPlace,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

    }

    void OnMButtonDown(int x, int y, BOOL& isDown) {

        isDown = true;
        rectPlace.left = x;
        rectPlace.top = y;
        rectPlace.bottom = y+30;
        rectPlace.right = x+30;
        text = (PTCHAR)GlobalAlloc(GPTR, 50000 * sizeof(TCHAR));
        size = 0;
    }

    void OnMouseMove(int x, int y) {
       
    }

    void OnMButtonUp(int x, int y, BOOL& isDown, Text* fg, std::vector<Figure*>& myfigures) {
       
    }

    void OnChar(WPARAM wParam, BOOL& isDown ,Text* fg, std::vector<Figure*>& myfigures) {
        switch (wParam)
        {
        case VK_ESCAPE:
            myfigures.push_back(fg);
            isDown = false;
            break;
        default:
            if (this != NULL) {
                rectPlace.right += 7;
                text[size] = (char)wParam;
                size++;
            }
            break;
        }
    }

    void OnDClick(int x, int y, BOOL& isDown, Text* fg, std::vector<Figure*>& myfigures) {}
   
};

