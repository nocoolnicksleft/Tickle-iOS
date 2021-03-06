//
//  pinkyImageView.h
//  animation
//
//  Created by Bjoern Seip on 21.08.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
	Tickle1,
	Tickle2,
	Tickle3,
	Tickle4
} TickleStatus;

@interface PinkyImageView : UIImageView 
{
	TickleStatus status;
	NSMutableArray * imagesTickle1;
	NSMutableArray * imagesTickle2;
	NSMutableArray * imagesTickle3;
	NSMutableArray * imagesTickle4;
	
}

- (void) loadImages;

@end
