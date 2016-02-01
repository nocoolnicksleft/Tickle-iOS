#pragma once

#include "common.h"
#include "sprite.h"
#include "window.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192
#define SCREEN_PIXELCOUNT (256*192)


class Screen : public Window
{
protected:
	int _id;
	vuint32 * _reg_cr; 
	uint32 _cr;

public:
	Screen();
	virtual ~Screen();

public:
	void Off();
	void On();
	void SetMode(uint32 pMode);
};
