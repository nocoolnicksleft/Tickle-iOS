//
//  sidescrollerViewController.h
//  animation
//
//  Created by developer on 24.09.10.
//  Copyright 2010 TURBO D3 GMBH. All rights reserved.
//

#define degreesToRadian(x) (M_PI * (x) / 180.0)

#import <UIKit/UIKit.h>

#import "sidescrollerView.h"

@interface sidescrollerViewController : UIViewController {

	sidescrollerView * sidescroller;
	
}

@end
