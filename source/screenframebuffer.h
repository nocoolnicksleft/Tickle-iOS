#pragma once

#include "common.h"
#include "flipbook.h"
#include "window.h"
#include "bitmap.h"
#include "screen.h"


class ScreenFramebuffer : public Screen
{
public:
	Bitmap * _background_buffer;

public:
	ScreenFramebuffer(int pId, uint16 * pVRAM);
	virtual ~ScreenFramebuffer(void);

public:	
	void LoadCompressedBackground(uint16 * pSrc);
	virtual void Display();
	virtual void BufferToScreen();
};
