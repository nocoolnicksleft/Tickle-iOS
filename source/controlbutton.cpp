#include "common.h"
#include "controlbutton.h"
#include "font.h"
#include "bitmap.h"

uint16 * ControlButton::_sounddata = 0;
uint32 ControlButton::_soundsize = 0;
Font * ControlButton::_fontxx = 0;

void ControlButton::Init()
{
	_fontxx = new Font(FontTypeComicSans10);
	_sounddata = LoadFileCopy(buttonpush_bin);
	_soundsize = FileSize(buttonpush_bin);
}

ControlButton::ControlButton(Rectangle * rect, char * text, uint16 * fileInactive, uint16 * fileActive, uint16 * filePushed, uint16 duration)
	: Window(rect,text)
{
	_fileInactive = 0;
	_fileActive = 0;
	_filePushed = 0;
	_duration = 0;
	_state = 0;
	OnPush = 0;
	OnReset = 0;
	_fontxx = 0;

	_fileInactive = fileInactive;
	_fileActive = fileActive;
	_filePushed = filePushed;
	_duration = duration;
	_state = CONTROLBUTTON_ACTIVE;

	_textRect = new Rectangle(7,-2,rect->Width-14,rect->Height);
	

}

ControlButton::~ControlButton()
{
	if (_textRect) delete _textRect;
}


void ControlButton::MsgPenDown(int pX, int pY)
{
	if (_state == CONTROLBUTTON_ACTIVE)	Push();
}

void ControlButton::Prepare()
{
	if (_state == CONTROLBUTTON_PUSHED)
	{
		if (_countdown) --_countdown;
		else {
			_state = CONTROLBUTTON_ACTIVE;
			if (OnReset) (*OnReset)(this,_state);
			_valid = false;
		}
	}

	if (!_valid)
	{
		if (_state == CONTROLBUTTON_INACTIVE) _buffer->LoadCompressedFile(_fileInactive);
		else if (_state == CONTROLBUTTON_PUSHED) _buffer->LoadCompressedFile(_filePushed);
		else _buffer->LoadCompressedFile(_fileActive);

		_buffer->DrawText(new Font(FontTypeComicSans10),_textRect,_textid,RGB5(255,255,255) | (1 << 15));
		_valid = true;
	}
	Window::Prepare();
}

void ControlButton::State(uint8 state)
{
	_state = state;
	_valid = false;
}

uint8 ControlButton::State()
{
	return _state;
}

void ControlButton::Push()
{
	if (_sounddata) playGenericSound( _sounddata, _soundsize);
	_state = CONTROLBUTTON_PUSHED;
	_countdown = _duration;
	_valid = false;
}


