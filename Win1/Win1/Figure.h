#pragma once
class Figure
{
public:
	int x0, y0, x1, y1;
	virtual void OnPaint();
	virtual void  OnMButtonDown(int x, int y);
	virtual void OnMButtonUp(int x, int y,Figure* fg);
	virtual void OnMouseMove(int x, int y);	
};

