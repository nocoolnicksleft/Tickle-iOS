//
//  stageViewController.h
//  animation
//
//  Created by developer on 19.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "pinkyView.h"
#import "stageView.h"

@interface stageViewController : UIViewController {

		stageView *stage;
	
}

- (void)prepareToQuit;
- (void)setStageToCenter;

@end
