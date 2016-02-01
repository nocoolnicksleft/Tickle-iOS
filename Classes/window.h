//
//  window.h
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "point.h"
#import "rectangle.h"

typedef enum AnimationCurveN 
{
	AnimationCurveLinear,
	AnimationCurveSlowing,
	AnimationCurveAccelerating,
	AnimationCurveOvershoot
} AnimationCurve;


@interface Window : UIView {

	@public
	
	bool _enabled;
	
	bool _valid;
	bool _visible;

	Rectangle * _position;
	Rectangle * _inner_rect;

	
	bool _alpha_enabled;
	UInt8 _alpha_value;
	
	UInt16 _back_color;
	UInt16 _fore_color;
	
	UInt16 _frame_width;
	UInt16 _frame_color;
	
	UInt16 _animation_last;
	UInt16 _animation_current;
	
	int _animation_type;
	UInt16 _animation_step;
	int _animation_delay;
	
	SInt16 * _position_table_x;
	SInt16 * _position_table_y;
	
	bool _pen_capture;

	char * textId;
}

- (void)drawRect:(CGRect)rect;

- (bool)hitTest:(UInt16)pX withY:(UInt16)pY;

- (void)flushPosition;

- (void)setPosition:(SInt16)x withY:(SInt16)y;
- (void)setPositionDelta:(SInt16)dx withY:(SInt16)dy;

- (void) enable;
- (void) disable;
- (bool) enabled;

- (void) visible;
- (void) invisible;
- (bool) isVisible;

- (void) alphaEnable;
- (void) alphaDisable;
- (bool) alphaEnabled;
- (void) setAlpha:(UInt8) pValue;

- (void) clear;
- (void) prepare;
- (void) display;
- (void) bufferToScreen;

- (void) endAnimation;

- (void) animatePosition:(int)pTargetX pTargetY:(int)pTargetY pTime:(int)pTime pCurve:(AnimationCurve)pCurve;

- (void) fadeToWhite:(int)pTime;
- (void) fadeFromWhite:(int)pTime;
- (void) fadeToBlack:(int)pTime;
- (void) fadeFromBlack:(int)pTime;

- (bool) hitTest:(int) pX pY:(int) pY;

@property char * textId;
@property (copy)Rectangle * _position;
/*
 
Bitmap * _buffer;
Bitmap * _parent_buffer;

multimap<int, Window*> _window;

static Window * _pen_capture_target;

GenericEvent OnAnimationCompleted;

*/

/*
void AddWindow(Window * pWindow, int zOrder);
void RemoveWindow(Window * pWindow);

void EnablePenCapture();
void DisablePenCapture();
bool PenCapture();

void SetParent(Bitmap * pParent);
Bitmap * GetBuffer();

 
 Rectangle * Position();

 */


/*
virtual void MsgPenDown(int pX, int pY);
virtual void MsgPenUp(int pX, int pY);
virtual void MsgPenMove(int pX, int pY);

WindowPositionEvent OnMsgPenDown;
WindowPositionEvent OnMsgPenMove;
WindowPositionEvent OnMsgPenUp;

virtual void DragStart(int pX, int pY);
virtual void DragMove(int pX, int pY);
virtual void DragEnd(int pX, int pY);

WindowPositionEvent OnDragStart;
WindowPositionEvent OnDragMove;
WindowPositionEvent OnDragEnd;

char * Text();
void Text(char * text);

*/



@end
