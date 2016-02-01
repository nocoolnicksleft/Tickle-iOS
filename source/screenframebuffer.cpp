#include "common.h"
#include "screen.h"
#include "screenframebuffer.h"
#include "sprite.h"
#include "bitmap.h"


ScreenFramebuffer::ScreenFramebuffer(int pId, uint16 * pVRAM)  : Screen()
{
	_id = pId;

	_pen_capture_target = 0;

	_background_buffer = new Bitmap(SCREEN_WIDTH,SCREEN_HEIGHT);
	_background_buffer->Clear(0);

	_parent_buffer = new Bitmap(SCREEN_WIDTH,SCREEN_HEIGHT,pVRAM);

	if (pId == 0)
		_reg_cr = &DISPLAY_CR;
	else 
		_reg_cr = &SUB_DISPLAY_CR;
}

ScreenFramebuffer::~ScreenFramebuffer(void)
{
	if (_background_buffer) delete _background_buffer;
}

void ScreenFramebuffer::LoadCompressedBackground(uint16 * pSrc)
{
	bitblt16rle(_background_buffer->GetImageBuffer(),SCREEN_WIDTH,0,0,pSrc);	
}

void ScreenFramebuffer::Display()
{
	_background_buffer->CopyBuffer(_buffer);
	Window::Display();
}

void ScreenFramebuffer::BufferToScreen()
{
	_buffer->CopyBufferVRAM(_parent_buffer);
}


