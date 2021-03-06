#ifndef __Balloonride__MainScene__
#define __Balloonride__MainScene__

#include "cocos2d.h"
#include "Balloon.h"
#include "EnemyGenerator.h"
#include "Enemy.h"
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
	* Generates birds and planes.
	*/
	EnemyGenerator*			__pEnemyGenerator;

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
	void updateBgPosition(Sprite* pBg);
	void updateBackground();
	void updateScore();
	void updateEnemies(Rect balloonRect, Vector<Node*> pEnemies);
};

#endif // __Balloonride__MainScene__
