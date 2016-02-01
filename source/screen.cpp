#include "common.h"
#include "screen.h"


Screen::Screen() : Window(new Rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT),"screen")
{
	_id = 0;
	_reg_cr = 0;	
}

Screen::~Screen()
{
}

void Screen::Off()
{
	(*_reg_cr) |= DISPLAY_SCREEN_OFF;
}

void Screen::On()
{
	(*_reg_cr) &= ~DISPLAY_SCREEN_OFF;
}

void Screen::SetMode(uint32 pMode)
{
  _cr = pMode;
  (*_reg_cr) = _cr;
}



