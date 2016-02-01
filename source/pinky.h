#pragma once

#include "common.h"
#include "sprite.h"

enum PinkySubaction
{
	PinkySubactionNone,
	PinkySubactionJump,
	PinkySubactionTurn,
	PinkySubactionFly,
	PinkySubactionWalk,
	PinkySubactionFall
};

enum PinkyHeading
{
	PinkyHeadingFront,
	PinkyHeadingLeft,
	PinkyHeadingRight
};

enum PinkyAction
{
	PinkyActionStop,
	PinkyActionWalk
};

enum PinkyStatus
{
	PinkyStatusStop,
	PinkyStatusFly,
	PinkyStatusWalk,
	PinkyStatusTurn,
	PinkyStatusJump
};

class Pinky :  public Sprite
{

private:
	PinkyAction _action;
	PinkySubaction _subaction;
	PinkyHeading _heading;
    PinkyHeading _newheading;

public:
	Pinky(int pSize);

	virtual void Initialized();

public:
	virtual void Prepare();
	virtual void Display();

	// virtual
	void LoadImages();
	void SelectImage(unsigned int action, unsigned int id);

	// specific
	PinkyHeading Heading();

	void WalkLeft();
	void WalkRight();
	void Turn(PinkyHeading pTargetHeading);
	void Jump();
	void Fly();
	void Fall();

	void Left();
	void Right();

};
