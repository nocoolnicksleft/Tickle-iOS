//
//  pinkyViewController.h
//  animation
//
//  Created by developer on 22.08.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "pinkyView.h"
#import "stageView.h"




@interface pinkyViewController : UIViewController {

	PinkyImageView   *animatedImages;
		
}

- (void)setStageToCenter;

@end
