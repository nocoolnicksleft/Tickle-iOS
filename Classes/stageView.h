//
//  stageView.h
//  animation
//
//  Created by developer on 26.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "flipbook.h"
#import "flipbookAnimation.h"
#import "flipbookFrame.h"

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
#define BUBBLES_STATUS_RUNNINGAWAY 9


#define BUBBLES_WALKRIGHT 0		 // nach rechts gehen (reinkommen)	          Dateiname: pinky_bubbles_walkright.psd
#define BUBBLES_TURNRIGHTBACK 1  // nach hinten drehen						  Dateiname: pinky_bubbles_turnrightback.psd
#define BUBBLES_CHECKWATER 2     // Wasser pr¸fen
#define BUBBLES_COLDSTANDING 3   // "zu kalt" w‰hrend er vor der Wanne steht  (etc)
#define BUBBLES_HOTSTANDING 4    // "zu heiss" w‰hrend er vor der Wanne steht
#define BUBBLES_SITDOWN 5        // vor der Wanne hinsetzen
#define BUBBLES_COLDSITTING 6    // "zu kalt" w‰hrend er vor der Wanne sitzt
#define BUBBLES_HOTSITTING 7     // "zu heiss" w‰hrend er vor der Wanne sitzt
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

#define ACTION_HANDTUCH_CLICK 1
#define ACTION_PINKY_CLICK 2

#define AUTO_RUN FALSE

@interface stageView : UIView <flipbookEventDelegate> {
	
	UIImage * backgroundImage;
	UIImage * testImage1;
	UIImage * testImage2;

	flipbook * planschen;
	flipbook * wasserhahn;
	flipbook * schaum;
	flipbook * schaumA;
	flipbook * schaumB;
	flipbook * schaumC;
	flipbook * handtuch;
	flipbook * buttonBack;
	
	UIButton * btnSchaum;
	UIButton * btnTapHot;
	UIButton * btnTapCold;
	UIButton * btnPinky;
	UIButton * btnHandtuch;

	int bubbles_status;
	int bubbles_temp;
	int bubbles_wasserstand;
	int bubbles_annoyance;
	int bubbles_selfcontrol;
	
	NSTimer * timer;
	
	int handtuch_start_x;
	int handtuch_start_y;
	
	int inactivity_counter;
	int inactivity_threshold;
}

- (id)initWithFrameAndBackground:(CGRect)frame theBackgroundImage:(UIImage *)_bgImage;
- (void)drawRect:(CGRect)rect;
- (void)frameTick:(NSTimer *)theTimer;

- (void)flipbookAnimationStarted:(id)theFlipbook theAnimation:(UInt16)animationId;
- (void)flipbookAnimationCompleted:(id)theFlipbook theAnimation:(UInt16)animationId;
- (void)flipbookActionCommencing:(id)theFlipbook theAction:(UInt16)actionId;
- (void)flipbookPositionChange:(id)theFlipbook thePoint:( CGPoint )point;

- (void)run;
	
- (void)onInactivity;

- (void)btnSchaumTouched:(id)sender;
- (void)btnTapHotTouched:(id)sender;
- (void)btnTapColdTouched:(id)sender;
- (void)btnPinkyTouched:(id)sender;
- (void)btnHandtuchTouched:(id)sender;

- (void)prepareToQuit;

@end
