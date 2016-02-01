#pragma once

#include "common.h"
#include "sprite.h"
#include "background.h"

class ScreenEngine : public Screen
{
protected:
	SpriteEntry * _sprites;
	SpriteRotation * _sprite_rotations;

	vector<Sprite *> _spriteObject;

	void * _bg_gfx;
	void * _bg_pal;

	vuint16 * _reg_mosaic_cr; 
	vuint16 * _reg_blend_cr; 
	vuint16 * _reg_blend_y; 
	vuint16 * _reg_blend_ab; 

	Background * _bg0;
	Background * _bg1;
	Background * _bg2;
	Background * _bg3;

	void * _sprite_pal;

	void * _oam;

	uint16 * _sprite_gfx;
	void * _sprite_gfx_next_address;

public:
	ScreenEngine(int pId);

public:
	virtual ~ScreenEngine(void);

public:
	void initOAM();
	void updateOAM();

	// Add sprite to collection
	void addSprite(Sprite * pSprite);

	void LoadBgPal(const void * _source);
	void LoadSpritePal(const void * _source);

	void ClearSprites();	

	virtual void Prepare();

	virtual void Display();
	virtual void BufferToScreen();

	virtual void FadeToWhite(int pTime);
	virtual void FadeFromWhite(int pTime);
	virtual void FadeToBlack(int pTime);
	virtual void FadeFromBlack(int pTime);

	virtual void MsgPenDown(int pX, int pY);
	virtual void MsgPenUp(int pX, int pY);
	virtual void MsgPenMove(int pX, int pY, int dx, int dy);


};
