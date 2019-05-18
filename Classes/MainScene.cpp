#include "MainScene.h"

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("balloons.plist");

	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Create the score label.
	__pScoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 30);
	// Position the label on the center of the screen.
	__pScoreLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 20));
	// Add the label as a child to this layer.
	this->addChild(__pScoreLabel, 2);

	// Create the background sprites.
	__pBg1 = Sprite::createWithSpriteFrameName("bg.png");
	// Change the anchor point for convenience.
	__pBg1->setAnchorPoint(Vec2(0, 0));
	__pBg1->setPosition(Vec2(0, 0));

	float bgWidth = __pBg1->getContentSize().width;
	__pBg2 = Sprite::createWithSpriteFrameName("bg.png");
	__pBg2->setAnchorPoint(Vec2(0, 0));
	// Position the second sprite directly after the first.
	__pBg2->setPosition(Vec2(bgWidth - 1, 0));

	__pBg3 = Sprite::createWithSpriteFrameName("bg.png");
	__pBg3->setAnchorPoint(Vec2(0, 0));
	// Position the third sprite directly after the second.
	__pBg3->setPosition(Vec2(2 * (bgWidth - 1), 0));

	this->addChild(__pBg1, 0);
	this->addChild(__pBg2, 0);
	this->addChild(__pBg3, 0);

    return true;
}

void MainScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainScene::update(float delta)
{
	updateBackground();
	updateScore();
}

void MainScene::onEnter()
{
	// Remember to call the parent method first.
	Scene::onEnter();

	__pBalloon = Balloon::create(this);

	__pEnemyGenerator = EnemyGenerator::create(this);
	
	// This method will schedule updates with every frame. This will call update() callback method.
	scheduleUpdate();

	// Enable accelerometer
	Device::setAccelerometerEnabled(true);
	// Add Accelerometer listener
	auto accelerateListener = EventListenerAcceleration::create(
		CC_CALLBACK_2(MainScene::didAccelerate, this));
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		accelerateListener, this);
}

void MainScene::didAccelerate(Acceleration* acceleration, Event* event)
{
	__pBalloon->setMove(acceleration->y, acceleration->x);
}

void MainScene::updateBgPosition(Sprite* pBg)
{
	if (pBg)
	{
		Vec2 bgPos = pBg->getPosition();
		bgPos.x -= 1;
		float bgWidth = pBg->getBoundingBox().size.width;
		if (bgPos.x < -bgWidth)
		{
			bgPos.x = 2 * bgWidth - 4;
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			pBg->retain();
			this->removeChild(pBg, false);
			this->addChild(pBg);
		};
		pBg->setPosition(bgPos);
	}
}

void MainScene::updateBackground()
{
	updateBgPosition(__pBg1);
	updateBgPosition(__pBg2);
	updateBgPosition(__pBg3);
}

void MainScene::updateScore()
{
	__score += 1;
	const int labelLength = 100;
	char scoreLabelText[labelLength];
	snprintf(scoreLabelText, labelLength, "Score: %d", __score);
	if (__score % 10 == 0)
	{
		__pScoreLabel->setString(scoreLabelText);
	}
}