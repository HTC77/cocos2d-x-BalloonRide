#include "EndScene.h"
#include "MainScene.h"

EndScene::EndScene():__pFinalScoreLabel(NULL),
__pBg1(NULL),
__pBg2(NULL),
__pBg3(NULL)
{
}

Scene* EndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EndScene::create();
	layer->setTag(endLayerTag);
	scene->addChild(layer);
    return scene;
}

bool EndScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto winSize = Director::sharedDirector()->getWinSize();

	// Create final score label.
	__pFinalScoreLabel = Label::createWithTTF ("Final score: 0!", "fonts/Marker Felt.ttf", 40);
	__pFinalScoreLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 20));
	this->addChild(__pFinalScoreLabel, 1);
	__pFinalScoreLabel->retain();

	// Create restart button.
	auto pRestartButton = MenuItemFont::create(
		"Restart",
		this,
		menu_selector(EndScene::menuRestartCallback));
	pRestartButton->setFontSizeObj(50);
	pRestartButton->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	// Create close button.
	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(EndScene::menuCloseCallback));
	pCloseItem->setPosition(Vec2(winSize.width - 20, 20));

	// create menu, it's an autorelease object
	auto pMenu = Menu::create(pRestartButton, pCloseItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);

	// Create the background sprites.
	__pBg1 = Sprite::createWithSpriteFrameName("bg.png");
	//Change the anchor point for convenience.
	__pBg1->setAnchorPoint(Vec2(0, 0));
	__pBg1->setPosition(Vec2(0, 0));

	float bgWidth = __pBg1->getContentSize().width;
	__pBg2 = Sprite::createWithSpriteFrameName("bg.png");
	__pBg2->setAnchorPoint(Vec2(0, 0));
	//Position the second sprite directly after the first.
	__pBg2->setPosition(Vec2(bgWidth - 1, 0));

	__pBg3 = Sprite::createWithSpriteFrameName("bg.png");
	__pBg3->setAnchorPoint(Vec2(0, 0));
	//Position the third sprite directly after the second.
	__pBg3->setPosition(Vec2(2 * (bgWidth - 1), 0));

	this->addChild(__pBg1, 0);
	this->addChild(__pBg2, 0);
	this->addChild(__pBg3, 0);
    return true;
}

void EndScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void EndScene::menuRestartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void EndScene::setFinalScore(int finalScore)
{
	const int labelLength = 100;
	char finalScoreLabelText[labelLength];
	snprintf(finalScoreLabelText, labelLength, "Final score: %d!", finalScore);
	__pFinalScoreLabel->setString(finalScoreLabelText);
}

void EndScene::update(float delta)
{
	updateBgPosition(__pBg1);
	updateBgPosition(__pBg2);
	updateBgPosition(__pBg3);
}

void EndScene::onEnter()
{
	// Remember to call the parent method.
	Scene::onEnter();
	// This method will schedule updates with every frame. This will call update() callback method.
	scheduleUpdate();
}

/**
* Move the background sprites.
* If a part is moved off the screen to left,
* it is moved back off the screen to the right.
*
* @param pBg The background sprite that should be moved.
*/
void EndScene::updateBgPosition(Sprite* pBg)
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

