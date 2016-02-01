
#include "menu.h"

#define BUTTON_ROW_1_Y 146
#define BUTTON_ROW_2_Y 165
#define BUTTON_COL_1_X 30
#define BUTTON_COL_2_X 100
#define BUTTON_COL_3_X 170

ScreenFramebuffer * Menu::screen = 0;

Flipbook * Menu::kitzeln = 0;

ControlButton * Menu::buttonOptions = 0;
ControlButton * Menu::buttonSea = 0;
ControlButton * Menu::buttonBeach = 0;
ControlButton * Menu::buttonPlay = 0;
ControlButton * Menu::buttonShopping = 0;
ControlButton * Menu::buttonBubbles = 0;

Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::Init()
{
	//Unload();

}

void Menu::BubbleButton_OnAnimationCompleted(ControlButton * button, uint8 state)
{
	SendMessage(PM_STARTBUBBLES);
}

void Menu::SeaButton_OnAnimationCompleted(ControlButton * button, uint8 state)
{
	SendMessage(PM_TOGGLETEXTFENSTER);
}

void Menu::BeachButton_OnAnimationCompleted(ControlButton * button, uint8 state)
{
	SendMessage(PM_STARTBEACH);
}

void Menu::Load()
{
	Init();

	uint16 * file_inactive = LoadFile(button_inactive_rle_bin);
	uint16 * file_active = LoadFile(button_active_rle_bin);
	uint16 * file_pushed = LoadFile(button_pressed_rle_bin);

	buttonBubbles  = new ControlButton(new Rectangle(BUTTON_COL_1_X,BUTTON_ROW_1_Y,61,15),"Bubbles",file_inactive,file_active,file_pushed,3);
	buttonBubbles->OnReset = &BubbleButton_OnAnimationCompleted;

	buttonSea = new ControlButton(new Rectangle(BUTTON_COL_2_X,BUTTON_ROW_2_Y,61,15),"Sea",file_inactive,file_active,file_pushed,3);
	buttonSea->OnReset = &SeaButton_OnAnimationCompleted;
	
	buttonOptions  = new ControlButton(new Rectangle(BUTTON_COL_1_X,BUTTON_ROW_2_Y,61,15),"Options",file_inactive,file_active,file_pushed,3);
	buttonPlay  = new ControlButton(new Rectangle(BUTTON_COL_2_X,BUTTON_ROW_1_Y,61,15),"Play",file_inactive,file_active,file_pushed,3);
	
	buttonBeach  = new ControlButton(new Rectangle(BUTTON_COL_3_X,BUTTON_ROW_1_Y,61,15),"Beach",file_inactive,file_active,file_pushed,3);
	buttonBeach->OnReset = &BeachButton_OnAnimationCompleted;

	buttonShopping  = new ControlButton(new Rectangle(BUTTON_COL_3_X,BUTTON_ROW_2_Y,61,15),"Shopping",file_inactive,file_active,file_pushed,3);

	kitzeln = new Flipbook(new Rectangle(13,2,96,120),"kitzeln");

	kitzeln->LoadAnimation(0,bigpinky_kitzel_0_ani_bin,ar_bigpinky_kitzel_0);
	kitzeln->LoadAnimation(1,bigpinky_kitzel_1_ani_bin,ar_bigpinky_kitzel_1);
	kitzeln->LoadAnimation(2,bigpinky_kitzel_2_ani_bin,ar_bigpinky_kitzel_2);
	kitzeln->LoadAnimation(3,bigpinky_kitzel_3_ani_bin,ar_bigpinky_kitzel_3);
	
	kitzeln->AddAction(new Rectangle(36,43,42,45),0,0);
	kitzeln->AddAction(new Rectangle(20,0,61,43),0,1);
	kitzeln->AddAction(new Rectangle(23,95,60,24),0,2);
	kitzeln->AddAction(new Rectangle(25,43,10,45),0,3);

}

void Menu::Unload()
{
	if (buttonBubbles) {
		screen->RemoveWindow(buttonBubbles);
		delete buttonBubbles;
	}

	if (buttonPlay) {
		screen->RemoveWindow(buttonPlay);
		delete buttonPlay;
	}

	if (buttonSea) {
		screen->RemoveWindow(buttonSea);
		delete buttonSea;
	}

	if (buttonBeach) {
		screen->RemoveWindow(buttonBeach);
		delete buttonBeach;
	}
		
	if (buttonShopping) {
		screen->RemoveWindow(buttonShopping);
		delete buttonShopping;
	}

	if (buttonOptions) {
		screen->RemoveWindow(buttonOptions);
		delete buttonOptions;
	}

	if (kitzeln) {
		screen->RemoveWindow(kitzeln);
		delete kitzeln;
	}

	buttonBubbles = 0;
	buttonPlay = 0;
	buttonSea = 0;
	buttonBeach = 0;
	buttonShopping = 0;
	buttonOptions = 0;
	kitzeln = 0;
}

void Menu::Run(ScreenFramebuffer * subscreen)
{
	screen = subscreen;

	screen->AddWindow(kitzeln,20);
	screen->AddWindow(buttonBubbles,10);
	screen->AddWindow(buttonPlay,10);
	screen->AddWindow(buttonSea,10);
	screen->AddWindow(buttonBeach,10);
	screen->AddWindow(buttonShopping,10);
	screen->AddWindow(buttonOptions,10);

	
	subscreen->LoadCompressedBackground(LoadFile(banner_rle_bin));

	InactivityAction = 0;
	
	//screen->FadeFromBlack(25);
	//subscreen->OnAnimationCompleted = &Bubbles_Start;

}



