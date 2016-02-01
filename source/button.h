#pragma once

#include "common.h"

#include "sprite.h"



enum ButtonStatus
{
	ButtonStatusOff,
	ButtonStatusUnpressed,
	ButtonStatusPressed
};

class Button :  public Sprite
{

private:
	ButtonStatus _status;

public:
	Button(int pSize);

public:
	virtual void Initialized();
	void Prepare(u32 pTimecodeDelta);
	void Display();

	// virtual
	void LoadImages();
	void SelectImage();

	// specific
	void Push();

};
