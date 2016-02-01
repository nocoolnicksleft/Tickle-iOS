#include "sprite.h"

u32 Sprite::_next_address = 0;

Sprite::Sprite( int pSize	)
{

	_size = pSize;

	_enabled = false;

	_x = 0;
	_y = 0;

	_delay = 0;
	_countdown = 0;

	_animation_first = 0;
	_animation_last = 0;
	_animation_mirror = 0;


}

void Sprite::Initialize(sSpriteEntry * pSpriteEntry, 
						uint16 * pSpriteGfxMemory
						)
{
	_spriteGfxMemory = pSpriteGfxMemory;

	_spriteEntry = pSpriteEntry;

	_vram_address = _next_address;
	
	_spriteEntry->attribute[0] = ATTR0_DISABLED | ATTR0_SQUARE | ATTR0_COLOR_256 | _x;
	_spriteEntry->attribute[2] = _vram_address; // 128*id;

	// ANZAHL TILES
	if (_size == ATTR1_SIZE_32) {
		_spriteSize = 1024;
		_numTiles = 32;
		_height = 32;
		_width = 32;
		_spriteEntry->attribute[1] = ATTR1_ROTDATA(0) | ATTR1_SIZE_32 | _x;
	}
	else if (_size == ATTR1_SIZE_16) {
		_spriteSize = 256;
		_numTiles = 8;
		_height = 16;
		_width = 16;
		_spriteEntry->attribute[1] = ATTR1_ROTDATA(0) | ATTR1_SIZE_16 | _x;
	}
	else if (_size == ATTR1_SIZE_8) {
		_spriteSize = 64;
		_numTiles = 2;
		_height = 8;
		_width = 8;
		_spriteEntry->attribute[1] = ATTR1_ROTDATA(0) | ATTR1_SIZE_8 | _x;
	}
	else { // = ATTR1_SIZE_64
		_spriteSize = 4096; 
		_numTiles = 128; 
		_height = 64;
		_width = 64;
		_spriteEntry->attribute[1] = ATTR1_ROTDATA(0) | ATTR1_SIZE_64 | _x;
	}

	_next_address += _numTiles; // Anzahl TILES  = SIZE / TILESIZE
	
//	iprintf("_vram_address: %u\n",_vram_address);
	Rotate(0);
	Disable();

	Initialized();
}

Sprite::~Sprite()
{

}

bool Sprite::Hit(unsigned int pX, unsigned int pY)
{

	if ( 
		(pX >= _x) && (pX <= (_x + _width)) &&
		(pY >= _y) && (pY <= (_y + _height))
	   )
	   return true;
	return false;
}


void Sprite::X(unsigned int pX)
{
	_x = pX;
	_spriteEntry->attribute[1] &= 0xFE00;
	_spriteEntry->attribute[1] |= (pX & 0x01FF);
}

unsigned int Sprite::Y()
{
	return _y;
}

void Sprite::Y(unsigned int pY)
{
	_y = pY;
	_spriteEntry->attribute[0] &= 0xFF00;
	_spriteEntry->attribute[0] |= (pY & 0x00FF);
}

unsigned int Sprite::X()
{
	return _x;
}

unsigned int Sprite::Width()
{
	return _width;
}

unsigned int Sprite::Height()
{
	return _height;
}

void Sprite::Enable()
{
	_enabled = true;
	_spriteEntry->attribute[0] &= ~ATTR0_DISABLED;
}

void Sprite::Disable()
{
	_enabled = false;
	_spriteEntry->attribute[0] |= ATTR0_DISABLED;
}

bool Sprite::Enabled()
{
	return _enabled;
}

void Sprite::Move(u16 x, u16 y) {
	_x = x;
	_y = y;
	
	_spriteEntry->attribute[1] &= 0xFE00;
	_spriteEntry->attribute[1] |= (x & 0x01FF);
	_spriteEntry->attribute[0] &= 0xFF00;
	_spriteEntry->attribute[0] |= (y & 0x00FF);
	
}

void Sprite::MoveDelta(u16 x, u16 y) {
	_x += x;
	_y += y;
	Move(_x,_y);
}


void Sprite::Rotate(u16 angle) {
/*	if (_spriteRotation) {
		s16 s = -SIN[angle & 0x1FF] >> 4;
		s16 c = COS[angle & 0x1FF] >> 4;
		_spriteRotation->hdx = c;
		_spriteRotation->hdy = -s;
		_spriteRotation->vdx = s;
		_spriteRotation->vdy = c;
	}*/
}

void Sprite::Display()
{
}

void Sprite::Prepare()
{

}

void Sprite::Initialized()
{

}



