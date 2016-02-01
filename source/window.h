#pragma once

#include "common.h"
#include "window.h"
#include "rectangle.h"
#include "bitmap.h"

class Window;

typedef void (*WindowPositionEvent) (Window * window, int x, int y);
typedef void (*WindowPositionDeltaEvent) (Window * window, int x, int y, int dx, int dy);

class Window
{
protected:
	bool _enabled;
	bool _visible;

	bool _valid;

	bool _alpha_enabled;
	uint8 _alpha_value;

	uint16 _back_color;
	uint16 _fore_color;

	uint16 _frame_width;
	uint16 _frame_color;

	Rectangle * _position;

	Bitmap * _buffer;
	Bitmap * _parent_buffer;

	Rectangle * _inner_rect;

	uint16 _animation_last;
	uint16 _animation_current;

	int _animation_type;
	uint16 _animation_step;
	int _animation_delay;

	multimap<int, Window*> _window;

	int16 * _position_table_x;
	int16 * _position_table_y;

	bool _pen_capture;

	static Window * _pen_capture_target;



public:
	char * _textid;
	Window();
	Window(Rectangle * pRect, char * ptextid);

public:
	virtual ~Window(void);

public:
	GenericEvent OnAnimationCompleted;

	void AddWindow(Window * pWindow, int zOrder);
	void RemoveWindow(Window * pWindow);


	void Enable();
	void Disable();
	bool Enabled();

	void Visible();
	void Invisible();
	bool IsVisible();

	void EnablePenCapture();
	void DisablePenCapture();
	bool PenCapture();
	
	void SetParent(Bitmap * pParent);
	Bitmap * GetBuffer();

	void AlphaEnable();
	void AlphaDisable();
	bool AlphaEnabled();
	void SetAlpha(uint8 pValue);

	void Position(int x, int y);
	void PositionDelta(int dx, int dy);

	Rectangle * Position();

	virtual void Clear();
	virtual void Prepare();
	virtual void Display();
	virtual void BufferToScreen();

	virtual void MsgPenDown(int pX, int pY);
	virtual void MsgPenUp(int pX, int pY);
	virtual void MsgPenMove(int pX, int pY);

	WindowPositionEvent OnMsgPenDown;
	WindowPositionEvent OnMsgPenMove;
	WindowPositionEvent OnMsgPenUp;

	virtual void DragStart(int pX, int pY);
	virtual void DragMove(int pX, int pY);
	virtual void DragEnd(int pX, int pY);

	WindowPositionEvent OnDragStart;
	WindowPositionEvent OnDragMove;
	WindowPositionEvent OnDragEnd;

	virtual void EndAnimation();

	virtual void AnimatePosition(int pTargetX, int pTargetY, int pTime, AnimationCurve pCurve);

	virtual void FadeToWhite(int pTime);
	virtual void FadeFromWhite(int pTime);
	virtual void FadeToBlack(int pTime);
	virtual void FadeFromBlack(int pTime);

	virtual bool HitTest(int pX, int pY);

	char * Text();
	void Text(char * text);





};
