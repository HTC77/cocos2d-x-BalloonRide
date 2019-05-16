#ifndef __BalloonRide__Balloon__
#define __BalloonRide__Balloon__

#include "cocos2d.h"
#include "AnimatedObject.h"
USING_NS_CC;

/**
* Main character class. Handles balloon movement.
*/
class Balloon : public AnimatedObject
{
public:

	Balloon();
    virtual bool init(Scene* parent);
	void setMove(float x, float y);

	static Balloon* create(Scene* parent);

private:
	/**
	* This value indicates how far the object should move based on accelerometer readings.
	*/
	float							__xMove;

	/**
	* This value indicates how far the object should move based on accelerometer readings.
	*/
	float							__yMove;

	/**
	* This is the balloon movement action. It is updated frequently.
	*/
	FiniteTimeAction*				__pMoveAction;

	/**
	* Balloon movement speed.
	*/
	float							__speed;

	/**
	* Size of the screen.
	*/
	Size							__winSize;

	void move(float delta);
};

#endif // __BalloonRide__Balloon__
