//
//  rectangle.h
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "point.h"

@interface Rectangle : NSObject {
    
	@public
	
	SInt16 top;
	SInt16 left;
	SInt16 width;
	SInt16 height;
	
	bool _enabled;
	
}

- (id)initWithDimensions:(SInt16)pTop theLeft:(SInt16)pLeft theWidth:(SInt16)pWidth theHeight:(SInt16)pHeight;
- (void)enable;
- (void)disable;
- (bool)hit:(SInt16)x theY:(SInt16)y;
- (CGRect)getCGRect;

@property SInt16 top;
@property SInt16 left;
@property SInt16 width;
@property SInt16 height;

@property (readonly) SInt16 right;
@property (readonly) SInt16 bottom;
@property (readonly) bool enabled;

@end
