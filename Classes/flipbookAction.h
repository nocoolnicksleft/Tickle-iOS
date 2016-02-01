//
//  flipbookAction.h
//  animation
//
//  Created by developer on 28.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "rectangle.h"


@interface flipbookAction : NSObject {
	
	@public
	
	CGRect rectangle;
	
	int actionId;
	
	int animationId;

}

@property (nonatomic) CGRect rectangle;
@property (nonatomic) int actionId;
@property (nonatomic) int animationId;

- (id) initWithData:(CGRect)pRectangle pActionId:(int)pActionId pAnimationId:(int)pAnimationId; 
- (bool)hitTest:(CGPoint)point;

@end
