#include "Enemy.h"

Enemy::Enemy():__speed(0)
{
}

bool Enemy::init(float speed)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	__speed = speed;
    return true;
}

Enemy* Enemy::create(float speed)
{
	auto pRet = new(std::nothrow) Enemy();
	if (pRet && pRet->init(speed))
	{
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

/**
* This method start enemy movement action.
*/
void Enemy::go()
{
	float duration = Director::getInstance()->getWinSize().height / __speed;
	float x = -__pSprite->getBoundingBox().size.width - 5;
	FiniteTimeAction* actionMove = MoveTo::create(duration, Vec2(x, __pSprite->getPosition().y));
	__pSprite->runAction(actionMove);
}