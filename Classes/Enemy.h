#ifndef __BalloonRide__Enemy__
#define __BalloonRide__Enemy__

#include "cocos2d.h"
#include "AnimatedObject.h"
USING_NS_CC;

class Enemy : public AnimatedObject
{
public:
	using AnimatedObject::init;
	Enemy();
    virtual bool init(float speed);
	static Enemy* create(float speed);
	void go();
private:
	/**
	* Movement speed of the enemy.
	*/
	float __speed;
};

#endif // __BalloonRide__Enemy__
