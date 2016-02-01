    //
//  sidescrollerViewController.m
//  animation
//
//  Created by developer on 24.09.10.
//  Copyright 2010 TURBO D3 GMBH. All rights reserved.
//

#import "sidescrollerViewController.h"


@implementation sidescrollerViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

- (id)init {
	
	self = [super init];
	
	if (self != nil) {
		
		self.tabBarItem = [ [ UITabBarItem alloc] initWithTitle:@"Laufen" image:[UIImage imageNamed:@"icon_sidescroller.png"] tag:1];
		
		sidescroller = [ [ sidescrollerView alloc] initWithFrame:CGRectMake(0,0,480,256)];
		
		// [sidescroller loadImages];
		
	}
	
	return self;
	
}

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	
	//sidescroller = [sidescrollerView alloc];
	
	[super loadView];
	
	[self.view addSubview:sidescroller];

}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	
    [super viewDidLoad];
	
	// UIApplication * application = [UIApplication sharedApplication];

	// application.statusBarOrientation = UIInterfaceOrientationLandscapeLeft;
	
	
}


// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
		if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft) return YES;
//		if (interfaceOrientation == UIInterfaceOrientationLandscapeRight) return YES;
		return NO;
	}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	
}



- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	[sidescroller release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	
    [super dealloc];
}


@end
