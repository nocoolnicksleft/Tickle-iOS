//
//  flipbook.h
//  animation
//
//  Created by developer on 25.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioServices.h>

#import "point.h"
#import "rectangle.h"
#import "window.h"
#import "flipbookAction.h"
#import "flipbookAnimation.h"
#import "flipbookFrame.h"

@protocol flipbookEventDelegate <NSObject>

@optional

- (void)flipbookAnimationStarted:(id)theFlipbook theAnimation:(UInt16)animationId;
- (void)flipbookAnimationCompleted:(id)theFlipbook theAnimation:(UInt16)animationId;
- (void)flipbookActionCommencing:(id)theFlipbook theAction:(UInt16)actionId;
- (void)flipbookPositionChange:(id)theFlipbook thePoint:(CGPoint)point;

@end



@interface flipbook : Window {

	
	UInt16 _animation_id;
	UInt16 _animation_frame;
	UInt16 _animation_frame_count;
	
	UInt16 _animation_repeat;
	
	bool _running;
	bool _reverse;
	
	bool tapAlphaFilter;
	
	UInt16 _delay;
	UInt16 _timeout;
	
	UInt16 _lastAnimationId;
	
	NSMutableArray * _actions;

	NSMutableDictionary * _animations;
	

	UIImage * _current_image;
	
	id<flipbookEventDelegate> delegate;
	
}

- (id)init;

- (id)initWithFrameAndName:(CGRect)pFrame withName:(char *)pName;

- (void)drawRect:(CGRect)rect;

- (void)runAnimation:(UInt16)animationId;

- (void)runAnimationRepeat:(UInt16)animationId  withRepeat:(UInt16) repeatCount;

- (void)runReverse;

- (void)setAnimationFrame:(UInt16)animationId withFrame:(UInt16) frameId;

- (void)setAnimationFrameNoPosition:(UInt16)animationId withFrame:(UInt16) frameId;

- (UInt16)addAction:(CGRect)rect withActionId:(int)actionId withAnimationId:(int)animationId;

- (UInt16)addAnimation:(UInt16)animationId withCount:(UInt16)pCount withDelay:(UInt16)delay withName:(NSString *)pName;

- (UInt16)addSound:(UInt16)animationId withFrame:(UInt16)pFrameId withName:(NSString *)pName;

- (UInt16)loadAnimation:(UInt16)animationId withName:(NSString *)pName;

- (UInt16)addTransformation:(UInt16)animationId withStepCount:(UInt16)stepCount withXTable:(NSArray *)xTable withYTable:(NSArray *)yTable;

- (void)loadCurrentImage;

- (UInt16)currentFrame;

- (void)prepare;

- (void)tap:(UInt16)pX withY:(UInt16)pY;

- (void)lift:(UInt16)pX withY:(UInt16)pY;

- (void)drag:(UInt16)pX withY:(UInt16)pY;

- (bool)isRunning;

- (bool)executeTap:(CGPoint)touchPos;

@property (assign) id<flipbookEventDelegate> delegate;
@property bool tapAlphaFilter;
@end

