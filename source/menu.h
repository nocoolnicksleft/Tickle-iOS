#pragma once

#include "common.h"
#include "screenframebuffer.h"
#include "flipbook.h"
#include "controlbutton.h"

class Menu
{
protected:
	static Flipbook * kitzeln;

	static ControlButton * buttonOptions;
	static ControlButton * buttonSea;
	static ControlButton * buttonBeach;
	static ControlButton * buttonPlay;
	static ControlButton * buttonShopping;
	static ControlButton * buttonBubbles;

	static ScreenFramebuffer * screen;

public:
	Menu();
	~Menu(void);

public:
	static void Init();
	static void Load();
	static void Unload();
	static void Run(ScreenFramebuffer * screen);
	static void BubbleButton_OnAnimationCompleted(ControlButton * button, uint8 state);
	static void SeaButton_OnAnimationCompleted(ControlButton * button, uint8 state);
	static void BeachButton_OnAnimationCompleted(ControlButton * button, uint8 state);
};

