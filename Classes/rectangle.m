//
//  rectangle.m
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "rectangle.h"


@implementation Rectangle

@synthesize top;
@synthesize left;
@synthesize width;
@synthesize height;


- (id)initWithDimensions:(SInt16)pTop theLeft:(SInt16)pLeft theWidth:(SInt16)pWidth theHeight:(SInt16)pHeight {
	
	if (self = [super init])
	{
		
		top = pTop;
		left = pLeft;
		width = pWidth;
		height = pHeight;
		
		_enabled = TRUE;
			
	}
	
	return self;
	
}


- (void)dealloc {
	
    [super dealloc];
	
}


- (void)enable {
	
	_enabled = TRUE;
	
}

- (void)disable {
	
	_enabled = FALSE;
	
}

- (bool)enabled {
	
	return _enabled;
	
}

- (bool)hit:(SInt16)x theY:(SInt16)y {
	
	if ((x >= left) && (x <= self.right)) {
	
		if ((y >= top) && (y <= self.bottom)) {
		
			return TRUE;
			
		}
	}
	
	return FALSE;
	
}

- (SInt16)bottom {
	
	return (top + height);
	
}

- (SInt16)right {
	
	return (left + width);
	
}

- (CGRect)getCGRect {

	return CGRectMake(left, top, width, height);
}




@end
