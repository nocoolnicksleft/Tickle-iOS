//
//  sidescrollerView.m
//  animation
//
//  Created by developer on 24.09.10.
//  Copyright 2010 TURBO D3 GMBH. All rights reserved.
//

#import "sidescrollerView.h"


@implementation sidescrollerView

@synthesize bg;

- (id)initWithFrame:(CGRect)frame {
	
    if ((self = [super initWithFrame:frame])) {
		
	//	backgroundImage = [UIImage imageNamed:[NSString stringWithFormat:@"wueste-1024-256.png"]];
		
		self.bg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"wueste-1024-256.png"]];
		
		[self addSubview:self.bg];
		
		self.bg.center = CGPointMake(kTopX, self.bg.center.y);
		
		currentDelta = -1;
		currentOffset = 0;
		
		accelerometer = [UIAccelerometer sharedAccelerometer];
		accelerometer.updateInterval = 0.5;
		accelerometer.delegate = self;
		
		[NSTimer scheduledTimerWithTimeInterval:kUpdateRate target:self selector:@selector(scrollView) userInfo:nil repeats:YES];
		
    }
	
    return self;
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
/*
- (void)drawRect:(CGRect)rect {
	
	[backgroundImage drawAtPoint:CGPointMake(00, 00)];

}
*/

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
// Y -0.45 bis 0.45
	NSLog(@"acc x %f y %f z %f",acceleration.x,acceleration.y,acceleration.z);
	
}

-(void)scrollView; {
		
	float oldX = self.bg.center.x + kMoveX;
	
	float newX = oldX;
	
	if (oldX <= kBottomX) {
		newX = kTopX;
	}
	
	self.bg.center = CGPointMake(newX, self.bg.center.y);
	
}


- (void)dealloc {
	[bg release];
	[backgroundImage release];
    [super dealloc];
}


@end
