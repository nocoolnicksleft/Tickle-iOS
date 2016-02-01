#pragma once

#include "common.h"
#include "screenframebuffer.h"
#include "flipbook.h"
#include "controlbutton.h"

// bubbles status
#define BEACH_WALK_N 0
#define BEACH_WALK_NE 1
#define BEACH_WALK_E 2
#define BEACH_WALK_SE 3
#define BEACH_WALK_S 4
#define BEACH_WALK_SW 5
#define BEACH_WALK_W 6
#define BEACH_WALK_NW 7

class Beach
{
protected:
	static Flipbook * pinkyWalk;
	
	static ControlButton * buttonBack;

	static uint16 beach_status;
	
	static ScreenFramebuffer * screen;

	
public:
	Beach();
	~Beach(void);

public:
	static void Init();
	static void Load();
	static void Unload();
	static void Run(ScreenFramebuffer * screen);
	static void Beach_Pinky_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId);

	static void BackButton_OnAnimationCompleted(ControlButton * button, uint8 state);
	static void OnBeachInactivity();
	static void Beach_Start();
	static void Keys(uint32 keysDown, uint32 keysHeld);

};

