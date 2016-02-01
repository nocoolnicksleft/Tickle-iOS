#include "sprite.h"
#include "pinky.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

#include <gbfs.h>

#include "binaries.h"

extern const GBFS_FILE  data_gbfs;


Pinky::Pinky(int pSize) : Sprite (pSize)
{
}

void Pinky::Initialized()
{
	_action = PinkyActionStop;
	_subaction = PinkySubactionNone;
	_heading = PinkyHeadingRight;
	_newheading = PinkyHeadingRight;
	SelectImage(PinkySubactionWalk,0);
}

#define PINKY_WALK_COUNT 13
#define PINKY_JUMP_COUNT 29
#define PINKY_FLY_COUNT 42
#define PINKY_TURN_COUNT 18

void Pinky::LoadImages()
{

}

void Pinky::SelectImage(unsigned int  action, unsigned int  id)
{
	uint8 * spriteData;

	uint16 * image_table;

	if (action == PinkySubactionWalk) {
		image_table = ar_pinky_walk_1;
	} 
	if (action == PinkySubactionFly) {
		image_table = ar_pinky_fly_1;
	}
	if (action == PinkySubactionJump) {
		image_table = ar_pinky_jump_1;
	}
	if (action == PinkySubactionTurn) {
		image_table = ar_pinky_turn_1;
	}
	if (action == PinkySubactionFall) {
		image_table = ar_pinky_fall_1;
	}

	spriteData = (uint8 *) LoadFile(image_table[id]);
	bitblt8rle((uint8 *)&_spriteGfxMemory[(_vram_address*16) ],64,0,0,spriteData);

}

void Pinky::Prepare()
{

}


void Pinky::Display()
{
	if (_enabled)
	{
		if (_countdown > 0) _countdown--;
		else  
		{
			_countdown = _delay;

			if (_action == PinkyActionWalk) 
			{
				if (_subaction == PinkySubactionNone) {
					if (_heading == PinkyHeadingLeft) {
						_x -= 2;
						_animation_mirror = true;
					}
					else {
						_x += 2;
						_animation_mirror = false;
					}

					SelectImage(PinkySubactionWalk,_animation_current);
					if (_animation_current == _animation_last) _action = PinkyActionStop;
					else if (_animation_current > _animation_last) _animation_current--;
					else _animation_current++;
				}
			}

			if (_subaction != PinkySubactionNone)
			{

				if (_subaction == PinkySubactionFly) 
				{
					if ((_animation_current < 34) && (_animation_current > 1)) {
						if (_animation_current > 17) {
							_y += 6;
						} else {
							_y -= 6;
						}
						_x -= 3;
					}

					SelectImage(PinkySubactionFly,_animation_current);
				}

				if (_subaction == PinkySubactionJump) 
				{


					if ( (_animation_current < 17) && (_animation_current >6 )) {
						if (_animation_current < 12) {
							_y -= 7;
						} else {
							_y += 7;
						}

						if (_heading == PinkyHeadingLeft) _x -= 10;
						else _x += 10;
					}

					if (_animation_current == 17) playGenericSound(LoadFileCopy(blob1_bin),1463);

					SelectImage(PinkySubactionJump,_animation_current);
				}

				if (_subaction == PinkySubactionTurn) 
				{
					if (_animation_current == _animation_last) {
						_heading = _newheading;
					}
					SelectImage(PinkySubactionTurn,_animation_current);
				}

				if (_subaction == PinkySubactionFall) 
				{
					_animation_mirror = false;

					if (_animation_current > 28) _x -= 4;

					SelectImage(PinkySubactionFall,_animation_current);
				}

				if (_animation_current == _animation_last) {
					_subaction = PinkySubactionNone;
					if (_action != PinkyActionStop)
					{
						_animation_first = 10;
						_animation_last = 0;
						_animation_current = _animation_first ;
					}
				}
				else if (_animation_current > _animation_last) _animation_current--;
				else _animation_current++;

			} // if subaction != none


			if (_animation_mirror) this->_spriteEntry->attribute[1] |= ATTR1_FLIP_X;
			else this->_spriteEntry->attribute[1] &= ~ATTR1_FLIP_X;

			Move(_x,_y);
		} // if _countdown / else

	} // if _enabled
}

PinkyHeading Pinky::Heading()
{
	return _heading;
}

void Pinky::Fall()
{
	if (_subaction == PinkySubactionNone) {
		if  (_heading == PinkyHeadingRight) {
			_delay = 0;
			 playGenericSound(LoadFileCopy(swoosh1_bin),22859);
			_animation_first = 0;
			_animation_last = 34;
			_animation_mirror = 1;
			_animation_current = _animation_first;
			_subaction = PinkySubactionFall;
		}
	}
}

void Pinky::Turn(PinkyHeading pTargetHeading)
{
	if (_subaction != PinkySubactionTurn)
	{
		if (_heading != pTargetHeading) {
			_newheading = pTargetHeading;
			_subaction = PinkySubactionTurn;
			_delay = 0;

			if ((_heading == PinkyHeadingRight) && (_newheading == PinkyHeadingFront))  {
				_animation_first = 26;
				_animation_last = 13;
				_animation_mirror = 0;
			} 

			if ((_newheading == PinkyHeadingRight) && (_heading == PinkyHeadingFront))  {
				_animation_first = 12;
				_animation_last = 26;
				_animation_mirror = 0;
			} 

			if ((_heading == PinkyHeadingLeft) && (_newheading == PinkyHeadingFront))  {
				_animation_first = 0;
				_animation_last = 13;
				_animation_mirror = 0;
			}

			if ((_newheading == PinkyHeadingLeft) && (_heading == PinkyHeadingFront))  {
				_animation_first = 14;
				_animation_last = 0;
				_animation_mirror = 0;
			}

			_animation_current = _animation_first;
		}
	}
}

void Pinky::WalkLeft()
{
	if (_action != PinkyActionWalk) 
	{
		if (_heading == PinkyHeadingLeft) {
			_delay = 0;
			_action = PinkyActionWalk;
			_animation_first = 10;
			_animation_last = 0;
			_animation_current = _animation_first;
		}
	}
}

void Pinky::WalkRight()
{
	if (_action != PinkyActionWalk) 
	{
		if (_heading == PinkyHeadingRight) {
			_delay = 0;
			_action = PinkyActionWalk;
			_animation_first = 10;
			_animation_last = 0;
			_animation_current = _animation_first;
		}
	}
}

void Pinky::Fly()
{
	if (_subaction == PinkySubactionNone) {
		if  (_heading == PinkyHeadingFront) {
			_delay = 0;
			 playGenericSound(LoadFileCopy(swoosh1_bin),22859);
			_animation_first = 0;
			_animation_last = 41;
			_animation_mirror = 1;
			_animation_current = _animation_first;
			_subaction = PinkySubactionFly;
		}
	}
}

void Pinky::Jump()
{
	if ((_subaction == PinkySubactionNone) && (_heading != PinkyHeadingFront)) { 
		_delay = 0;
		_animation_first = 0;
		_animation_last = 28;
		if (_heading == PinkyHeadingLeft) _animation_mirror = 1;
		else _animation_mirror = 0;
		_animation_current = _animation_first;
		_subaction = PinkySubactionJump;
	}
}

void Pinky::Left()
{
	if (_heading == PinkyHeadingRight) Turn(PinkyHeadingFront);
	else if (_heading == PinkyHeadingFront) Turn(PinkyHeadingLeft);
	else WalkLeft();
}

void Pinky::Right()
{
	if (_heading == PinkyHeadingLeft) Turn(PinkyHeadingFront);
	else if (_heading == PinkyHeadingFront) Turn(PinkyHeadingRight);
	else WalkRight();
}

