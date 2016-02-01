
#include "window.h"

Window * Window::_pen_capture_target = 0;

Window::Window()
{

}

Window::Window(Rectangle * pRect, char * ptextid)
{
	_position_table_x = 0;
	_position_table_y = 0;

	_animation_last = 0;
	_animation_current = 0;

	_animation_type = 0;
	_animation_step = 0;
	_animation_delay = 0;

	_position = pRect;

	_enabled = true;
	_visible = true;
	_valid = false;

	_pen_capture = false;

	_alpha_enabled = false;
	_alpha_value = 255;

	_frame_width = 0;
	_frame_color = RGB15(255,0,0) | (1 << 15);

	OnAnimationCompleted = 0;
	OnMsgPenDown = 0;
	OnMsgPenMove = 0;
	OnMsgPenUp = 0;
	OnDragStart = 0;
	OnDragMove = 0;
	OnDragEnd = 0;

	_parent_buffer = 0;
	_buffer = 0;
	_buffer = new Bitmap(pRect->Width,pRect->Height);

	_textid = new char[20];
	strncpy(_textid,ptextid,19);

	_back_color = RGB15(31,31,31) | (1 << 15);
	_fore_color = RGB15( 0, 0, 0) | (1 << 15);
	_fore_color = RGB15( 0, 0, 0) | (1 << 15);

	_inner_rect = new Rectangle(0,0,_position->Width, _position->Height);

	Clear();
}

Window::~Window(void)
{
	if (_position_table_x) delete [] _position_table_x;
	if (_position_table_y) delete [] _position_table_y;

	if (_inner_rect) delete _inner_rect;
	if (_buffer) delete _buffer;

	if (_textid) delete _textid;
}

void Window::SetParent(Bitmap * pParent)
{
	_parent_buffer = pParent;
}

Bitmap * Window::GetBuffer()
{
	return _buffer;
}

void Window::EndAnimation()
{
	if (OnAnimationCompleted) (*OnAnimationCompleted)();

	_animation_current = 0;
	_animation_last = 0;

	if (_position_table_x)
	{
		delete [] _position_table_x;
		_position_table_x = 0;
	}

	if (_position_table_y)
	{
		delete [] _position_table_y;
		_position_table_y = 0;
	}
}

void Window::BufferToScreen()
{
	if (_alpha_enabled) 
		_parent_buffer->DrawBitmapAlphaFixed(_buffer,_alpha_value,_position->Left,_position->Top);
	else
		_parent_buffer->DrawBitmap(_buffer,_position->Left,_position->Top);
}


void Window::Display()
{
	if (_visible)
	{
		multimap <int, Window*>::iterator window_iterator;
		for ( window_iterator = _window.begin( ); window_iterator != _window.end( ); window_iterator++ )
			window_iterator->second->Display();

		if (_animation_type)
		{
			if (_animation_type == 1) { // Fade to white
				if (_animation_step == 240) _animation_type = 0;
				else {
					_animation_step+=16;
					_buffer->FadeHigh(_animation_step);
				}
			}
			else if (_animation_type == 2) { // Fade from white
				if (_animation_step == 0) _animation_type = 0;
				else {
					_animation_step-=16;
					_buffer->FadeHigh(_animation_step);
				}
			}
			else if (_animation_type == 3) { // Fade to black
				if (_animation_step == 240) _animation_type = 0;
				else {
					_animation_step+=16;
					_buffer->FadeLow(_animation_step);
				}
			}
			else if (_animation_type == 4) { // Fade from black
				if (_animation_step == 0) _animation_type = 0;
				else {
					_animation_step-=16;
					_buffer->FadeLow(_animation_step);
				}
			}
			if (_animation_type == 0) if (OnAnimationCompleted) (*OnAnimationCompleted)();
		}

		BufferToScreen();
	}
}

void Window::Clear()
{
	_buffer->Clear(_back_color);
}

void Window::MsgPenDown(int pX, int pY)
{
	if (OnMsgPenDown)	
	{
		(*OnMsgPenDown)(this,pX - _position->Left,pY - _position->Top);
	}

	multimap <int, Window*>::reverse_iterator window_iterator;
	for ( window_iterator = _window.rbegin( ); window_iterator != _window.rend( ); window_iterator++ )
	{
		Window * window = window_iterator->second;

		if (window->Enabled())
		{
			if (window->HitTest(pX,pY)) 
			{
				window->MsgPenDown(pX,pY);
				return;
			}
		}
	}
}


void Window::MsgPenUp(int pX, int pY)
{
	if (OnMsgPenUp)	
	{
		(*OnMsgPenUp)(this,pX - _position->Left,pY - _position->Top);
	}
	if (_pen_capture_target) 
	{
		_pen_capture_target->DragEnd(pX,pY);
		_pen_capture_target = 0;
	}
	else {
		multimap <int, Window*>::reverse_iterator window_iterator;
		for ( window_iterator = _window.rbegin(); window_iterator != _window.rend(); window_iterator++ )
			if (window_iterator->second->HitTest(pX,pY)) window_iterator->second->MsgPenUp(pX,pY);
	}
}


void Window::MsgPenMove(int pX, int pY)
{
	if (OnMsgPenMove)	
	{
		(*OnMsgPenMove)(this,pX - _position->Left,pY - _position->Top);
	}

	if (_pen_capture_target) 
	{
		_pen_capture_target->DragMove(pX,pY);
	}
	else {
		multimap <int, Window*>::reverse_iterator window_iterator;
		for ( window_iterator = _window.rbegin(); window_iterator != _window.rend(); window_iterator++ )
		{
			Window * window = window_iterator->second;

			if (window->Position()->Hit(pX,pY)) 
			{


				if (window->PenCapture()) {
					_pen_capture_target = window;
					_pen_capture_target->DragStart(pX,pY);
					_pen_capture_target->DragMove(pX,pY);
				} else window->MsgPenMove(pX,pY);
			}
		}
	}
}

void Window::DragStart(int pX, int pY)
{
	if (OnDragStart)	
	{
		(*OnDragStart)(this,pX,pY);
	}
}

void Window::DragMove(int pX, int pY)
{
	if (OnDragMove)	
	{
		(*OnDragMove)(this,pX,pY);
	}
}

void Window::DragEnd(int pX, int pY)
{
	if (OnDragEnd)	
	{
		(*OnDragEnd)(this,pX,pY);
	}
}


void Window::Visible()
{
	_visible = true;
}

void Window::Invisible()
{
	_visible = false;
}

bool Window::IsVisible()
{
	return _visible;
}


void Window::Enable()
{
	_enabled = true;
}

void Window::Disable()
{
	_enabled = false;
}

bool Window::Enabled()
{
	return _enabled;
}

void Window::Position(int x, int y)
{
	_position->Left = x;
	_position->Top = y;

}

void Window::PositionDelta(int dx, int dy)
{
	//	char debstr[40];
	//sprintf(debstr,"W::PDelta 1 %d %d %d %d",_position->Left,_position->Top,dx,dy);
	//DebugPrint(debstr);
	_position->Left = _position->Left + dx;
	_position->Top  = _position->Top  + dy;
	//sprintf(debstr,"W::PDelta 2 %d %d %d %d",_position->Left,_position->Top,dx,dy);
	//DebugPrint(debstr);

}

void Window::AnimatePosition(int pTargetX, int pTargetY, int pTime, AnimationCurve pCurve)
{
	//TODO debug raus
	//	char debstr[40];

	if (_position_table_x)
	{
		EndAnimation();
	}
	_position_table_x = new int16[pTime];
	_position_table_y = new int16[pTime];

	int pDeltaX;
	int pDeltaY;
	int i = 0;

	if (pCurve == AnimationCurveLinear)
	{
		pDeltaX = ( ((_position->Left - pTargetX) << 8) / pTime);
		pDeltaY = ( ((_position->Top  - pTargetY) << 8) / pTime);

		for (i = 0; i < pTime; i++)
		{
			_position_table_x[i] = _position->Left - ((i*pDeltaX) >> 8);
			_position_table_y[i] = _position->Top  - ((i*pDeltaY) >> 8);
		}

	} 
	else if (pCurve == AnimationCurveAccelerating)
	{

		pDeltaX = (_position->Left - pTargetX);
		pDeltaY = (_position->Top  - pTargetY);

		int pDelta = 256 / pTime;

		for (i = 0; i < pTime; i++)
		{
			int  fact = x3table[(i*pDelta)];

			_position_table_x[i] = _position->Left - (  (fact * pDeltaX) >> 8);
			_position_table_y[i] = _position->Top  - (  (fact * pDeltaY) >> 8);
		}

	}

	else if (pCurve == AnimationCurveSlowing)
	{

		pDeltaX = (_position->Left - pTargetX);
		pDeltaY = (_position->Top  - pTargetY);

		int pDelta = 256 / pTime;

		for (i = 0; i < pTime; i++)
		{
			int  fact = x3table[(pTime-i-1)*pDelta];

			_position_table_x[i] = _position->Left - (  ((256-fact) * pDeltaX) >> 8);
			_position_table_y[i] = _position->Top  - (  ((256-fact) * pDeltaY) >> 8);
		}
	}
	else if (pCurve == AnimationCurveOvershoot)
	{
		pDeltaX = (_position->Left - pTargetX);
		pDeltaY = (_position->Top  - pTargetY);

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
			_position_table_x[i] = (_position->Left - pOvershootX) - (  ((256-fact) * pDeltaX) >> 8);
			_position_table_y[i] = (_position->Top  - pOvershootY) - (  ((256-fact) * pDeltaY) >> 8);
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

void Window::AlphaEnable()
{
	this->_alpha_enabled = true;
}

void Window::AlphaDisable()
{
	this->_alpha_enabled = false;
}

bool Window::AlphaEnabled()
{
	return this->_alpha_enabled;
}

void Window::SetAlpha(uint8 pValue)
{
	_alpha_value = pValue;
}

void Window::EnablePenCapture()
{
	_pen_capture = true;
}

void Window::DisablePenCapture()
{
	_pen_capture = false;
}

bool Window::PenCapture()
{
	return 	_pen_capture;
}

Rectangle * Window::Position()
{
	return _position;
}


void Window::AddWindow(Window * pWindow, int zOrder)
{
	typedef pair <int, Window*> zorder_window;

	_window.insert(zorder_window(zOrder,pWindow));

	pWindow->SetParent(_buffer);
}

void Window::RemoveWindow(Window * pWindow)
{
	multimap <int, Window*>::iterator window_iterator;
	for ( window_iterator = _window.begin(); window_iterator != _window.end(); window_iterator++ )
	{
		if ( window_iterator->second == pWindow) {
			_window.erase(window_iterator);
			return;
		}
	}
}

void Window::Prepare()
{
	if (_position_table_x)
	{
		this->_position->Left  = _position_table_x[_animation_current];
		this->_position->Top = _position_table_y[_animation_current];

		if (_animation_current == _animation_last) EndAnimation();
		else _animation_current++;
	}
	multimap <int, Window*>::iterator window_iterator;
	for ( window_iterator = _window.begin( ); window_iterator != _window.end( ); window_iterator++ )
		window_iterator->second->Prepare();
}

void Window::FadeToWhite(int pTime)
{
	_animation_type = 1;
	_animation_delay = 0;
	_animation_step = 0;
}

void Window::FadeFromWhite(int pTime)
{
	_animation_type = 2;
	_animation_delay = 0;
	_animation_step = 240;
}

void Window::FadeToBlack(int pTime)
{
	_animation_type = 3;
	_animation_delay = 0;
	_animation_step = 0;
}

void Window::FadeFromBlack(int pTime)
{
	_animation_type = 4;
	_animation_delay = 0;
	_animation_step = 240;
}

bool Window::HitTest(int pX, int pY)
{
	return (_position->Hit(pX,pY));
}

char * Window::Text()
{
	return _textid;
}

void Window::Text(char * text)
{
	strncpy(_textid,text,19);
}
