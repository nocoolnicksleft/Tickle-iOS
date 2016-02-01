//
//  flipbookAction.m
//  animation
//
//  Created by Bjoern Seip on 28.08.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import "flipbookAction.h"


@implementation flipbookAction

@synthesize rectangle;
@synthesize animationId;
@synthesize actionId;

- (id)initWithData:(CGRect)pRectangle pActionId:(int)pActionId pAnimationId:(int)pAnimationId {
	
	if (self = [super init])
	{
		rectangle = pRectangle;
		actionId = pActionId;
		animationId = pAnimationId;
		
	}
	
	return self;
		
}

- (bool)hitTest:(CGPoint)point {
	
	return CGRectContainsPoint(rectangle,point);

}

- (void)dealloc {
    [super dealloc];
}


@end
