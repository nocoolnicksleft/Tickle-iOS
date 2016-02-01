//
//  flipbookAnimation.h
//  animation
//
//  Created by developer on 28.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "flipbookFrame.h"

@interface flipbookAnimation : NSObject {

@public
	
	SInt16 positionX;
	SInt16 positionY;
	SInt16 width;
	SInt16 height;
	
	NSMutableArray * frames;
	
	UInt16 frameCount;
	UInt16 delay;

}

- (id) init;
- (void) load:(NSString*)basename;
- (id) getFrame:(UInt16)frameId;


@property SInt16 positionX;
@property SInt16 positionY;
@property SInt16 width;
@property SInt16 height;
@property UInt16 frameCount;
@property UInt16 delay;
@property UInt16 currentFrame;

// @property (nonatomic,retain)	NSMutableArray * frames;

@end
