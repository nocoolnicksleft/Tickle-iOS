#pragma once

#include "common.h"
#include "window.h"
#include "rectangle.h"


class Flipbook;

/******************************************************************************/
/* Delegates                                                                  */
/******************************************************************************/
typedef void (*FlipbookGenericEvent) (Flipbook * flipbook);
typedef void (*FlipbookActionEvent) (Flipbook * flipbook, uint16 action);
typedef void (*FlipbookPositionEvent) (Flipbook * flipbook, uint16 x, uint16 y);
typedef void (*FlipbookPositionChangeEvent) (Flipbook * flipbook, Point * position);
typedef void (*FlipbookAnimationEvent) (Flipbook * flipbook, uint16 animationId);


/******************************************************************************/
/* FlipbookFrame                                                              */
/******************************************************************************/
class FlipbookFrame
{
public:
	int16 OffsetX;
	int16 OffsetY;
	uint16 Delay;
	uint16 * Imagedata;
	uint8 * Alphadata;
	uint16 * Sounddata;
	uint32 Soundsize;

	FlipbookFrame();

	FlipbookFrame(uint16 offsetX, uint16 offsetY, uint16 delay);
	
	~FlipbookFrame()
	{
		if (Sounddata) delete [] Sounddata;
		Sounddata = 0;
	}
};

typedef FlipbookFrame * PFlipbookFrame;


/******************************************************************************/
/* FlipbookAnimation                                                          */
/******************************************************************************/
class FlipbookAnimation
{
public:
	int * TransformationX;
	int * TransformationY;

	int16 PositionX;
	int16 PositionY;
	int16 Width;
	int16 Height;

	vector<FlipbookFrame *> Frames;
	
public:
	uint16 FileId;
	uint16 FrameCount;
	int16 Delay;
	uint16 * Table;
	uint16 * AlphaTable;

public:
	FlipbookAnimation(uint16 pFileId, uint16 pPhaseCount, uint16 pDelay)
	{
		FileId = pFileId;
		FrameCount = pPhaseCount;
		Delay = pDelay;
		Table = 0;
		PositionX = 0;
		PositionY = 0;
		Width = 0;
		Height = 0;
		AlphaTable = 0;
		TransformationX = 0;
		TransformationY = 0;
	}

	~FlipbookAnimation()
	{
		
		for_each(Frames.begin(), Frames.end(), free_ptr<FlipbookFrame>());
		/*
		vector <FlipbookFrame*>::iterator frame_iterator;
		for ( frame_iterator = Frames.begin( ); frame_iterator != Frames.end( ); frame_iterator++ )
			delete *frame_iterator;
		*/	

	}

	FlipbookAnimation(uint16 pAnimationId, uint16 pFileId, uint16 * pTable, uint16 * pAlphaTable);

	void Load();

};


/******************************************************************************/
/* FlipbookAction                                                             */
/******************************************************************************/
class FlipbookAction
{
public:
	Rectangle * Rect;
	int16 ActionId;
	GenericEvent OnTrigger;

public:
	FlipbookAction(Rectangle * pRect, GenericEvent pEvent, uint16 pAnimationId)
	{
		Rect = pRect;
		ActionId = pAnimationId;
		OnTrigger = pEvent;
	};

};


/******************************************************************************/
/* Flipbook                                                                   */
/******************************************************************************/
class Flipbook : public Window
{
protected:
	
	uint16 _animation_id;
	uint16 _animation_phase;
	uint16 _animation_phase_count;
	uint16 _animation_repeat;

	bool _running;
	bool _reverse;

	uint16 _delay;
	uint16 _timeout;

	vector<FlipbookAction*> _actions;
	vector<FlipbookAnimation*> _animations;

public:
	Flipbook(Rectangle * pRect, char * textid);

public:
	virtual ~Flipbook();

public:
	FlipbookAnimationEvent OnAnimationStarted;
	FlipbookAnimationEvent OnAnimationCompleted;
	FlipbookPositionChangeEvent OnFramePrepare;
	FlipbookActionEvent OnAction;

	bool IsRunning();

	void Run(
		uint16 pAnimationId);

	void Run(
		uint16 pAnimationId, 
		uint16 pRepeat);

	void RunReverse();

	void Set(
		uint16 pAnimationId, 
		uint16 pPhaseId);

	void SetNoPosition(
		uint16 pAnimationId, 
		uint16 pPhaseId);

	void AddAction(
		Rectangle * pRect, 
		GenericEvent pEvent, 
		uint16 pAnimationId);

	void AddAnimation(
		int pAnimationId,
		int pAnimationCount,
		int pDelay, 
		uint16 * pTable);

	void AddSound(
		uint16 pAnimationId,
		uint16 pFrame, 
		uint16 pFile);

	void LoadAnimation(
		int pAnimationId, 
		int pFile, 
		uint16 * pTable);

	void LoadAnimationAlpha(
		int pAnimationId, 
		int pFile, 
		uint16 * pTable, 
		uint16 * pAlphaTable);

	void AddTransformation(
		int pAnimationId, 
		int pAnimationCount, 
		int pDeltaTableX[], 
		int pDeltaTableY[]);

	void LoadCurrentImage();

	uint16 CurrentFrame();

	virtual void Prepare();

	virtual void MsgPenDown(int pX, int pY);
	virtual void MsgPenUp(int pX, int pY);
	virtual void MsgPenMove(int pX, int pY);

	virtual bool HitTest(int pX, int pY);

};


