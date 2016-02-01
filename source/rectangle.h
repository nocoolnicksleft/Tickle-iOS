#pragma once

#include "common.h"

class Rectangle
{
	bool _enabled;

public:
	int Top;
	int Left;
	int Width;
	int Height;

public:
	Rectangle(int x, int y, int width, int height);

public:
	~Rectangle(void);

public:
	void Enable();
	void Disable();

	bool Enabled();

	bool Hit(int pX, int pY);

	int Bottom();
	int Right();

};

class Point
{
public:
	int X;
	int Y;

public:
	 Point(int x, int y);
};
