//
//  point.h
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface point : NSObject {
		
	@public
	
	SInt16 x;
	SInt16 y;

}

- (id)initWithDimensions:(SInt16)pX theY:(SInt16)pY;

@property SInt16 x;
@property SInt16 y;

@end
