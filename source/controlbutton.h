#pragma once

#include "common.h"
#include "window.h"
#include "font.h"
#include "rectangle.h"

#define CONTROLBUTTON_INACTIVE 0
#define CONTROLBUTTON_ACTIVE 1
#define CONTROLBUTTON_PUSHED 2

class ControlButton;

typedef void (*ControlButtonEvent) (ControlButton * button, uint8 state);

class ControlButton : public Window
{
protected:
	uint16 * _fileInactive;
	uint16 * _fileActive;
	uint16 * _filePushed;
	uint8 _duration;
	uint8 _state;
	uint8 _countdown;
	Rectangle * _textRect;
	
	static Font * _fontxx;
	static uint16 * _sounddata;
	static uint32 _soundsize;

	

public:
	ControlButton(Rectangle * rect, char * text, uint16 * fileInactive, uint16 * fileActive, uint16 * filePushed,uint16 duration);
	virtual ~ControlButton();

public:

	static void Init();

	ControlButtonEvent OnPush;
	ControlButtonEvent OnReset;

	virtual void MsgPenDown(int pX, int pY);
	virtual void Prepare();

	void State(uint8 state);
	uint8 State();

	void Push();
};
