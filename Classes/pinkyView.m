//
//  pinkyImageView.m
//  animation
//
//  Created by developer on 21.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "pinkyView.h"

#define IMAGE_COUNT_1       21
#define IMAGE_COUNT_2       12
#define IMAGE_COUNT_3 	    20	
#define IMAGE_COUNT_4       43

@implementation PinkyImageView

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation
{

	return YES;
}


- (void)loadImages
{
	// Set Default Image
	self.image = [UIImage imageNamed:[NSString stringWithFormat:@"bigpinky_kitzel_0_0.png"]];
	
	// Enable Touch Messages
	self.userInteractionEnabled = YES;
	
	// One cycle through all the images takes 1.5 seconds
	self.animationDuration = 1.0;
	
	// Do not repeat
	self.animationRepeatCount = 1;
	
	// Array to hold jpg images
	imagesTickle1 = [[NSMutableArray alloc] initWithCapacity:IMAGE_COUNT_1];
	
	// Build array of images, cycling through image names
	for (int i = 0; i < IMAGE_COUNT_1; i++)
		[imagesTickle1 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"bigpinky_kitzel_0_%d.png", i]]];
	
    
	// Array to hold jpg images
	imagesTickle2 = [[NSMutableArray alloc] initWithCapacity:IMAGE_COUNT_2];
	
	// Build array of images, cycling through image names
	for (int i = 0; i < IMAGE_COUNT_2; i++)
		[imagesTickle2 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"bigpinky_kitzel_1_%d.png", i]]];
	
    
	// Array to hold jpg images
	imagesTickle3 = [[NSMutableArray alloc] initWithCapacity:IMAGE_COUNT_3];
	
	// Build array of images, cycling through image names
	for (int i = 0; i < IMAGE_COUNT_3; i++)
		[imagesTickle3 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"bigpinky_kitzel_2_%d.png", i]]];
	
    
	// Array to hold jpg images
	imagesTickle4 = [[NSMutableArray alloc] initWithCapacity:IMAGE_COUNT_4];
	
	// Build array of images, cycling through image names
	for (int i = 0; i < IMAGE_COUNT_4; i++)
		[imagesTickle4 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"bigpinky_kitzel_3_%d.png", i]]];
	
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	
	UITouch *t = [[touches allObjects] objectAtIndex:0];
    
	CGPoint touchPos = [t locationInView:t.view];
		
	if (touchPos.y < 30) status = Tickle2;
	else if (touchPos.y > 90) status = Tickle3;
	else {
		if (touchPos.x < 30) {
			status = Tickle4;
		} else {
			status = Tickle1;
		}

	}

	if (status == Tickle2) {
		
		self.animationImages = [NSArray arrayWithArray:imagesTickle2];
		self.animationDuration = IMAGE_COUNT_2*0.04;
		
	} else if (status == Tickle3) {
		
		self.animationImages = [NSArray arrayWithArray:imagesTickle3];
		self.animationDuration = IMAGE_COUNT_3*0.04;
		
	} else if (status == Tickle4) {
		
		self.animationImages = [NSArray arrayWithArray:imagesTickle4];
		self.animationDuration = IMAGE_COUNT_4*0.04;
		
	} else { // Tickle 1
		
		self.animationImages = [NSArray arrayWithArray:imagesTickle1];
		self.animationDuration = IMAGE_COUNT_1*0.04;
		
		
	}
	
	self.animationRepeatCount = 1;
	
	[self startAnimating];
	
	
}

- (void)dealloc 
{
	[imagesTickle1 release];
	[imagesTickle2 release];
	[imagesTickle3 release];
	[imagesTickle4 release];
	
	[super dealloc];
}



@end
