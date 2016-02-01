
#include "background.h"


Background::Background(int pScreen, int pBg, uint16 pMemoryIndex, uint16 pMapIndex)
{
	_screen = pScreen; 
	_bg = pBg;

	_memory_index = pMemoryIndex;
	_priority = pMemoryIndex;
	
	_map_index = pMapIndex;
	_wrap = false;
	
	_cx = 0;
	_cy = 0;

	_xdx = 1;
	_xdy = 0;
	_ydx = 0;
	_ydy = 1;

	_reg_valid = false;

	_type = 0;

	SetTarget();
}

Background::~Background()
{
}


void Background::Priority(uint16 pPriority)
{
	_priority = pPriority;
	_reg_valid = false;
}

uint16 Background::Priority()
{
	return _priority;
}

void Background::Wrap(bool pWrap)
{
	_wrap = pWrap;
	_reg_valid = false;
}

bool Background::Wrap()
{
	return _wrap;
}

void Background::InitConsole()
{
	consoleInitDefault(_reg_map, _reg_data, 16);
}

void Background::Type(uint16 pType)
{
	_type = pType;
	_reg_valid = false;
}

uint16 Background::Type()
{
	return _type;
}

void Background::OffsetX(int pOffset)
{
	_cx = pOffset;
	_reg_valid = false;
}

void Background::OffsetXDelta(int pOffset)
{
	_cx += pOffset;
	_reg_valid = false;
}

int Background::OffsetX()
{
	return _cx;
}

void Background::OffsetY(int pOffset)
{
	_cy = pOffset;
	_reg_valid = false;
}

void Background::OffsetYDelta(int pOffset)
{
	_cy += pOffset;
	_reg_valid = false;
}

int Background::OffsetY()
{
	return _cy;
}

void Background::SetTarget()
{
	if (_screen == 0)
	{
		if (_bg == 0)
		{
			_reg_cr = &BG0_CR;

			_reg_cx = 0;
			_reg_cy = 0;

			_reg_data = (uint16*)BG_BMP_RAM(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM(_map_index);

			_reg_xdx = 0;
			_reg_xdy = 0;
			_reg_ydx = 0;
			_reg_ydy = 0;
		}
		else if (_bg == 1)
		{
			_reg_cr = &BG1_CR;

			_reg_cx = 0;
			_reg_cy = 0;

			_reg_data = (uint16*)BG_BMP_RAM(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM(_map_index);

			_reg_xdx = 0;
			_reg_xdy = 0;
			_reg_ydx = 0;
			_reg_ydy = 0;
		}
		else if (_bg == 2)
		{
			_reg_cr = &BG2_CR;

			_reg_cx = &BG2_CX;
			_reg_cy = &BG2_CY;

			_reg_data = (uint16*)BG_BMP_RAM(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM(_map_index);

			_reg_xdx = &BG2_XDX;
			_reg_xdy = &BG2_XDY;
			_reg_ydx = &BG2_YDX;
			_reg_ydy = &BG2_YDY;
		}
		else if (_bg == 3)
		{
			_reg_cr = &BG3_CR;

			_reg_cx = (vuint32*)0x04000038; // &BG3_CX;
			_reg_cy = (vuint32*)0x0400003C; // &BG3_CY;

			_reg_data = (uint16*)BG_BMP_RAM(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM(_map_index);

			_reg_xdx = &BG3_XDX;
			_reg_xdy = &BG3_XDY;
			_reg_ydx = &BG3_YDX;
			_reg_ydy = &BG3_YDY;
		}

	} 
	else
	{
		if (_bg == 0)
		{
			_reg_cr = &SUB_BG0_CR;

			_reg_cx = 0;
			_reg_cy = 0;

			_reg_data = (uint16*)BG_BMP_RAM_SUB(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM_SUB(_map_index);

			_reg_xdx = 0;
			_reg_xdy = 0;
			_reg_ydx = 0;
			_reg_ydy = 0;
		}
		else if (_bg == 1)
		{
			_reg_cr = &SUB_BG1_CR;

			_reg_cx = 0;
			_reg_cy = 0;

			_reg_data = (uint16*)BG_BMP_RAM_SUB(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM_SUB(_map_index);

			_reg_xdx = 0;
			_reg_xdy = 0;
			_reg_ydx = 0;
			_reg_ydy = 0;
		}
		else if (_bg == 2)
		{
			_reg_cr = &SUB_BG2_CR;

			_reg_cx = &SUB_BG2_CX;
			_reg_cy = &SUB_BG2_CY;

			_reg_data = (uint16*)BG_BMP_RAM_SUB(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM_SUB(_map_index);

			_reg_xdx = &SUB_BG2_XDX;
			_reg_xdy = &SUB_BG2_XDY;
			_reg_ydx = &SUB_BG2_YDX;
			_reg_ydy = &SUB_BG2_YDY;
		}
		else if (_bg == 3)
		{
			_reg_cr = &SUB_BG3_CR;

			_reg_cx = &SUB_BG3_CX;
			_reg_cy = &SUB_BG3_CY;

			_reg_data = (uint16*)BG_BMP_RAM_SUB(_memory_index);
			_reg_map = (uint16*)BG_MAP_RAM_SUB(_map_index);

			_reg_xdx = &SUB_BG3_XDX;
			_reg_xdy = &SUB_BG3_XDY;
			_reg_ydx = &SUB_BG3_YDX;
			_reg_ydy = &SUB_BG3_YDY;
		}

	}
	_reg_valid = false;
}

void Background::WriteRegisters()
{
	if (_wrap)
	{
		_cr = (_type | BG_BMP_BASE(_memory_index) | BG_MAP_BASE(_map_index) | BG_PRIORITY(_priority) | BG_WRAP_ON);
	} else 
	{
		_cr = (_type | BG_BMP_BASE(_memory_index) | BG_MAP_BASE(_map_index) | BG_PRIORITY(_priority));
	}

	(*_reg_cr) = _cr;

	if (_reg_cx != 0)
	{
		(*_reg_cx) = (_cx << 8);
		(*_reg_cy) = (_cy << 8);
		(*_reg_xdx) = (_xdx << 8); 
		(*_reg_xdy) = _xdy;
		(*_reg_ydx) = _ydx;
		(*_reg_ydy) = (_ydy << 8);
	}
	_reg_valid = true;
}

void Background::Prepare()
{
	_cr = _type | BG_BMP_BASE(_memory_index) | BG_MAP_BASE(_map_index) | BG_PRIORITY(_priority) ;
	 (*_reg_cr) = _cr;
}

void Background::Display()
{
	if (!_reg_valid) 
			WriteRegisters();
}

void Background::Clear()
{

	// byte-weise, zu langsam
	//for (int i = 0; i < 256*256; i++)	_reg_data[i] = 0;

	// word-weise, besser
	//uint16 * regdata = (uint16 *)_reg_data;
	//for (int i = 0; i < 32768; i++) regdata[i] = (uint16)0;

	// 4-byte weise, funktioniert nicht richtig
	//int32 * regdata = (int32 *)_reg_data;
	//for (int i = 0; i < 16384; i++) regdata[i] = (int32)0;

	// fastcopy, bislang am schnellsten aber irgendwie komisch
	int32 zero = 0;
	swiFastCopy(&zero, _reg_data, COPY_MODE_FILL | (192*256*2/4) );

	// memset, macht müll auf der hw?
	//memset(_reg_data,0,192*256*2/4);
	
}




