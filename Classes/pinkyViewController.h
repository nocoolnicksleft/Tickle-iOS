//
//  pinkyViewController.h
//  animation
//
//  Created by Bjoern Seip on 19.09.10.
//  Copyright 2010 Bjoern Seip. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "pinkyView.h"
#import "stageView.h"




@interface pinkyViewController : UIViewController {

	PinkyImageView   *animatedImages;
		
}

- (void)setStageToCenter;

@end
