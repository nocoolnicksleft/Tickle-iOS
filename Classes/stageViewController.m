//
//  stageViewController.m
//  animation
//
//  Created by developer on 19.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "stageViewController.h"


@implementation stageViewController

- (void)prepareToQuit {
	
	[stage prepareToQuit];
}


- (id)init {
	
	self = [super init];
	
	if (self != nil) {
		
		self.tabBarItem = [ [ UITabBarItem alloc] initWithTitle:@"Baden" image:[UIImage imageNamed:@"icon_bubbles.png"] tag:2];

		UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"badezimmer_blau.png"]];
		
		stage = [[stageView alloc] initWithFrameAndBackground:CGRectMake(32, 60, 256, 260) theBackgroundImage:image ];
		[self setStageToCenter];
		
	}
	
	return self;
	
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {

    if (interfaceOrientation == UIInterfaceOrientationPortrait) return YES;
    if (interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) return YES;
    if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft) return YES;
    if (interfaceOrientation == UIInterfaceOrientationLandscapeRight) return YES;
	return NO;
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{

	CGPoint newcenter;
	
	if ( (toInterfaceOrientation == UIInterfaceOrientationPortrait) || 
		(toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) )
		
	{
		
		newcenter = CGPointMake((320 / 2),((480 - 40)/ 2));

	} else {
		
		newcenter = CGPointMake((480 / 2),((320 - 40)/ 2));
		
	}
	
	stage.center = newcenter;
	
}


- (void)loadView {
	
	[super loadView];
	
	[self.view addSubview:stage];
	
	[self setStageToCenter];
	
	[stage run];

}

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	[self setStageToCenter];
}

- (void)setStageToCenter {

	CGPoint newcenter;
	
	UIScreen * screen = [UIScreen mainScreen];
	
	CGRect screenRect = screen.applicationFrame;
	
	UIApplication * app =  [UIApplication sharedApplication];
	
	if (UIInterfaceOrientationIsLandscape(app.statusBarOrientation)) {
		
		newcenter = CGPointMake((screenRect.size.height / 2),((screenRect.size.width - 40)/ 2));
		
	} else   {
		
		newcenter = CGPointMake((screenRect.size.width / 2),((screenRect.size.height - 40)/ 2));
		
	}
	
	stage.center = newcenter;	
	
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}


- (void)dealloc {
	[stage dealloc];
    [super dealloc];
}


@end
