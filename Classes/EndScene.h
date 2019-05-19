#ifndef __BalloonRide__EndScene__
#define __BalloonRide__EndScene__

#include "cocos2d.h"
USING_NS_CC;

class EndScene : public Scene
{
public:

	EndScene();
	static const int endLayerTag = 1;
    static Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(EndScene);

	void menuCloseCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void setFinalScore(int finalScore);
	void update(float delta);
	void onEnter();
private:
	/**
	* This label will show the final score.
	*/
	Label* 	__pFinalScoreLabel;
	/**
	* First element of a moving background.
	*/
	Sprite* 		__pBg1;

	/**
	* Second element of the moving background.
	*/
	Sprite* 		__pBg2;

	/**
	* Third element of the moving background.
	*/
	Sprite* 		__pBg3;

	void updateBgPosition(Sprite* pBg);
};

#endif // __BalloonRide__EndScene__
