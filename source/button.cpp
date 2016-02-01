#include "sprite.h"
#include "button.h"
#include <stdio.h>
#include <string.h>

#include <gbfs.h>

extern const GBFS_FILE  data_gbfs;

Button::Button(int pSize) : Sprite (pSize)
{
	_status = ButtonStatusUnpressed;

	_delay = 6;

}

void Button::Initialized()
{
	SelectImage();

}

void Button::LoadImages()
{

}

void Button::SelectImage()
{
	uint16 * spriteData = 0;

	char filename[22];

	if (_status == ButtonStatusOff) {
        sprintf(filename,"button_%u.bin",0);
	}
	if (_status == ButtonStatusUnpressed) {
        sprintf(filename,"button_%u.bin",1);
	}
	if (_status == ButtonStatusPressed) {
        sprintf(filename,"button_%u.bin",2);
	}
	
	 //iprintf("Load %s\n",filename);

//	spriteData = (uint16 *)gbfs_get_obj(gbfs_file, filename, NULL);

    DC_FlushAll();
	dmaCopy(spriteData,	&_spriteGfxMemory[(_vram_address*16) ], _spriteSize);	//size of data to copy
}

void Button::Prepare(u32 pTimecodeDelta)
{

}


void Button::Display()
{
	if (_enabled)
	{
		if (_status == ButtonStatusPressed) 
		{
			if (_countdown > 0) _countdown--;
			else  
			{
				_status = ButtonStatusUnpressed;
				SelectImage();
			} // if _countdown / else
		}

	} // if _enabled
}

void Button::Push()
{
	if (_enabled) 
	{
		if (_status != ButtonStatusOff)
		{
			_status = ButtonStatusPressed;
			_countdown = _delay;
			SelectImage();
		}
	}
}

