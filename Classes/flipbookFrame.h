//
//  flipbookFrame.h
//  animation
//
//  Created by Bjoern Seip on 28.08.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioServices.h>

@interface flipbookFrame : NSObject {
	
@public
	SInt16 offsetX;
	SInt16 offsetY;
	
	UInt16 duration;
	
	UIImage * image;
	
	SystemSoundID soundId;
	

}

- (id) init;
- (CGContextRef) createARGBBitmapContextFromImage:(CGImageRef) inImage;
- (UIColor*) getPixelColorAtLocation:(CGPoint)point;

@property SInt16 offsetX;
@property SInt16 offsetY;
@property UInt16 duration;
@property (nonatomic,retain) UIImage * image;
@property SystemSoundID soundId;

@end
