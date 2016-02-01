#include "common.h"
#include "screen.h"
#include "window.h"
#include "screenengine.h"
#include "sprite.h"

ScreenEngine::ScreenEngine(int pId) : Screen()
{
	_id = pId;

	if (pId == 0)
	{
		_oam = OAM;

		_bg_gfx = BG_GFX;
		_bg_pal = BG_PALETTE;

		_sprite_pal = SPRITE_PALETTE;
		_sprite_gfx = SPRITE_GFX;

		_reg_cr = &DISPLAY_CR;

		_reg_mosaic_cr = &MOSAIC_CR; 
		_reg_blend_cr = &BLEND_CR; 
		_reg_blend_y = &BLEND_Y; 
		_reg_blend_ab = &BLEND_AB; 

	} 
	else 
	{
		_oam = OAM_SUB;

		_bg_gfx = BG_GFX_SUB;
		_bg_pal = BG_PALETTE_SUB;

		_sprite_pal = SPRITE_PALETTE_SUB;
		_sprite_gfx = SPRITE_GFX_SUB;

		_reg_cr = &SUB_DISPLAY_CR;

		_reg_mosaic_cr = &SUB_MOSAIC_CR; 
		_reg_blend_cr = &SUB_BLEND_CR; 
		_reg_blend_y = &SUB_BLEND_Y; 
		_reg_blend_ab = &SUB_BLEND_AB; 
	}

	_sprites = new SpriteEntry[128];
	_sprite_rotations = (SpriteRotation *)_sprites;

	initOAM();
	updateOAM();

	_sprite_gfx_next_address = 0;

}

ScreenEngine::~ScreenEngine(void)
{
	delete [] _sprites;
}

void ScreenEngine::updateOAM() {
	DC_FlushAll();
	dmaCopy(_sprites, _oam, 128 * sizeof(SpriteEntry));
}

//Initialize the OAM
void ScreenEngine::initOAM() {
	//For all 128 sprites on the DS, disable and clear any attributes they
	//might have. This prevents any garbage from being displayed and gives
	//us a clean slate to work with.
	int i;
	for(i = 0; i < 128; i++) {
		_sprites[i].attribute[0] = ATTR0_DISABLED;
		_sprites[i].attribute[1] = 0;
		_sprites[i].attribute[2] = 0;
	}
	//For all 32 possible sprite rotations, set them to default values
	for(i = 0; i < 32; i++) {
		_sprite_rotations[i].hdx = 256;
		_sprite_rotations[i].hdy = 0;
		_sprite_rotations[i].vdx = 0;
		_sprite_rotations[i].vdy = 256;
	}
	updateOAM();
}

void ScreenEngine::addSprite(Sprite * pSprite)
{
	_spriteObject.push_back(pSprite);
	_spriteObject.back()->Initialize(&_sprites[_spriteObject.size()],_sprite_gfx);
}

void ScreenEngine::Prepare()
{
	for (unsigned int i =0 ; i < _spriteObject.size(); i++) 
	{
		if (_spriteObject[i]) _spriteObject[i]->Prepare();
	}
}

void ScreenEngine::Display()
{
		for (unsigned int i=0; i<_spriteObject.size(); i++) 
		{
			_spriteObject[i]->Display();
		}

		updateOAM();

		if (_animation_type)
		{
			if (_animation_type == 3) {
				if (_animation_step >= 0x10) _animation_type = 0;
				else {
					_animation_step++;
					(*_reg_blend_y) = _animation_step;
				}
			}
			if (_animation_type == 4) {
				if (_animation_step <= 0x00) _animation_type = 0;
				else {
					_animation_step--;
					(*_reg_blend_y) = _animation_step;
				}
			}
		}
}


void ScreenEngine::LoadBgPal(const void * _source)
{
	dmaCopy(_source,_bg_pal,512);
}

void ScreenEngine::LoadSpritePal(const void * _source)
{
	dmaCopy(_source,_sprite_pal,512);
}

void ScreenEngine::FadeToWhite(int pTime)
{
		_animation_type = 1;
		_animation_delay = 0;
		_animation_step = 0x00;

		(*_reg_blend_cr) = BLEND_FADE_WHITE | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		(*_reg_blend_y) = _animation_step;
}

void ScreenEngine::FadeFromWhite(int pTime)
{
		_animation_type = 2;
		_animation_delay = 0;
		_animation_step = 0x10;

		(*_reg_blend_cr) = BLEND_FADE_WHITE | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		(*_reg_blend_y) = _animation_step;
}

void ScreenEngine::FadeToBlack(int pTime)
{
		_animation_type = 3;
		_animation_delay = 0;
		_animation_step = 0x00;

		(*_reg_blend_cr) = BLEND_FADE_BLACK | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		(*_reg_blend_y) = _animation_step;
}

void ScreenEngine::FadeFromBlack(int pTime)
{
		_animation_type = 4;
		_animation_delay = 0;
		_animation_step = 0x10;

		(*_reg_blend_cr) = BLEND_FADE_BLACK | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		(*_reg_blend_y) = _animation_step;
}


void ScreenEngine::ClearSprites()
{
  _sprite_gfx_next_address = 0;

  _spriteObject.clear();

  Sprite::_next_address = 0;

  initOAM();
  updateOAM();
}

void ScreenEngine::MsgPenDown(int pX, int pY)
{
}

void ScreenEngine::MsgPenUp(int pX, int pY)
{
}

void ScreenEngine::MsgPenMove(int pX, int pY, int dx, int dy)
{
}

void ScreenEngine::BufferToScreen()
{

}

