//
//  window.m
//  animation
//
//  Created by developer on 06.09.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "window.h"

const SInt16  x3table[256] = {
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,
	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	1	,	2	,	2	,
	2	,	2	,	2	,	2	,	2	,	2	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	4	,	4	,	4	,
	4	,	4	,	5	,	5	,	5	,	5	,	5	,	6	,	6	,	6	,	6	,	7	,	7	,	7	,	8	,	8	,
	8	,	8	,	9	,	9	,	9	,	10	,	10	,	10	,	11	,	11	,	11	,	12	,	12	,	13	,	13	,	14	,
	14	,	14	,	15	,	15	,	16	,	16	,	17	,	17	,	18	,	18	,	19	,	19	,	20	,	20	,	21	,	21	,
	22	,	23	,	23	,	24	,	24	,	25	,	26	,	26	,	27	,	28	,	28	,	29	,	30	,	31	,	31	,	32	,
	33	,	34	,	34	,	35	,	36	,	37	,	38	,	38	,	39	,	40	,	41	,	42	,	43	,	44	,	45	,	46	,
	47	,	47	,	48	,	49	,	50	,	51	,	53	,	54	,	55	,	56	,	57	,	58	,	59	,	60	,	61	,	63	,
	64	,	65	,	66	,	67	,	69	,	70	,	71	,	72	,	74	,	75	,	76	,	78	,	79	,	80	,	82	,	83	,
	85	,	86	,	88	,	89	,	90	,	92	,	94	,	95	,	97	,	98	,	100	,	101	,	103	,	105	,	106	,	108	,
	110	,	111	,	113	,	115	,	117	,	118	,	120	,	122	,	124	,	126	,	128	,	130	,	131	,	133	,	135	,	137	,
	139	,	141	,	143	,	145	,	147	,	150	,	152	,	154	,	156	,	158	,	160	,	162	,	165	,	167	,	169	,	172	,
	174	,	176	,	178	,	181	,	183	,	186	,	188	,	191	,	193	,	196	,	198	,	201	,	203	,	206	,	208	,	211	,
	214	,	216	,	219	,	222	,	224	,	227	,	230	,	233	,	236	,	238	,	241	,	244	,	247	,	250	,	253	,	255	,
};

@implementation Window

@synthesize textId;
@synthesize _position;

- (void) alphaEnable {

}

- (void) alphaDisable {

}

- (bool) alphaEnabled {
    return false;   
}

- (void) setAlpha:(UInt8) pValue {
    
}

- (void) display {
    
}

- (void) bufferToScreen {
    
}

- (void) fadeToWhite:(int)pTime {
    
}

- (void) fadeFromWhite:(int)pTime {
    
}

- (void) fadeToBlack:(int)pTime {
    
}

- (void) fadeFromBlack:(int)pTime {
    
}

- (bool) hitTest:(int) pX pY:(int) pY {
    return false;
}

- (void) clear {
    
}

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
    }
    return self;
}

- (void)prepare {
	if (_position_table_x)
	{
		_position->left  = _position_table_x[_animation_current];
		_position->top = _position_table_y[_animation_current];
		
		[self flushPosition];
		
		if (_animation_current == _animation_last) [self endAnimation];
		else _animation_current++;
	}
}



- (void)drawRect:(CGRect)rect {
	
	if (_visible) {
/*
		CGContextRef context = UIGraphicsGetCurrentContext(); 
		CGContextSetRGBFillColor(context, 0.5, 1.0, 0.5, 0.5); 
		CGRect rect2 = CGRectMake(0, 0, 200, 200);
		CGContextFillRect(context, rect);
*/		
	}
	
}


- (void)flushPosition {
	
	CGRect frame2 = self.frame;
	
	frame2.origin.x = _position.left;
	frame2.origin.y = _position.top;
	
	self.frame = frame2;
	
	
	//self.frame = [_position getCGRect];
}


- (void)setPosition:(SInt16)x withY:(SInt16)y {
		
	_position.top = y;
	_position.left = x;
	
	[self flushPosition];
}

- (void)setPositionDelta:(SInt16)dx withY:(SInt16)dy {

	_position.left = _position.left + dx;
	_position.top  = _position.top  + dy;
	
	[self flushPosition];
}

- (void) animatePosition:(int)pTargetX pTargetY:(int)pTargetY pTime:(int)pTime pCurve:(AnimationCurve)pCurve {
	
	if (pTime == 0) return;
	
	if (_position_table_x)
	{
		[self endAnimation];
	}
	/*NSMutableData* data = [NSMutableData dataWithLength:sizeof(int) * 100];
	 int* array = [data mutableBytes];
	 // memory is already zeroed
	 
	 // use the array
	 
	 // decide later that we need more space:
	 [data setLength:sizeof(int) * 200];
	 array = [data mutableBytes]; // re-fetch pointer in case memory needed to be copied
	 
	 // no need to free
	 // (it's done when the autoreleased object is deallocated)
	 */
	//NSMutableData* datax = [NSMutableData dataWithLength:sizeof(SInt16) * pTime];
	//_position_table_x = [datax mutableBytes];
	_position_table_x = malloc(sizeof(SInt16) * pTime);

	//NSMutableData* datay = [NSMutableData dataWithLength:sizeof(SInt16) * pTime];
	//_position_table_y = [datay mutableBytes];
	_position_table_y = malloc(sizeof(SInt16) * pTime);
	
//	_position_table_x = alloca(<#size_t #>) UInt16[pTime];
//	_position_table_y = new UInt16[pTime];
	
	int pDeltaX;
	int pDeltaY;
	int i = 0;
	
	if (pCurve == AnimationCurveLinear)
	{
		pDeltaX = ( ((_position->left - pTargetX) << 8) / pTime);
		pDeltaY = ( ((_position->top  - pTargetY) << 8) / pTime);
		
		for (i = 0; i < pTime; i++)
		{
			_position_table_x[i] = _position->left - ((i*pDeltaX) >> 8);
			_position_table_y[i] = _position->top  - ((i*pDeltaY) >> 8);
		}
		
	} 
	else if (pCurve == AnimationCurveAccelerating)
	{
		
		pDeltaX = (_position->left - pTargetX);
		pDeltaY = (_position->top  - pTargetY);
		
		int pDelta = 256 / pTime;
		
		for (i = 0; i < pTime; i++)
		{
			int  fact = x3table[(i*pDelta)];
			_position_table_x[i] = _position->left - (  (fact * pDeltaX) >> 8);
			_position_table_y[i] = _position->top  - (  (fact * pDeltaY) >> 8);
		}
		
	}
	
	else if (pCurve == AnimationCurveSlowing)
	{
		
		pDeltaX = (_position->left - pTargetX);
		pDeltaY = (_position->top  - pTargetY);
		
		int pDelta = 256 / pTime;
		
		for (i = 0; i < pTime; i++)
		{
			int  fact = x3table[(pTime-i-1)*pDelta];
			
			_position_table_x[i] = _position->left - (  ((256-fact) * pDeltaX) >> 8);
			_position_table_y[i] = _position->top  - (  ((256-fact) * pDeltaY) >> 8);
		}
	}
	else if (pCurve == AnimationCurveOvershoot)
	{
		pDeltaX = (_position->left - pTargetX);
		pDeltaY = (_position->top  - pTargetY);
		
		int pOvershootX = 0;
		int pOvershootY = 0;
		
		if (pDeltaX < 0) pOvershootX = -8;
		else if (pDeltaX > 0) pOvershootX = 8;
		if (pDeltaY < 0) pOvershootY = -8;
		else if (pDeltaY > 0) pOvershootY = 8;
		
		int pOvertime = pTime / 10;
		
		int pDelta = 256 / (pTime - pOvertime);
		for (i = 0; i < (pTime - pOvertime); i++)
		{
			int  fact = x3table[(pTime-pOvertime-i-1)*pDelta];
			_position_table_x[i] = (_position->left - pOvershootX) - (  ((256-fact) * pDeltaX) >> 8);
			_position_table_y[i] = (_position->top  - pOvershootY) - (  ((256-fact) * pDeltaY) >> 8);
			//TODO debug raus
			//sprintf(debstr,"anipos o d %d i %d dx %d dy %d ",(pTime-i),i,_position_table_x[i],_position_table_y[i]);
			//DebugPrint(debstr);
		}
		
		int interX = _position_table_x[i-1];
		int interY = _position_table_y[i-1];
		
		pDeltaX = (interX - pTargetX);
		pDeltaY = (interY - pTargetY);
		
		pDelta = 256 / pOvertime;
		for (i = i; i < pTime; i++)
		{
			int  fact = x3table[(256-i)*pDelta];
			_position_table_x[i] = interX - (  (fact * pDeltaX) >> 8);
			_position_table_y[i] = interY  - (  (fact * pDeltaY) >> 8);
		}
	}
	
	_animation_last = i-1;
	_animation_current = 0;
	
	_position_table_x[i-1] = pTargetX;
	_position_table_y[i-1] = pTargetY;
}


- (void) endAnimation {
	
	// if (OnAnimationCompleted) (*OnAnimationCompleted)();
	
	_animation_current = 0;
	_animation_last = 0;
	
	if (_position_table_x)
	{
		free(_position_table_x);
		_position_table_x = 0;
	}
	
	if (_position_table_y)
	{
		free(_position_table_y);
		_position_table_y = 0;
	}
	
}

- (void) enable {
	
	_enabled = TRUE;
	
}

- (void) disable {
	
	_enabled = FALSE;
	
}

- (bool) enabled {
	
	return _enabled;
	
}

- (void) visible {
	
	_visible = TRUE;

}

- (void) invisible {
	
	_visible = FALSE;
	
}

- (bool) isVisible {
	
	return _visible;
	
}

- (bool)hitTest:(UInt16)pX withY:(UInt16)pY {
	
	return [_position hit:pX theY:pY];
	
}

- (void)dealloc {
    [super dealloc];
}


@end
