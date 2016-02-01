//
//  flipbook.m
//  animation
//
//  Created by developer on 25.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "flipbook.h"


@implementation flipbook

@synthesize delegate;
@synthesize tapAlphaFilter;

/************************************************/
/**
 *	Regular Init
 *
 */
- (id)init {
	
	if (self = [super init])
	{
		
		_animation_id = 0;
		_animation_frame = 0;
		_animation_frame_count = 0;
		
		_animation_repeat = 0;
		
		_running = FALSE;
		_reverse = FALSE;
		
		_delay = 0;
		_timeout = 0;
		
		_lastAnimationId = 0;
		
		_actions = [[NSMutableArray alloc] initWithCapacity:10];
		_animations = [[NSMutableDictionary alloc] initWithCapacity:10];;
		
		delegate = 0;
		
	}
		
		
	return self;
	
	
}

/**
 *  Full Init setting frame and text id 
 */
- (id)initWithFrameAndName:(CGRect)frame withName:(char *)pName {
	
	if ((self = [super initWithFrame:frame])) {	
		
		_animation_id = 0;
		_animation_frame = 0;
		_animation_frame_count = 0;
		
		_animation_repeat = 0;
		
		_running = FALSE;
		_reverse = FALSE;
		
		_delay = 0;
		_timeout = 0;
		
		_lastAnimationId = 0;
		
		_actions = [[NSMutableArray alloc] initWithCapacity:10];
		_animations = [[NSMutableDictionary alloc] initWithCapacity:10];;
		
		delegate = 0;

		textId = pName;
		
		_position = [[Rectangle alloc] initWithDimensions:0 theLeft:0 theWidth:0 theHeight:0];
		
		self.opaque = FALSE;
		
		self.userInteractionEnabled = FALSE;
		
		
		// ***********************************************************************
		// ***********************************************************************
		// ***********************************************************************
		// TODO Dictionary und Enumerator einbauen (AnimationId -> Animation *)
		NSEnumerator *enumerator = [_animations keyEnumerator];
		
		for(NSString *aKey in enumerator){
			
			NSLog(@"%@",aKey);
			NSLog(@"%@",[[_animations valueForKey:aKey] string]); //made up method
			
		}
		// ***********************************************************************
		// ***********************************************************************

		
	}
		
	return self;
	
}
				

/**
 * Drawing routine
 */
- (void)drawRect:(CGRect)rect {
	
	[super drawRect:rect];

	if (_visible) {
	//	[self loadCurrentImage];
		[_current_image drawAtPoint:CGPointMake(0, 0)]; 
/*
		NSEnumerator *enumerator = [_actions objectEnumerator];
		flipbookAction * action;
		
		while (action = [enumerator nextObject]) {
		
			CGContextRef context = UIGraphicsGetCurrentContext(); 
			CGContextSetRGBFillColor(context, 1.0, 0.0, 0.0, 1.0); 
			CGContextStrokeRectWithWidth(context,action->rectangle,1);
			
		}
 */
	}
	
}

/**
 * Start animation sequence. 
 *
 */
- (void)runAnimation:(UInt16)animationId {
	
	if ([_animations count] > 0) {

		if (!_running) {
				_reverse = FALSE;
				_animation_id = animationId;
				flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:animationId] stringValue]];
				_animation_frame = 0;
				_animation_frame_count = currentAnimation->frameCount;
				_valid = FALSE;
				_delay = currentAnimation->delay;
				_timeout = _delay;
				_running = TRUE;
				
				if ((currentAnimation->positionX != 0) || (currentAnimation->positionY != 0)) {
					_position->left = currentAnimation->positionX;
					_position->top = currentAnimation->positionY;
					[self flushPosition];
				}
			    
				
				if( [delegate respondsToSelector:@selector(flipbookAnimationStarted)] ) {
					
					[delegate flipbookAnimationStarted:self  theAnimation:animationId];
					
				}

		}
	}
	
	
}


/**
 * Start animation sequence, run multiple times
 */
- (void)runAnimationRepeat:(UInt16)animationId  withRepeat:(UInt16) repeatCount {
	
	_animation_repeat = repeatCount;
	
	[self runAnimation:animationId];
	
}

/**
 * Start current animation sequence running backwards
 */
- (void)runReverse {
	
	if (!_running) {
		
		_reverse = TRUE;
		
		// _valid = FALSE;
		
		_timeout = _delay;
		
		_running = TRUE;
		
		[self prepare];
	}
	
}


- (void)setAnimationFrame:(UInt16)animationId withFrame:(UInt16) frameId {
	_animation_id = animationId;
	_animation_frame = frameId;
	flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:_animation_id] stringValue]];
	_animation_frame_count = currentAnimation->frameCount;
	_valid = FALSE;
	_running = FALSE;

	if ( (currentAnimation->positionX) || (currentAnimation->positionY) ) {
		_position->left = currentAnimation->positionX;
		_position->top = currentAnimation->positionY;
		[self flushPosition];		
	}
	
	[self prepare];
}

- (void)setAnimationFrameNoPosition:(UInt16)animationId withFrame:(UInt16) frameId {
	
	_animation_id = animationId;
	_animation_frame = frameId;
	flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:_animation_id] stringValue]];
	_animation_frame_count = currentAnimation.frameCount;
	_valid = FALSE;
	_running = FALSE;
	[self prepare];
	
}

- (UInt16)addAction:(CGRect)rect withActionId:(int)actionId withAnimationId:(int)animationId {
	
	// Enable Touch Messages
	// self.userInteractionEnabled = YES;
	
	flipbookAction * newaction = [[flipbookAction alloc] initWithData:rect pActionId:actionId pAnimationId:animationId];
	
	[_actions addObject:newaction];
								  
	[newaction release];								  
	
	return actionId;
	
}

- (bool)executeTap:(CGPoint)touchPos {
	
	if (_enabled) {
				
		touchPos = CGPointMake(touchPos.x - self.frame.origin.x, touchPos.y - self.frame.origin.y);
		
		if (tapAlphaFilter) {
			
			flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:_animation_id] stringValue]];
			
			flipbookFrame * currentframe = [currentAnimation getFrame:_animation_frame];
			
			UIColor * color = [currentframe getPixelColorAtLocation:touchPos];
			
			float c2af = CGColorGetAlpha(color.CGColor);
			
			if (c2af == 0) {
				
				return false;
				
			}
				
		}
		
		NSEnumerator *enumerator = [_actions objectEnumerator];
		
		flipbookAction * action;

		while (action = [enumerator nextObject]) {
			
			if ([action hitTest:touchPos]) {
				
				if (action->animationId > -1) {
					[self runAnimation:action->animationId];
				} 
				
				if (action->actionId) {
					
					//	if( [self.delegate respondsToSelector:@selector(flipbookActionCommencing:)] ) {
					
				   [self.delegate flipbookActionCommencing:self theAction:action->actionId];
					
					//	}
					
				}
				
				return true;
				
				
			}
			
		}
		
	}
	
	return FALSE;

}



- (UInt16)addAnimation:(UInt16)animationId withCount:(UInt16)pCount withDelay:(UInt16)delay withName:(NSString *)pName {
	
	return 0;
	
}

- (UInt16)addSound:(UInt16)animationId withFrame:(UInt16)pFrameId withName:(NSString *)pName {
	
	NSString * binpath = [[NSBundle mainBundle] pathForResource:pName ofType:@"aif"];
	
	//declare a system sound id
	SystemSoundID soundID;
	
	//Get a URL for the sound file
	NSURL *filePath = [NSURL fileURLWithPath:binpath isDirectory:NO];
	
	//Use audio sevices to create the sound
	AudioServicesCreateSystemSoundID((CFURLRef)filePath, &soundID);
	 
	flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:animationId] stringValue]];
	
	flipbookFrame * currentframe = [currentAnimation getFrame:pFrameId];
	
	currentframe->soundId = soundID;
	
	//Use audio services to play the sound
	//AudioServicesPlaySystemSound(soundID);
	
	return 0;
	
}
	

- (UInt16)loadAnimation:(UInt16)animationId withName:(NSString *)pName {
	
	flipbookAnimation * newAnimation = [[flipbookAnimation alloc] init];
	
	[newAnimation load:pName];
	
	[_animations setValue:newAnimation forKey:[[NSNumber numberWithInt:animationId] stringValue]];
	
	[newAnimation release];
	
	return animationId;
	
}

- (UInt16)addTransformation:(UInt16)animationId withStepCount:(UInt16)stepCount withXTable:(NSArray *)xTable withYTable:(NSArray *)yTable {
	
	return 0;
	
}

/**
 * Load current image to secondary buffer or write to screen
 *
 */
- (void)loadCurrentImage {
	
	flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:_animation_id] stringValue]];
	
	flipbookFrame * currentframe = [currentAnimation getFrame:_animation_frame];
	
	_current_image = currentframe->image;
}

/**
 * Return currently active frame 
 */
- (UInt16)currentFrame {
	
	return _animation_frame;
	
}

/**
 * Prepare position and frame data for next display.
 * Must be called exactly once before each frame refresh (e.g. every 40ms for 25fps)
 */
- (void)prepare {
	
	[super prepare];

	if (_running) {

		if (!_timeout) {
			
			_timeout = _delay;
			
			if (_reverse) {
				[self loadCurrentImage];
				
				if (_animation_frame) {
					--_animation_frame;
				} else {
					_running = FALSE;
					
					// TODO: Warum funktioniert die Abfrage nicht??
					//if( [delegate respondsToSelector:@selector(flipbookAnimationCompleted)] ) {
						
						[delegate flipbookAnimationCompleted:self theAnimation:_animation_id];
						
					//}
					
				}

			} else {
				
				flipbookAnimation * currentAnimation = [_animations objectForKey:[[NSNumber numberWithInt:_animation_id] stringValue]];
				
				flipbookFrame * currentframe = [currentAnimation getFrame:_animation_frame];
				
				if (currentframe->soundId) {
					
					AudioServicesPlaySystemSound(currentframe->soundId);
				}
				
				// TODO: Implement Transformations
				
				
				_position.left += currentframe->offsetX;
				_position.top += currentframe->offsetY;
				
			    [self flushPosition];
				
				[self loadCurrentImage];
				
				if (_animation_frame < (_animation_frame_count - 1) ) {
					
					++_animation_frame;
					
				} else {
					
					_running = FALSE;
					
					if (_animation_repeat) {
						
						--_animation_repeat;
						
						[self runAnimation:_animation_id];
						
					} else {
						
						// TODO: Warum funktioniert die Abfrage nicht??
						
					//	if( [self.delegate respondsToSelector:@selector(flipbookAnimationCompleted:)] ) {
							
							[self.delegate flipbookAnimationCompleted:self theAnimation:_animation_id];
							
					//	}
						
					}
				}

				
				
			}

		} else {
			
			--_timeout;
			
		}
		
	} else {
		
	
		 if (!_valid) {
			
			[self loadCurrentImage];
			
			_valid = TRUE;
			
		 }
		
	}
	
	[self setNeedsDisplay];

}

- (bool)isRunning {

	return _running;
	
}


- (void)tap:(UInt16)pX withY:(UInt16)pY {
	
}

- (void)lift:(UInt16)pX withY:(UInt16)pY {
	
}


- (void)drag:(UInt16)pX withY:(UInt16)pY {
	
}





- (void)dealloc {
	[_animations release];
	[_actions release];
	[_position release];
	
    [super dealloc];
}



@end
