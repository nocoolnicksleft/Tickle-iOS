//
//  animationAppDelegate.m
//  animation
//
//  Created by Bjoern Seip on 19.09.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import "animationAppDelegate.h"
#import "pinkyViewController.h"
#import "stageViewController.h"

@implementation animationAppDelegate

@synthesize window;

@synthesize viewController;

- (void)applicationWillTerminate:(UIApplication *)application {

	[stageViewController1 prepareToQuit];
	
}

- (void)applicationDidEnterBackground:(UIApplication *)application {

//	[stageViewController1 prepareToQuit];

}

- (void)applicationWillResignActive:(UIApplication *)application {
	
	[stageViewController1 prepareToQuit];

}


- (void)applicationDidFinishLaunching:(UIApplication *)application
{
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	window.backgroundColor = [UIColor blackColor];

	UIApplication * myApp = [UIApplication sharedApplication];
	[myApp setStatusBarHidden:YES withAnimation:YES];
	myApp.applicationIconBadgeNumber = 0;
	
    UIViewController* rootViewController = [[UIViewController alloc] init];
    [self.window setRootViewController:rootViewController];
    
	startupImage = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"Default.png"]]];
	
	[window addSubview:startupImage];
	
	activityIndicator = [ [UIActivityIndicatorView alloc] initWithFrame:CGRectMake(140, 300, 40, 40)];
	activityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
	[activityIndicator startAnimating];
	[window addSubview:activityIndicator];	
	
	[window makeKeyAndVisible];
    
	[self performSelector:@selector(completeApplicationLaunch) withObject:nil afterDelay:0];

}



- (void)completeApplicationLaunch {

    pinkyViewController1 = [ [ pinkyViewController alloc] init ];
    stageViewController1 = [ [ stageViewController alloc] init ];
    
    
    NSMutableArray * viewControllers = [ [ NSMutableArray alloc] init];
    [viewControllers addObject:pinkyViewController1];
    [viewControllers addObject:stageViewController1];

    
    tabbarController = [ [ rotatingTabBarController alloc] init];
    tabbarController.viewControllers = viewControllers;
    tabbarController.delegate = self;
    
    self.window.rootViewController = tabbarController;
 	
	[activityIndicator stopAnimating];
	[activityIndicator removeFromSuperview];
	[activityIndicator release];
	[startupImage removeFromSuperview];
	[startupImage release];
	
	[window addSubview:tabbarController.view];
    
}

- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)activeViewController {
	
	currentViewController = activeViewController;
	
	if (activeViewController == pinkyViewController1) {
				
	} else if (activeViewController == stageViewController1) {
		
	}
		/*
	} else if (activeViewController == sidescrollerViewController1) {
		
		
		UIApplication * application = [UIApplication sharedApplication];
		
		application.statusBarOrientation = UIInterfaceOrientationLandscapeLeft;
		
	} */
	
}



- (void)dealloc 
{
	[pinkyViewController1 release];
	[stageViewController1 release];
//	[sidescrollerViewController1 release];
	
	[tabbarController release];
	
	[window release];
	[super dealloc];
}

@end
