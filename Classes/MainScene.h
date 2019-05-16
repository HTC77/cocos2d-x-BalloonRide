#ifndef __Balloonride__MainScene__
#define __Balloonride__MainScene__

#include "cocos2d.h"
#include "Balloon.h"
USING_NS_CC;

class MainScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
	void menuCloseCallback(Ref* pSender);

    CREATE_FUNC(MainScene);

	void update(float delta) override;
	void onEnter() override;
	
	void didAccelerate(Acceleration* acceleration, Event* event);
private:
	/**
	* Player controlled character.
	*/
	Balloon* 				__pBalloon;

	/**
	* Displays current score.
	*/
	Label*					__pScoreLabel;
	
	/**
	* Current score value.
	*/
	int						__score;
	
	/**
	* First element of a moving background.
	*/
	Sprite* 				__pBg1;

	/**
	* Second element of a moving background.
	*/
	Sprite* 				__pBg2;

	/**
	* Third element of a moving background.
	*/
	Sprite* 				__pBg3;
	void updateBgPosition(cocos2d::CCSprite* pBg);
	void updateBackground();
};

#endif // __Balloonride__MainScene__
