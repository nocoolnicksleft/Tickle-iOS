#pragma once

#include "common.h"
#include "window.h"
#include "bitmap.h"

class WConsole : public Window
{
protected:
	uint16 _rows;
	uint16 _cols;

	uint16 _current_row;
	uint16 _current_col;

	Font * _font;
	uint16 * _charbuffer;

	uint16 _padding;

//	Bitmap * windowbuffer;
	Bitmap * testbmp;

public:
	WConsole(Rectangle * pRect, uint16 pRows, uint16 pCols, Font * pFont);

public:
	virtual ~WConsole(void)
	{
		if (_charbuffer) delete [] _charbuffer;
	}

public:
	virtual void Clear();
	virtual void Prepare();

	

	void printf(const char * fmt,...);

	//void SetChar(uint16 row, uint16 col, uint16 c);
	void PaintChar(uint16 row, uint16 col, char c);

	void GotoXY(uint16 pX, uint16 pY);

	void ScrollUp();
	void ScrollDown();
	void Print(char * pString);

	void TestFill(char c);

};
