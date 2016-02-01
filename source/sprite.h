#pragma once

#include "common.h"

class Sprite
{
protected:
	bool _enabled;

	unsigned int _animation_first;
	unsigned int _animation_last;
	unsigned int _animation_mirror;
	unsigned int _animation_current;

	unsigned int _size;

	unsigned int _delay;
	unsigned int _countdown;

	unsigned int _x;
	unsigned int _y;

	unsigned int _height;
	unsigned int _width;


	unsigned int _vram_address;
	unsigned int _spriteSize;
	unsigned int _numTiles;

	uint16 * _spriteGfxMemory;

	sSpriteEntry * _spriteEntry;

public:
	static u32 _next_address;

public:
	Sprite(int pSize);
public:
	virtual ~Sprite(void);

public:
	void Initialize(
		  sSpriteEntry * pSpriteEntry, 
		  uint16 * pSpriteGfxMemory);

	virtual void Initialized();

	void Enable();
	void Disable();

	bool Enabled();

	void Move(u16 pX, u16 pY);
	void MoveDelta(u16 x, u16 y);

	void Rotate(u16 angle);

	bool Hit(unsigned int x, unsigned int y);

	unsigned int X();
	void X(unsigned int pX);

	unsigned int Y();
	void Y(unsigned int pY);

	unsigned int Height();
	unsigned int Width();

	virtual void Prepare();
	virtual void Display();

};
