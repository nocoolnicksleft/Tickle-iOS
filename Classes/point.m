//
//  point.m
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "point.h"


@implementation point

@synthesize x;
@synthesize y;

- (id)initWithDimensions:(SInt16)pX theY:(SInt16)pY {

	if (self = [super init])
	{

		x = pX;
		y = pY;

	}

	return self;

}

@end
