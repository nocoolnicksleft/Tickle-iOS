//
//  animationAppDelegate.h
//  animation
//
//  Created by Bjoern Seip on 19.09.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "pinkyView.h"
#import "pinkyViewController.h"
#import "stageViewController.h"
//#import "sidescrollerViewController.h"
#import "rotatingTabBarController.h"

@interface animationAppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate>
{
	
	UIWindow *window;
	
	UIActivityIndicatorView * activityIndicator;
	
	UIImageView * startupImage;
	
	rotatingTabBarController * tabbarController;
	
	pinkyViewController * pinkyViewController1;
	stageViewController * stageViewController1;
//	sidescrollerViewController * sidescrollerViewController1;
	
	UIViewController * currentViewController;
	
}

- (void)completeApplicationLaunch;

- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;


@property (nonatomic, retain) UIWindow *window;

@property (nonatomic, retain) pinkyViewController *viewController;

@end

