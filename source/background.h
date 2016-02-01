#pragma once

#include "common.h"

class Background
{
protected:
	bool _enabled;

	int _screen;
	int _bg;
	uint16 _type;
	uint16 _memory_index;
	uint16 _map_index;
	uint16 _mode;
	bool _wrap;
	int16 _priority;

	bool _reg_valid;

	// Register addresses
	vuint16 * _reg_cr;
	
	vuint32 * _reg_cx;
	vuint32 * _reg_cy;

	vuint16 * _reg_xdx;
	vuint16 * _reg_xdy;
	vuint16 * _reg_ydx;
	vuint16 * _reg_ydy;

	uint16 * _reg_data;
	uint16 * _reg_map;

	// Stored Values
	uint16 _cr;
	
	int _cx;
	int _cy;

	int16 _xdx;
	int16 _xdy;
	int16 _ydx;
	int16 _ydy;

	int32 _data;
	int32 _map;

/*
BG3_CR = BG_BMP8_256x256 | BG_BMP_BASE(4) | BG_PRIORITY(3);
SUB_BG3_CR = BG_BMP8_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(2);
*/

public:
	Background(int pScreen, int pBg, uint16 pMemoryIndex, uint16 pMapIndex);

public:
	~Background(void);

public:

	void Clear();

	void Type(uint16 pType);
	uint16 Type();

	void Priority(uint16 pPriority);
	uint16 Priority();

	void Wrap(bool pWrap);
	bool Wrap();

	void SetTarget();
	void WriteRegisters();

	void OffsetX(int pOffset);
	void OffsetXDelta(int pOffset);
	int OffsetX();

	void OffsetY(int pOffset);
	void OffsetYDelta(int pOffset);
	int OffsetY();

	void Enable();
	void Disable();

	bool Enabled();

	void Move(u16 pX, u16 pY);
	void MoveDelta(u16 x, u16 y);

	void Rotate(u16 angle);

	unsigned int Height();
	unsigned int Width();

	void InitConsole();

	void Prepare();

	
	void Display();

};
