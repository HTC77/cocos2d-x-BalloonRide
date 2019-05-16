#include "Balloon.h"

Balloon::Balloon():
__xMove(0.0f),
__yMove(0.0f),
__pMoveAction(NULL),
__speed(0.0f)
{
}

/**
* Set balloon properties and schedule movement update.
* @param parent Parent that will hold the sprite sheet.
*/
bool Balloon::init(Scene* parent)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

	parent->addChild(this);

	auto frameNamePrefix = "balloon";
	auto textureFileName = "balloons.png";
	int frameNumber = 3;
	float delay = 0.5f;
	__speed = 1000.0f;
	__winSize = Director::getInstance()->getWinSize();
	AnimatedObject::init(textureFileName, frameNamePrefix, frameNumber, delay, parent, ANIM_BALLOON_SPRITESHEET);
	schedule(schedule_selector(Balloon::move), 0.03f);
    return true;
}

void Balloon::setMove(float x, float y)
{
	__xMove = y;
	__yMove = x;
}

void Balloon::move(float delta)
{
	const int speedLimit = 50;
	if (__pSprite)
	{
		if (__pMoveAction)
		{
			// Stop the previous movement action.
			__pSprite->stopAction(__pMoveAction);
		}
		Vec2 currentPosition = __pSprite->getPosition();
		Vec2 newPosition = currentPosition;

		//Don't move too fast
		if (__xMove > speedLimit)
		{
			__xMove = speedLimit;
		}
		else if (__xMove < -speedLimit)
		{
			__xMove = -speedLimit;
		}

		if (__yMove > speedLimit)
		{
			__yMove = speedLimit;
		}
		else if (__yMove < -speedLimit)
		{
			__yMove = -speedLimit;
		}

		// Multiplying by dt should improve movement smoothness.
		float xMove = __xMove * 1000 * delta;
		float yMove = __yMove * 1000 * delta;

		//Dead zone for movement
		if (abs(xMove * 10) < 5)
		{
			xMove = 0;
		}

		if (abs(yMove * 10) < 5)
		{
			yMove = 0;
		}

		newPosition.x += xMove;
		newPosition.y += yMove;

		float hMargin = __pSprite->getBoundingBox().size.width / 2;
		float vMargin = __pSprite->getBoundingBox().size.height / 2;

		//Don't move too far
		if (newPosition.x < hMargin)
		{
			newPosition.x = hMargin;
		}
		else if (newPosition.x > __winSize.width - hMargin)
		{
			newPosition.x = __winSize.width - hMargin;
		}

		if (newPosition.y < vMargin)
		{
			newPosition.y = vMargin;
		}
		else if (newPosition.y > __winSize.height - vMargin)
		{
			newPosition.y = __winSize.height - vMargin;
		}

		//Count movement movement duration
		Vec2 moveDifference = currentPosition - newPosition;
		float distanceToMove = moveDifference.getLength();
		float moveDuration = distanceToMove / __speed;

		// Create the movement action
		__pMoveAction = MoveTo::create(moveDuration, newPosition);
		__pSprite->runAction(__pMoveAction);
	}
}

Balloon* Balloon::create(Scene* parent)
{
	auto *pRet = new(std::nothrow) Balloon();
	if (pRet && pRet->init(parent))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
};

