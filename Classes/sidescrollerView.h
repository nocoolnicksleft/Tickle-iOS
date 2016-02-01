//
//  sidescrollerView.h
//  animation
//
//  Created by developer on 24.09.10.
//  Copyright 2010 TURBO D3 GMBH. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kUpdateRate (1.0 / 60.0)
#define kMoveX (-1)
#define kTopX (544)
#define kBottomX (0)


@interface sidescrollerView : UIView <UIAccelerometerDelegate> {
	
	UIImage * backgroundImage;
	UIImageView * bg;
	UIAccelerometer * accelerometer;
	int currentOffset;
	int currentDelta;

}

- (void)scrollView;
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration;

@property (nonatomic, retain) UIImageView *bg;

@end
