
#include "beach.h"

#define BUTTON_ROW_1_Y 146
#define BUTTON_ROW_2_Y 165
#define BUTTON_COL_1_X 30
#define BUTTON_COL_2_X 100
#define BUTTON_COL_3_X 170

ScreenFramebuffer * Beach::screen = 0;

Flipbook * Beach::pinkyWalk = 0;

ControlButton * Beach::buttonBack = 0;

uint16 Beach::beach_status = 0;

Beach::Beach()
{
}

Beach::~Beach()
{
}

void Beach::Init()
{
	//Unload();
}

void Beach::BackButton_OnAnimationCompleted(ControlButton * button, uint8 state)
{
	SendMessage(PM_STARTMENU);
}

void Beach::Load()
{
	Init();

	uint16 * file_inactive = LoadFile(button_inactive_rle_bin);
	uint16 * file_active = LoadFile(button_active_rle_bin);
	uint16 * file_pushed = LoadFile(button_pressed_rle_bin);
	
	 Beach::buttonBack  = new ControlButton(new Rectangle(BUTTON_COL_3_X,BUTTON_ROW_2_Y,61,15),"Back",file_inactive,file_active,file_pushed,3);
	 Beach::buttonBack->OnReset =  &Beach::BackButton_OnAnimationCompleted;

	pinkyWalk = new Flipbook(new Rectangle(100,100,64,64),"pinky_walk");
	pinkyWalk->OnAnimationCompleted = &Beach_Pinky_OnAnimationCompleted;

	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_N,littlepinky_walk_north_ani_bin,ar_littlepinky_walk_north,ar_alphalittlepinky_walk_north);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_NE,littlepinky_walk_northeast_ani_bin,ar_littlepinky_walk_northeast,ar_alphalittlepinky_walk_northeast);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_E,littlepinky_walk_east_ani_bin,ar_littlepinky_walk_east,ar_alphalittlepinky_walk_east);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_SE,littlepinky_walk_southeast_ani_bin,ar_littlepinky_walk_southeast,ar_alphalittlepinky_walk_southeast);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_S,littlepinky_walk_south_ani_bin,ar_littlepinky_walk_south,ar_alphalittlepinky_walk_south);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_SW,littlepinky_walk_southwest_ani_bin,ar_littlepinky_walk_southwest,ar_alphalittlepinky_walk_southwest);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_W,littlepinky_walk_west_ani_bin,ar_littlepinky_walk_west,ar_alphalittlepinky_walk_west);
	pinkyWalk->LoadAnimationAlpha(BEACH_WALK_NW,littlepinky_walk_northwest_ani_bin,ar_littlepinky_walk_northwest,ar_alphalittlepinky_walk_northwest);

	pinkyWalk->Invisible();

}

void Beach::Unload()
{


	if (pinkyWalk) {
		screen->RemoveWindow(pinkyWalk);
		delete pinkyWalk;
	}

	if ( Beach::buttonBack) {
		screen->RemoveWindow( Beach::buttonBack);
		delete  Beach::buttonBack;
	}

	pinkyWalk = 0;
	buttonBack = 0;

	beach_status = 0;
}

void Beach::Run(ScreenFramebuffer * subscreen)
{	
	screen = subscreen;

	subscreen->AddWindow(pinkyWalk,10);
	subscreen->AddWindow(buttonBack,100);

	subscreen->LoadCompressedBackground(LoadFile(sand_background_small_rle_bin));

	pinkyWalk->Set(0,0);
	pinkyWalk->Position(100,100);
	pinkyWalk->Visible();
	pinkyWalk->Enable();
	pinkyWalk->Run(0);

	buttonBack->Visible();
	buttonBack->Enable();

	//subscreen->FadeFromBlack(25);
	//subscreen->OnAnimationCompleted = &Beach_Start;	
}

void Beach::Beach_Pinky_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId)
{
	//pinkyWalk->Run(BEACH_WALK_W);
}

void Beach::OnBeachInactivity()
{

}

void Beach::Beach_Start()
{
	// TODO	InactivityAction = &OnBubblesInactivity;
}

void Beach::Keys(uint32 keysDown, uint32 keysHeld)
{
	//DebugPrint("Beach::Keys");
	if ( (keysDown & KEY_LEFT ) || (keysHeld & KEY_LEFT) ) {
		if (keysHeld & KEY_UP) pinkyWalk->Run(BEACH_WALK_NW);
		else if (keysHeld & KEY_DOWN) pinkyWalk->Run(BEACH_WALK_SW);
		else pinkyWalk->Run(BEACH_WALK_W);
	}

	if ( (keysDown & KEY_RIGHT) || (keysHeld & KEY_RIGHT)) {
		if (keysHeld & KEY_UP) pinkyWalk->Run(BEACH_WALK_NE);
		else if (keysHeld & KEY_DOWN) pinkyWalk->Run(BEACH_WALK_SE);
		else pinkyWalk->Run(BEACH_WALK_E);
	}

	if ( (keysDown & KEY_UP   ) || (keysHeld & KEY_UP)   ) {
		if (keysHeld & KEY_LEFT) pinkyWalk->Run(BEACH_WALK_NW);
		else if (keysHeld & KEY_RIGHT) pinkyWalk->Run(BEACH_WALK_NE);
		else pinkyWalk->Run(BEACH_WALK_N);
	}

	if ( (keysDown & KEY_DOWN ) || (keysHeld & KEY_DOWN) ) {
		if (keysHeld & KEY_LEFT) pinkyWalk->Run(BEACH_WALK_SW);
		else if (keysHeld & KEY_RIGHT) pinkyWalk->Run(BEACH_WALK_SE);
		else pinkyWalk->Run(BEACH_WALK_S);
	}
}


