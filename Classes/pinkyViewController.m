    //
//  pinkyViewController.m
//  animation
//
//  Created by developer on 22.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "pinkyViewController.h"

#define IMAGE_WIDTH       96
#define IMAGE_HEIGHT      120

#define TAB_BAR_HEIGHT 40
#define SCREEN_HEIGHT     480
#define SCREEN_WIDTH      320

@implementation pinkyViewController

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
		
		self.tabBarItem = [ [ UITabBarItem alloc] initWithTitle:@"Kitzeln" image:[UIImage imageNamed:@"icon_kitzel.png"] tag:1];
	
		animatedImages = [[PinkyImageView alloc] 
						  initWithFrame:CGRectMake(
												   (SCREEN_WIDTH / 2) - (IMAGE_WIDTH / 2), 
												   (SCREEN_HEIGHT / 2) - (IMAGE_HEIGHT / 2) - TAB_BAR_HEIGHT,
												   IMAGE_WIDTH, IMAGE_HEIGHT)];
		
		[animatedImages loadImages];
		
	}
	
	return self;
	
}


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	
	[super loadView];

	[self.view addSubview:animatedImages];
	
	[self setStageToCenter];
	
}


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {

    if (interfaceOrientation == UIInterfaceOrientationPortrait) return YES;
    if (interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) return YES;
    if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft) return YES;
    if (interfaceOrientation == UIInterfaceOrientationLandscapeRight) return YES;
	
	return NO;
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
	
	CGPoint newcenter;
	
	if ( UIInterfaceOrientationIsPortrait(toInterfaceOrientation)) {
		
		newcenter = CGPointMake((320 / 2),((480 - 40)/ 2));
		
	} else {
		
		newcenter = CGPointMake((480 / 2),((320 - 40)/ 2));
		
	}
	
	animatedImages.center = newcenter;
	
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
	
	animatedImages.center = newcenter;
	
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	
//	UITouch *t = [[touches allObjects] objectAtIndex:0];
    
//	CGPoint touchPos = [t locationInView:t.view];
	
}


- (void)dealloc {
	[animatedImages release];
	
    [super dealloc];
}


@end
