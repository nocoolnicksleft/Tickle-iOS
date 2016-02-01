//
//  flipbookAnimation.m
//  animation
//
//  Created by Bjoern Seip on 28.08.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import "flipbookAnimation.h"

@implementation flipbookAnimation

@synthesize positionX;
@synthesize positionY;
@synthesize delay;
@synthesize width;
@synthesize height;
@synthesize frameCount;
@synthesize currentFrame;
// @synthesize frames;

- (id) init {

	if (self = [super init])
	{
		
		self.positionX = 0;
		
		self.positionY = 0;
		
		self.delay = 0;
		
		self.width = 0;
		
		self.height = 0;
		
		self.frameCount = 0;
		
		self.currentFrame = 0;
		
	}
	
	return self;
	
}		

- (void) load: (NSString*) basename {
		
	NSString * name = [NSString stringWithFormat:@"%@.ani", basename];
			
	NSString * binpath = [[NSBundle mainBundle] pathForResource:name ofType:@"bin"];
	
	NSFileHandle * readFile = [NSFileHandle fileHandleForReadingAtPath:binpath];

	NSData * fileData = [readFile readDataToEndOfFile];
	
	const UInt16 *file = fileData.bytes;
	
	// UInt32 length = fileData.length;
	
	file += 2; // magic
	
	file += 2; // version 
	
	width = *file;
	
	file += 1;
	
	height = *file;
	
	file += 1;
	
	positionX = *file;
	
	file += 1;
	
	positionY = *file;
	
	file += 1;
	
	delay = *file;
	
	file += 1;
	
	frameCount = *file;
	
	file += 1;
	
	frames = [[NSMutableArray alloc] initWithCapacity:frameCount];
	
	UInt16 i;
	
	for (i = 0; i < frameCount; i++) {
		
		flipbookFrame * frame = [[flipbookFrame alloc] init];
		
		file += 1;
		
		frame->offsetX = *file;
		
		file += 1;
		
		frame->offsetY = *file;
		
		file += 1;
		
		frame->duration = *file;
		
		file += 1;
		
		name = [NSString stringWithFormat:@"%@_%d.png", basename, i];
		
		frame->image = [UIImage imageNamed:name];
		
		[frame->image retain];
		
		[frames addObject:frame];
		
		[frame release];
		
	}
	
	[readFile closeFile];
	
}


- (id) getFrame:(UInt16)frameId {
	
	return [frames objectAtIndex:frameId];
	
}

			
- (void)dealloc {
	[frames release];
	
    [super dealloc];
}
							

@end
