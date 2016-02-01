//
//  stageView.m
//  animation
//
//  Created by developer on 26.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "stageView.h"


@implementation stageView


- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
    }
    return self;
}


- (id)initWithFrameAndBackground:(CGRect)frame theBackgroundImage:(UIImage *)_bgImage {
    
	if ((self = [super initWithFrame:frame])) {
		
        // Initialization code
		backgroundImage = _bgImage;
		[backgroundImage retain];
		
		wasserhahn = [flipbook alloc];
		[wasserhahn initWithFrameAndName:CGRectMake(30,25,32,32) withName:"wasserhahn"];
//		[wasserhahn initWithFrameAndName:CGRectMake(20,25,32,32) withName:"wasserhahn"];
		 wasserhahn.delegate = self;		
		[wasserhahn loadAnimation:BUBBLES_WATER withName:@"extras_bubbles_tap"];
		[wasserhahn loadAnimation:BUBBLES_HOTWATER withName:@"extras_bubbles_taphot"];
		[wasserhahn addAction:CGRectMake(0, 0, 15, 15) withActionId:0 withAnimationId:BUBBLES_HOTWATER];
		[wasserhahn addSound:BUBBLES_HOTWATER withFrame:0 withName:@"rausch"];
		[wasserhahn loadAnimation:BUBBLES_COLDWATER withName:@"extras_bubbles_tapcold"];
		[wasserhahn addAction:CGRectMake(16, 0, 16, 15) withActionId:0 withAnimationId:BUBBLES_COLDWATER];
		[wasserhahn addSound:BUBBLES_COLDWATER withFrame:0 withName:@"rausch"];
		[wasserhahn visible];
		[wasserhahn enable];
		[wasserhahn setAnimationFrame:0 withFrame:0];
		
		
		schaum = [flipbook alloc];
		[schaum initWithFrameAndName:CGRectMake(30,25,32,32) withName:"schaum"];
		 schaum.delegate = self;		
		[schaum loadAnimation:BUBBLES_SCHAUM withName:@"extras_bubbles_foam"];
		[schaum addAction:CGRectMake(0, 0, 32, 32) withActionId:0 withAnimationId:BUBBLES_SCHAUM];
		[schaum addSound:BUBBLES_SCHAUM withFrame:7 withName:@"blubb"];
		[schaum visible];
		[schaum enable];
		[schaum setAnimationFrame:0 withFrame:0];
		
		schaumA = [flipbook alloc];		
		[schaumA initWithFrameAndName:CGRectMake(54,47,148,40) withName:"schaumA"];
		 schaumA.delegate = self;
		[schaumA loadAnimation:BUBBLES_SCHAUM withName:@"bigpinky_bubbles_foamA"];
		[schaumA setAnimationFrame:0 withFrame:0];
		[schaumA invisible];
		[schaumA disable];
		
		schaumB = [flipbook alloc];		
		[schaumB initWithFrameAndName:CGRectMake(54,47,148,40) withName:"schaumB"];
		 schaumB.delegate = self;
		[schaumB loadAnimation:BUBBLES_SCHAUM withName:@"bigpinky_bubbles_foamB"];
		[schaumB setAnimationFrame:0 withFrame:0];
		[schaumB invisible];
		[schaumB disable];
		
		schaumC = [flipbook alloc];		
		[schaumC initWithFrameAndName:CGRectMake(54,47,148,40) withName:"schaumC"];
		 schaumC.delegate = self;
		[schaumC loadAnimation:BUBBLES_SCHAUM withName:@"bigpinky_bubbles_foamC"];
		[schaumC setAnimationFrame:0 withFrame:0];
		[schaumC invisible];
		[schaumC disable];
		

		handtuch = [flipbook alloc];
		[handtuch initWithFrameAndName:CGRectMake(30,25,120,120) withName:"handtuch"];
		 handtuch.delegate = self;
		[handtuch loadAnimation:BUBBLES_TOWEL_DRY withName:@"bigpinky_bubbles_towel"];
		[handtuch loadAnimation:BUBBLES_TOWEL_BACK withName:@"bigpinky_bubbles_towelback"];
//		[handtuch addAction:CGRectMake(95, 10, 25, 100) withActionId:ACTION_HANDTUCH_CLICK withAnimationId:-1];
		[handtuch addAction:CGRectMake(85, 10, 25, 100) withActionId:ACTION_HANDTUCH_CLICK withAnimationId:-1];
		[handtuch setAnimationFrame:0 withFrame:0];
		[handtuch visible];
		[handtuch enable];
		handtuch.tapAlphaFilter = TRUE;
		
		
		planschen = [flipbook alloc];
		
		[planschen initWithFrameAndName:CGRectMake(30,25,120,120) withName:"planschen"];

		planschen.delegate = self;

		[planschen loadAnimation:BUBBLES_WALKRIGHT withName:@"bigpinky_allgemein_simpleright"];
		
		[planschen loadAnimation:BUBBLES_TURNRIGHTBACK withName:@"bigpinky_bubbles_turnrightback"];
		
		[planschen loadAnimation:BUBBLES_CHECKWATER withName:@"bigpinky_bubbles_checkwater"];
		[planschen addSound:BUBBLES_CHECKWATER withFrame:0 withName:@"plitsch"];
		
		[planschen loadAnimation:BUBBLES_COLDSTANDING withName:@"bigpinky_bubbles_coldstanding"];
		[planschen loadAnimation:BUBBLES_HOTSTANDING withName:@"bigpinky_bubbles_hotstanding"];
		[planschen loadAnimation:BUBBLES_SITDOWN withName:@"bigpinky_bubbles_sitdown"];
		[planschen loadAnimation:BUBBLES_COLDSITTING withName:@"bigpinky_bubbles_coldsitting"];
		[planschen loadAnimation:BUBBLES_HOTSITTING withName:@"bigpinky_bubbles_hotsitting"];
		[planschen loadAnimation:BUBBLES_STANDUP withName:@"bigpinky_bubbles_standup"];
		
		[planschen loadAnimation:BUBBLES_CLIMBIN withName:@"bigpinky_bubbles_climbin"];
		[planschen addSound:BUBBLES_CLIMBIN withFrame:20 withName:@"splash"];
		
		[planschen loadAnimation:BUBBLES_SPLASH withName:@"bigpinky_bubbles_splash"];
		[planschen addSound:BUBBLES_SPLASH withFrame:6 withName:@"splash"];
		
		[planschen loadAnimation:BUBBLES_DIVE withName:@"bigpinky_bubbles_dive"];
		[planschen addSound:BUBBLES_DIVE withFrame:10 withName:@"splash"];
		
		[planschen loadAnimation:BUBBLES_BLINKLEFT withName:@"bigpinky_bubbles_blinkleft"];
		
		[planschen loadAnimation:BUBBLES_TURNSITTINGFRONT withName:@"bigpinky_bubbles_turnsittingfront"];
		
		[planschen loadAnimation:BUBBLES_SPLASHFRONT withName:@"bigpinky_bubbles_splashfront"];
		[planschen addSound:BUBBLES_SPLASHFRONT withFrame:4 withName:@"splash"];
		[planschen addSound:BUBBLES_SPLASHFRONT withFrame:22 withName:@"splash"];
		
		[planschen loadAnimation:BUBBLES_BLINKFRONT withName:@"bigpinky_bubbles_blinkfront"];
		[planschen loadAnimation:BUBBLES_CLIMBOUT withName:@"bigpinky_bubbles_climbout"];
		[planschen loadAnimation:BUBBLES_DRYNAKED withName:@"bigpinky_bubbles_drynaked"];
		[planschen loadAnimation:BUBBLES_JOYJOY withName:@"bigpinky_bubbles_joyjoy"];
		[planschen loadAnimation:BUBBLES_JUMPOUT withName:@"bigpinky_bubbles_jumpout"];
		[planschen loadAnimation:BUBBLES_CONTROLCOLD withName:@"bigpinky_bubbles_controlcold"];
		[planschen loadAnimation:BUBBLES_CONTROLHOT withName:@"bigpinky_bubbles_controlhot"];
		
		[planschen loadAnimation:BUBBLES_WALKLEFT withName:@"bigpinky_allgemein_simpleleft"];
		
//		[planschen addAction:CGRectMake(20, 0, 100, 100) withActionId:ACTION_PINKY_CLICK withAnimationId:-1];			
		[planschen addAction:CGRectMake(0, 0, 120, 120) withActionId:ACTION_PINKY_CLICK withAnimationId:-1];			
		
		[planschen visible];
		[planschen enable];
		
		planschen.tapAlphaFilter = TRUE;

		[self addSubview:wasserhahn];
		[self addSubview:schaum];
		[self addSubview:schaumA];
		[self addSubview:schaumB];
		[self addSubview:planschen];
		[self addSubview:schaumC];
		[self addSubview:handtuch];
		
		self.clipsToBounds = YES;
		
		inactivity_threshold = 125;
		
		timer = [NSTimer scheduledTimerWithTimeInterval:0.07f
										 target:self
									     selector:@selector(frameTick:)
									     userInfo:nil
										 repeats:YES];
		
		btnSchaum = [UIButton buttonWithType:0];
		[btnSchaum setImage:[UIImage imageNamed:[NSString stringWithFormat:@"big-button-schaum.png"]] forState:UIControlStateNormal];
		btnSchaum.showsTouchWhenHighlighted = TRUE;
		btnSchaum.frame = CGRectMake(10, 200, 36, 36);
		[btnSchaum addTarget:self action:@selector(btnSchaumTouched:) forControlEvents:UIControlEventTouchDown];
		
		btnTapHot = [UIButton buttonWithType:0];
		[btnTapHot setImage:[UIImage imageNamed:[NSString stringWithFormat:@"big-button-hot.png"]] forState:UIControlStateNormal];
		btnTapHot.showsTouchWhenHighlighted = TRUE;
		btnTapHot.frame = CGRectMake(60, 200, 36, 36);
		[btnTapHot addTarget:self action:@selector(btnTapHotTouched:) forControlEvents:UIControlEventTouchDown];
		
		btnTapCold = [UIButton buttonWithType:0];
		[btnTapCold setImage:[UIImage imageNamed:[NSString stringWithFormat:@"big-button-cold.png"]] forState:UIControlStateNormal];
		btnTapCold.showsTouchWhenHighlighted = TRUE;
		btnTapCold.frame = CGRectMake(110, 200, 36, 36);
		[btnTapCold addTarget:self action:@selector(btnTapColdTouched:) forControlEvents:UIControlEventTouchDown];
		
		btnPinky = [UIButton buttonWithType:0];
		[btnPinky setImage:[UIImage imageNamed:[NSString stringWithFormat:@"big-button-pinky.png"]] forState:UIControlStateNormal];
		btnPinky.showsTouchWhenHighlighted = TRUE;
		btnPinky.frame = CGRectMake(160, 200, 36, 36);
		[btnPinky addTarget:self action:@selector(btnPinkyTouched:) forControlEvents:UIControlEventTouchDown];

		btnHandtuch = [UIButton buttonWithType:0];
		[btnHandtuch setImage:[UIImage imageNamed:[NSString stringWithFormat:@"big-button-handtuch.png"]] forState:UIControlStateNormal];
		btnHandtuch.showsTouchWhenHighlighted = TRUE;
		btnHandtuch.frame = CGRectMake(210, 200, 36, 36);
		[btnHandtuch addTarget:self action:@selector(btnHandtuchTouched:) forControlEvents:UIControlEventTouchDown];

		[self addSubview:btnSchaum];
		[self addSubview:btnTapHot];
		[self addSubview:btnTapCold];
		[self addSubview:btnPinky];
		[self addSubview:btnHandtuch];

	}

	 return self;
}

- (void)btnSchaumTouched:(id)sender {
	[schaum runAnimation:BUBBLES_SCHAUM];
}

- (void)btnTapHotTouched:(id)sender {
	[wasserhahn runAnimation:BUBBLES_HOTWATER];
}

- (void)btnTapColdTouched:(id)sender {
	[wasserhahn runAnimation:BUBBLES_COLDWATER];
}

- (void)btnPinkyTouched:(id)sender {
	[self flipbookActionCommencing:planschen theAction:ACTION_PINKY_CLICK];
}

- (void)btnHandtuchTouched:(id)sender {
	[self flipbookActionCommencing:handtuch theAction:ACTION_HANDTUCH_CLICK];	
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {

	UITouch *t = [[touches allObjects] objectAtIndex:0];
    
	CGPoint touchPos = [t locationInView:t.view];
	
	
	NSEnumerator * enumerator = [[self subviews] reverseObjectEnumerator];
	flipbook * subview;
	while (subview = [enumerator nextObject]) {
	
		if (CGRectContainsPoint(subview.frame, touchPos)) {
	//		printf("%s touched\r",subview.textId);
			if ([subview executeTap:touchPos]) {
				return;
			}
		}
		
	}
	
	inactivity_counter = 0;
	
	handtuch_start_x = touchPos.x;
	handtuch_start_y = touchPos.y;
	//			char debstr[60];
	//			sprintf(debstr,"Handtuch::Drag Start dx %d dy %d s_x %d s_y %d",dx,dy,handtuch_start_x,handtuch_start_y);
	//			DebugPrint(debstr);

}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {

	if (bubbles_status == BUBBLES_STATUS_OUT)
	{
		if (![planschen isRunning])
		{
			//			char debstr[60];
			//			sprintf(debstr,"Handtuch::Drag dx %d dy %d x %d y %d",dx,dy,handtuch->Position()->Left,handtuch->Position()->Top);
			//			DebugPrint(debstr);
			UITouch *t = [[touches allObjects] objectAtIndex:0];
			
			CGPoint touchPos = [t locationInView:t.view];
	
			int dx = touchPos.x;
			int dy = touchPos.y;
			[handtuch setPositionDelta:dx-handtuch_start_x withY:dy-handtuch_start_y];
			
			int newframe = 0;
			
			if (handtuch->_position.top > 131) handtuch._position.top = 131;
			
			
			if (handtuch->_position.top > 63) 
			{
				newframe = 35 - ((handtuch._position.top  - 63) / 2);
				[handtuch setAnimationFrameNoPosition:BUBBLES_TOWEL_BACK withFrame:newframe];
			}
			
			
			handtuch_start_x = dx;
			handtuch_start_y = dy;
			
		}
	}
	 
	inactivity_counter = 0;

}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {

	
	if (bubbles_status == BUBBLES_STATUS_OUT)
	{
		if (![planschen isRunning])
		{

			if ( (handtuch->_position.top < 100) && (handtuch->_position.left > 170) )
			{
				bubbles_status = BUBBLES_STATUS_FINISHED;
				[self run];
				[handtuch animatePosition:176 pTargetY:36 pTime:[handtuch currentFrame] pCurve:AnimationCurveLinear ];
				//handtuch->OnDragStart = 0;
				//handtuch->OnDragMove = 0;
				//handtuch->OnDragEnd = 0;
				//handtuch->DisablePenCapture();
			} else
			{
				//		char debstr[40];
				//		sprintf(debstr,"DragEnd dx %d dy %d left %d top %d",dx,dy,window->Position()->Left,window->Position()->Top);
				//		DebugPrint(debstr);
		//		handtuch->AnimatePosition(window->Position()->Left,131,handtuch->CurrentFrame(),AnimationCurveLinear);
				[handtuch animatePosition:handtuch->_position.left pTargetY:131 pTime:[handtuch currentFrame] pCurve:AnimationCurveLinear ];
				[handtuch runReverse];
			}
					
		}
		
	}
	
	inactivity_counter = 0;
	 
}


- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	
}


- (void)run {

	bubbles_wasserstand = 0;
	bubbles_temp = 10;
	bubbles_status = BUBBLES_STATUS_WAITING;

	[schaum setAnimationFrame:0 withFrame:0];
	
	[schaumA invisible];
	[schaumA setAnimationFrame:0 withFrame:0];
	[schaumB invisible];
	[schaumB setAnimationFrame:0 withFrame:0];
	[schaumC invisible];
	[schaumC setAnimationFrame:0 withFrame:0];

	[planschen setAnimationFrame:0 withFrame:0];
	[planschen setPosition:(-98) withY:24];
	[planschen runAnimationRepeat:BUBBLES_WALKRIGHT withRepeat:2];
	
	[handtuch setAnimationFrame:0 withFrame:0];
//	[handtuch setPosition:(85) withY:10];
	
}


- (void)frameTick:(NSTimer *)theTimer {
	
	if (inactivity_counter > inactivity_threshold) {
		inactivity_counter = 0;
		[self onInactivity];
	} else inactivity_counter++;
	
	[wasserhahn prepare];
	[schaum prepare];
	[schaumA prepare];
	[schaumB prepare];
	[schaumC prepare];
	[handtuch prepare];
	[planschen prepare];
	
	// [self setNeedsDisplay];
	
}


- (void)drawRect:(CGRect)rect {

	// CGContextRef context = UIGraphicsGetCurrentContext();
	
		
	[backgroundImage drawAtPoint:CGPointMake(00, 00)];


	
}

- (void)flipbookAnimationStarted:(id)theFlipbook theAnimation:(UInt16)animationId {
	

	
}

- (void)flipbookAnimationCompleted:(id)theFlipbook theAnimation:(UInt16)animationId {
	
	if (theFlipbook == planschen) {
		
			switch (animationId) {

				case BUBBLES_CONTROLCOLD:
			
					[wasserhahn runAnimation:BUBBLES_COLDWATER];
					
					break;
			
				case BUBBLES_CONTROLHOT:
					
					[wasserhahn runAnimation:BUBBLES_HOTWATER];
					
					break;
			
				case BUBBLES_JUMPOUT:
			
					bubbles_status = BUBBLES_STATUS_RUNNINGAWAY;
					[planschen runAnimationRepeat:BUBBLES_WALKLEFT withRepeat:3];
					
					break;
					
				case BUBBLES_WALKLEFT:
					bubbles_status = BUBBLES_STATUS_FINISHED;
					[self run];
					
					break;
			
				case BUBBLES_WALKRIGHT:
					
					[planschen runAnimation:BUBBLES_JOYJOY];
					break;
			
				case BUBBLES_JOYJOY:
					break;
			
				case BUBBLES_TURNRIGHTBACK:
					[planschen runAnimation:BUBBLES_CHECKWATER];
					break;
			
				case BUBBLES_CHECKWATER:

					if (bubbles_temp == 35) [planschen runAnimation:BUBBLES_CLIMBIN];
					else if (bubbles_temp < 35) [planschen runAnimation:BUBBLES_COLDSTANDING];
					else [planschen runAnimation:BUBBLES_HOTSTANDING];
					break;
			
				case BUBBLES_HOTSTANDING:
					[planschen runAnimation:BUBBLES_SITDOWN];
					break;
			
				case BUBBLES_COLDSTANDING:
					[planschen runAnimation:BUBBLES_SITDOWN];
					break;
			
				case BUBBLES_SITDOWN:
					bubbles_status = BUBBLES_STATUS_SITTING;
					break;
			
				case BUBBLES_CLIMBIN:
					bubbles_status = BUBBLES_STATUS_BATHINGLEFT;
					[planschen runAnimation:BUBBLES_BLINKLEFT];
					break;
			
				case BUBBLES_STANDUP:
					[planschen runAnimation:BUBBLES_CHECKWATER];
					break;
			
				case BUBBLES_SPLASH:
					bubbles_status = BUBBLES_STATUS_BATHINGLEFT2;
					[planschen runAnimation:BUBBLES_BLINKLEFT];
					break;

				case BUBBLES_DIVE:
					bubbles_status = BUBBLES_STATUS_BATHINGLEFT3;
					[planschen runAnimation:BUBBLES_BLINKLEFT];
					break;
			
				case BUBBLES_TURNSITTINGFRONT:
			
					bubbles_status = BUBBLES_STATUS_BATHINGFRONT;
					[planschen runAnimation:BUBBLES_SPLASHFRONT];
					[schaumC visible];
					[schaumC runAnimation:0];
					break;
			
				case BUBBLES_SPLASHFRONT:
					[planschen runAnimation:BUBBLES_BLINKFRONT];
					break;
					
				case BUBBLES_CLIMBOUT:
					bubbles_status = BUBBLES_STATUS_DRYING;
					[handtuch enable];
					[handtuch runAnimation:BUBBLES_TOWEL_DRY];
					[planschen runAnimation:BUBBLES_DRYNAKED];
					break;
			
				case BUBBLES_DRYNAKED:
					bubbles_status = BUBBLES_STATUS_OUT;
					//handtuch->OnDragStart = &Handtuch_DragStart;
					//handtuch->OnDragMove = &Handtuch_DragMove;
					//handtuch->OnDragEnd = &Handtuch_DragEnd;
					//handtuch->EnablePenCapture();
					[handtuch setAnimationFrame:BUBBLES_TOWEL_BACK withFrame:0];
					break;
				
				default:
					break;
				
		}
	
	} else if (theFlipbook == wasserhahn) {
			
			[wasserhahn setAnimationFrame:0 withFrame:0];
			
			if (
				(bubbles_status == BUBBLES_STATUS_BATHINGLEFT) ||
				(bubbles_status == BUBBLES_STATUS_BATHINGLEFT2) ||
				(bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
				)
			{
				if (!bubbles_selfcontrol)
				{
					if (bubbles_annoyance > 3) {
						
						[planschen runAnimation:BUBBLES_JUMPOUT];
						
					} else {
						
						if (animationId == BUBBLES_HOTWATER) {
							[planschen runAnimation:BUBBLES_CONTROLCOLD];
						}
						else if (animationId == BUBBLES_COLDWATER) {
							[planschen runAnimation:BUBBLES_CONTROLHOT];
						}
						bubbles_selfcontrol = 1;
						bubbles_annoyance++;
					}
				} else bubbles_selfcontrol = 0;
				
			}
			
			
			if (animationId == BUBBLES_HOTWATER) {
				bubbles_temp += 10;
				bubbles_wasserstand += 10;
			}
			else if (animationId == BUBBLES_COLDWATER) {
				bubbles_temp -= 5;
				bubbles_wasserstand += 10;
			}
			
			if (bubbles_wasserstand >= 20)
			{
				if (bubbles_status == BUBBLES_STATUS_SITTING) [planschen runAnimation:BUBBLES_STANDUP];
				else if (bubbles_status == BUBBLES_STATUS_WAITING) [planschen runAnimation:BUBBLES_TURNRIGHTBACK];
			}
		
		 
		} else if (theFlipbook == schaum) {
			 
			[schaum setAnimationFrame:0 withFrame:0];
			
			if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT)
			{
				[planschen runAnimationRepeat:BUBBLES_SPLASH withRepeat: 1];
				[schaumA visible];
			    [schaumA runAnimation:0];
			}
			  
		}
	
}

- (void)flipbookActionCommencing:(id)theFlipbook theAction:(UInt16)actionId {
	
	if (actionId == ACTION_PINKY_CLICK) {
		
		if (![planschen isRunning])
		{
			if (bubbles_status == BUBBLES_STATUS_SITTING)
			{
				if (bubbles_temp == 35) [planschen runAnimation:BUBBLES_STANDUP];
				else if (bubbles_temp < 35) [planschen runAnimation:BUBBLES_COLDSITTING];
				else [planschen runAnimation:BUBBLES_HOTSITTING];
			} 
			else if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT2)
			{
				[planschen runAnimation:BUBBLES_DIVE];
				[schaumB visible];
				[schaumB runAnimation:0];
			}
			else if (bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
			{
				[planschen runAnimation:BUBBLES_TURNSITTINGFRONT];
			}
			else if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT)
			{
				[planschen runAnimation:BUBBLES_SPLASHFRONT];
			}
		}	
	
	} else if (actionId == ACTION_HANDTUCH_CLICK) {
		
		if (![planschen isRunning])
		{
			if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT)
			{
				[schaumA runReverse];
				[schaumB runReverse];
				[schaumC runReverse];
				[schaumC invisible];
				[planschen runAnimation:BUBBLES_CLIMBOUT];
			}
		}
		
	}
	
}

- (void)onInactivity {
	
	if (![planschen isRunning])
	{
		if (
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT) ||
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT2) ||
			(bubbles_status == BUBBLES_STATUS_BATHINGLEFT3)
			) 
			[planschen runAnimation:BUBBLES_BLINKLEFT];
		
		else if (bubbles_status == BUBBLES_STATUS_BATHINGFRONT) {
			
			[planschen runAnimation:BUBBLES_BLINKFRONT];
			
		}
	}
}


- (void)flipbookPositionChange:(id)theFlipbook thePoint:( CGPoint )point {
	
}


- (void)prepareToQuit {

//	[timer invalidate];
//	[timer release];
}


- (void)dealloc {
	
	[planschen release];
	[wasserhahn release];
	[schaum release];
	[schaumA release];
	[schaumB release];
	[schaumC release];
	[handtuch release];
	[buttonBack release];	
	
	[timer invalidate];
	[timer release];
	
	[btnSchaum release];
	[btnTapHot release];
	[btnTapCold release];
	[btnPinky release];
	[btnHandtuch release];

    [super dealloc];
}


@end
