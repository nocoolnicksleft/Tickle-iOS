#include "flipbook.h"

#include "common.h"


Flipbook::Flipbook(Rectangle * pRect,char * textid) : Window(pRect,textid)
{

	_animation_id = 0;
	_animation_phase = 0;
	_animation_repeat = 0;
	_reverse = 0;
	_valid = false;
	_delay = 0;
	_running = false;

	
	// Events to null
	OnAnimationStarted = 0;
	OnAnimationCompleted = 0;
	OnFramePrepare = 0;
	OnAction = 0;
}

Flipbook::~Flipbook()
{
	for_each(_animations.begin(), _animations.end(), free_ptr<FlipbookAnimation>());
	for_each(_actions.begin(), _actions.end(), free_ptr<FlipbookAction>());
/*
	vector <FlipbookAnimation*>::iterator animation_iterator;
	for ( animation_iterator = _animations.begin( ); animation_iterator != 
	++


	{
		if (!_timeout)
		{
			_timeout = _delay;

			if (_reverse)
			{
				LoadCurrentImage();

				if (_animation_phase) --_animation_phase;

				else
				{
					_running = false;
					if (OnAnimationCompleted) (*OnAnimationCompleted)(this,_animation_id);
				}

			} else {

				FlipbookAnimation * animation = _animations.at(_animation_id);
				FlipbookFrame * frame = animation->Frames.at(_animation_phase);

				if (frame->Sounddata) playGenericSound( frame->Sounddata, frame->Soundsize);

				if (animation->TransformationX) _position->Left += animation->TransformationX[_animation_phase];

				if (animation->TransformationY) _position->Top += animation->TransformationY[_animation_phase];

				_position->Left += frame->OffsetX;

				_position->Top += frame->OffsetY;

				LoadCurrentImage();

				if (_animation_phase < _animation_phase_count-1) 
				{
					++_animation_phase;
				}
				else 
				{
					_running = false;
					if (_animation_repeat)
					{
						--_animation_repeat;
						Run(_animation_id);
					}
					else if (OnAnimationCompleted) (*OnAnimationCompleted)(this,_animation_id);
				}

			}

		} else --_timeout;
	} else {
		if (!_valid)
		{
			LoadCurrentImage();
			_valid = true;
		}
	}
	Window::Prepare();
}

bool Flipbook::IsRunning()
{
	return _running;
}

void Flipbook::LoadCurrentImage()
{
	/*
	if (_textid[0] == 'k')
	{
	char debstring[10];
	sprintf(debstring,"l %u %u",_animation_id, _animation_phase);
	DebugPrint(debstring);
	}
	if (!_buffer) {
		DebugPrint("NoImageBuffer");
		return;
	}
	*/

	//_valid = false;
	bitblt16rle(
			_buffer->GetImageBuffer(),
			_animations.at(_animation_id)->Width,
			0,
			0,
			_animations.at(_animation_id)->Frames.at(_animation_phase)->Imagedata);


	if (_animations.at(_animation_id)->Frames.at(_animation_phase)->Alphadata)
	{
		bitblt8rle(
			_buffer->GetAlphaBuffer(),
			_animations.at(_animation_id)->Width,
			0,
			0,
			(uint8 *)_animations.at(_animation_id)->Frames.at(_animation_phase)->Alphadata);

	}

	
	
}

void Flipbook::RunReverse()
{
	if (!_running)
	{
		_reverse = true;
		_valid = false;
	
		_timeout = _delay;
		_running = true;
		Prepare();
	}
}

void Flipbook::Run(uint16 pAnimationId, uint16 pRepeat)
{
	_animation_repeat = pRepeat;
	Run(pAnimationId);
}


void Flipbook::Run(uint16 pAnimationId)
{
	if (_animations.size())
	{
		if (pAnimationId < _animations.size())
		{
			if (!_running)
			{
				_reverse = false;

				_animation_id = pAnimationId;

				FlipbookAnimation * animation = _animations.at(_animation_id);

				_animation_phase = 0;
				_animation_phase_count = animation->FrameCount;
				_valid = false;
				_delay = animation->Delay;
				_timeout = _delay;
				_running = true;

				if ( (animation->PositionX) || (animation->PositionY) ) {
					_position->Left = animation->PositionX;
					_position->Top = animation->PositionY;
				}

				if (OnAnimationStarted) (*OnAnimationStarted)(this,_animation_id);
				Prepare();
			}
		}
	}
}

void Flipbook::SetNoPosition(uint16 pAnimationId, uint16 pPhaseId)
{
	_animation_id = pAnimationId;
	_animation_phase = pPhaseId;
	_animation_phase_count = _animations.at(pAnimationId)->FrameCount;
	_valid = false;
	_running = false;
	Prepare();
}

void Flipbook::Set(uint16 pAnimationId, uint16 pPhaseId)
{
	_animation_id = pAnimationId;
	_animation_phase = pPhaseId;
	_animation_phase_count = _animations.at(pAnimationId)->FrameCount;
	_valid = false;
	_running = false;
	if ( (_animations.at(pAnimationId)->PositionX) || (_animations.at(pAnimationId)->PositionY) ) {
		_position->Left = _animations.at(pAnimationId)->PositionX;
		_position->Top = _animations.at(pAnimationId)->PositionY;
	}
	Prepare();
}

void Flipbook::AddAction(Rectangle * pRect, GenericEvent pEvent, uint16 pAnimationId)
{
// TODO irgendwie auf gültige AnimationId prüfen
//	if (pAnimationId < _animations.size()) 
//	{
	
		_actions.push_back(new FlipbookAction(pRect, pEvent, pAnimationId));
//	}
}

void Flipbook::AddAnimation(int pAnimationId,int pAnimationCount,int pDelay, uint16 * pTable)
{
	_animations.push_back(new FlipbookAnimation(pAnimationId,pAnimationCount,pDelay));
	_animations.back()->Table = pTable;
}

void Flipbook::LoadAnimation(int pAnimationId, int pFileId, uint16 * pTable)
{
	_animations.push_back(new FlipbookAnimation(pAnimationId,pFileId,pTable,0));
	_animations.back()->Load();
}

void Flipbook::LoadAnimationAlpha(int pAnimationId, int pFileId, uint16 * pTable, uint16 * pAlphaTable)
{
	_animations.push_back(new FlipbookAnimation(pAnimationId,pFileId,pTable,pAlphaTable));
	_animations.back()->Load();
}

void Flipbook::MsgPenMove(int pX, int pY)
{
	//char debstr[30];
	//sprintf(debstr,"%s::Move x: %d y: %d",_textid,pX,pY);
	//DebugPrint(debstr);

	if (!_running)
	{
	//	MsgPenDown(pX,pY);
	}
	
	Window::MsgPenMove(pX,pY);
}

void Flipbook::MsgPenUp(int pX, int pY)
{
	Window::MsgPenUp(pX,pY);
}

void Flipbook::MsgPenDown(int pX, int pY)
{
	for (uint16 i = 0; i < _actions.size(); i++)
	{
		FlipbookAction * action = _actions.at(i);

		if (action->Rect->Hit(pX - _position->Left ,pY - _position->Top  )) 
		{
			if (action->ActionId != -1) Run(action->ActionId);

			if (action->OnTrigger) (*(action->OnTrigger))(); 
		}
	}
	Window::MsgPenDown(pX,pY);
}


void Flipbook::AddTransformation(int pAnimationId, int pAnimationCount, int * pDeltaTableX, int * pDeltaTableY)
{
	if (pDeltaTableX) _animations.at(pAnimationId)->TransformationX = pDeltaTableX;
	if (pDeltaTableY) _animations.at(pAnimationId)->TransformationY = pDeltaTableY;

}

void Flipbook::AddSound(uint16 pAnimationId,uint16 pFrame, uint16 pFile)
{
	_animations[pAnimationId]->Frames.at(pFrame)->Sounddata = LoadFileCopy(pFile);
	_animations[pAnimationId]->Frames.at(pFrame)->Soundsize = FileSize(pFile);
}

void FlipbookAnimation::Load()
{

	uint16 * file = LoadFile(FileId);
	if (file)
	{
		file += 2; // magic
		file += 2; // version
		Width = *file;
		file += 1;
		Height = *file;
		file += 1;
		PositionX = *file;
		file += 1;
		PositionY = *file;
		file += 1;
		Delay = *file;
		file += 1;
		FrameCount = *file;
		file += 1;

		//char debstr[55];
		//sprintf(debstr,"ani c %u w %u h %u x %u y %u",FrameCount,Width, Height, PositionX, PositionY);
		//DebugPrint(debstr);

		for (uint16 i = 0; i < FrameCount; i++)
		{
			FlipbookFrame * frame = new FlipbookFrame();

			file += 1;
			frame->OffsetX = *file;
			file += 1;
			frame->OffsetY = *file;
			file += 1;
			frame->Delay = *file;
			file += 1;

			frame->Imagedata  = LoadFile(Table[i]);
			if (AlphaTable)	frame->Alphadata  = (uint8 *)LoadFile(AlphaTable[i]);
			else frame->Alphadata = 0;

			Frames.push_back(frame);

		}

	}
}

FlipbookAnimation::FlipbookAnimation(uint16 pAnimationId, uint16 pFileId, uint16 * pTable, uint16 * pAlphaTable)
{

//		Frames = 0;
		FileId = 0;
		FrameCount = 0;
		Delay = 0;
		TransformationX = 0;
		TransformationY = 0;

		FileId = pFileId;
		Table = pTable;
		AlphaTable = pAlphaTable;

}

uint16 Flipbook::CurrentFrame()
{
	return _animation_phase;
}


FlipbookFrame::FlipbookFrame()
{
		OffsetX = 0;
		OffsetY = 0;
		Delay = 0;
		Imagedata = 0;
		Alphadata = 0;
		Sounddata = 0;
		Soundsize = 0;
}

FlipbookFrame::FlipbookFrame(uint16 offsetX, uint16 offsetY, uint16 delay)
{
	Imagedata = 0;
	Alphadata = 0;
	Sounddata = 0;
	Soundsize = 0;
	OffsetX = offsetX;
	OffsetY = offsetY;
	Delay = delay;
}

bool Flipbook::HitTest(int pX, int pY)
{
	if (_position->Hit(pX,pY))
	{
		if (!(_animations.at(_animation_id)->AlphaTable)) 
		{
			return true;
		}
		else
		{ 
			uint8 * alpha = _buffer->GetAlphaBuffer();
			if (alpha)
			{
				if (alpha[(pY-_position->Top) * _animations.at(_animation_id)->Width + (pX - _position->Left)] != 0) 
					return true;
			} else return true;
		}
	}
	return false;
}

