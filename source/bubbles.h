#pragma once

#include "common.h"
#include "screenframebuffer.h"
#include "flipbook.h"
#include "controlbutton.h"

// bubbles status
#define BUBBLES_STATUS_WAITING 0
#define BUBBLES_STATUS_SITTING 1
#define BUBBLES_STATUS_BATHINGLEFT 2
#define BUBBLES_STATUS_BATHINGLEFT2 3
#define BUBBLES_STATUS_BATHINGLEFT3 4
#define BUBBLES_STATUS_BATHINGFRONT 5
#define BUBBLES_STATUS_DRYING 6
#define BUBBLES_STATUS_OUT 7
#define BUBBLES_STATUS_FINISHED 8

#define BUBBLES_WALKRIGHT 0		 // nach rechts gehen (reinkommen)	          Dateiname: pinky_bubbles_walkright.psd
#define BUBBLES_TURNRIGHTBACK 1  // nach hinten drehen						  Dateiname: pinky_bubbles_turnrightback.psd
#define BUBBLES_CHECKWATER 2     // Wasser prüfen
#define BUBBLES_COLDSTANDING 3   // "zu kalt" während er vor der Wanne steht  (etc)
#define BUBBLES_HOTSTANDING 4    // "zu heiss" während er vor der Wanne steht
#define BUBBLES_SITDOWN 5        // vor der Wanne hinsetzen
#define BUBBLES_COLDSITTING 6    // "zu kalt" während er vor der Wanne sitzt
#define BUBBLES_HOTSITTING 7     // "zu heiss" während er vor der Wanne sitzt
#define BUBBLES_STANDUP 8		 // vor der Wanne wieder aufstehen
#define BUBBLES_CLIMBIN 9        // in die Wanne klettern
#define BUBBLES_SPLASH 10        // planschen
#define BUBBLES_DIVE 11          // tauchen
#define BUBBLES_BLINKLEFT 12      // aus der Wanne klettern
#define BUBBLES_TURNSITTINGFRONT 13 // nach links drehen
#define BUBBLES_SPLASHFRONT 14        // planschen
#define BUBBLES_BLINKFRONT 15      // aus der Wanne klettern
#define BUBBLES_CLIMBOUT 16      // aus der Wanne klettern
#define BUBBLES_DRYNAKED 17      // nach links gehen (rausgehen)
#define BUBBLES_JOYJOY 18      // nach links gehen (rausgehen)
#define BUBBLES_JUMPOUT 19      // nach links gehen (rausgehen)
#define BUBBLES_CONTROLCOLD 20      // nach links gehen (rausgehen)
#define BUBBLES_CONTROLHOT 21      // nach links gehen (rausgehen)
#define BUBBLES_WALKLEFT 22      

#define BUBBLES_SCHAUM 0

// Wasserhahn (32x32)
#define BUBBLES_WATER 0           // wasserhahn ohne bewegung (evtl blinken/glitzern?)
#define BUBBLES_HOTWATER 1		 // wasserhahn, heisse seite aktiv (hellrot?) und wasserstrahl
#define BUBBLES_COLDWATER 2       // wasserhahn, kalte seite aktiv (hellblau?) und wasserstrahl

// Handtuch (32x32)
#define BUBBLES_TOWEL_DRY 0           
#define BUBBLES_TOWEL_BACK 1           


class Bubbles
{
protected:
	static Flipbook * wasserhahn;
	static Flipbook * schaum;
	static Flipbook * handtuch;
	static Flipbook * schaumA;
	static Flipbook * schaumB;
	static Flipbook * schaumC;
	static Flipbook * planschen;

	static ControlButton * buttonBack;

	static uint16 bubbles_status;
	static uint16 bubbles_temp;
	static uint16 bubbles_wasserstand;
	static uint16 bubbles_annoyance;
	static uint16 bubbles_selfcontrol;

	static ScreenFramebuffer * screen;

	static uint16 handtuch_start_x;
	static uint16 handtuch_start_y;

public:
	Bubbles();
	~Bubbles(void);

public:
	static void Init();
	static void Load();
	static void Unload();
	static void Run(ScreenFramebuffer * screen);

	static void Handtuch_DragMove(Window * window, int dx, int dy);
	static void Handtuch_DragStart(Window * window, int dx, int dy);
	static void Handtuch_DragEnd(Window * window, int dx, int dy);
	static void Bubbles_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId);
	static void Bubbles_Wasserhahn_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId);
	static void Bubbles_Schaum_OnAnimationCompleted(Flipbook * flipbook, uint16 animationId);
	static void BackButton_OnAnimationCompleted(ControlButton * button, uint8 state);
	static void Schaum_OnClick();
	static void Handtuch_Click();
	static void OnBubblesPinkyClick();
	static void OnBubblesInactivity();
	static void Bubbles_Start();
};

