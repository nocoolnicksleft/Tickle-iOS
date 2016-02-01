#include "common.h"

#include "rectangle.h"


Rectangle::Rectangle(int x, int y, int width, int height)
{
	Left = x;
	Top = y;
	Width = width;
	Height = height;
}

Rectangle::~Rectangle()
{
}

bool Rectangle::Hit(int pX, int pY)
{
	//char DebStr[62];
	//sprintf(DebStr,"px %d py %d l %d t %d r %d b %d",pX,pY,Left,Top,Right(),Bottom());
	//DebugPrint(DebStr);

	if ( 
		(pX >= Left) && (pX <= (Left + Width)) &&
		(pY >= Top) && (pY <= (Top + Height))
	   )
	   return true;
	return false;
}

int Rectangle::Right()
{
	return Left + Width;
}

int Rectangle::Bottom()
{
	return Top + Height;
}


Point::Point(int x, int y)
{
	X = x;
	Y = y;
}


