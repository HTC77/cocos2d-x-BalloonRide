/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "MainScene.h"


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	auto center = Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	// Start menu
	auto startSceneItem = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::menuMainSceneCallback, this));
	startSceneItem->setPosition(center);
	menu->addChild(startSceneItem);
	startSceneItem->setFontSizeObj(50);

	// Background

	// Add background to cache.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		"background.plist", "bg_duplicate.png");
	// Create the background sprites.
	__pBg1 = Sprite::createWithSpriteFrameName("bg.png");
	// Change the anchor point for convenience.
	 __pBg1->setAnchorPoint(Vec2(0, 0));
	__pBg1->setPosition(Vec2(0, 0));

	 float bgWidth = __pBg1->getContentSize().width;
	 __pBg2 = Sprite::createWithSpriteFrameName("bg.png");
	 __pBg2->setAnchorPoint(Vec2(0, 0));
	 // Position the second sprite directly after the first (from left to right).
	 __pBg2->setPosition(Vec2(bgWidth - 1, 0));
	
	 __pBg3 = Sprite::createWithSpriteFrameName("bg.png");
	 __pBg3->setAnchorPoint(Vec2(0, 0));
	 // Position the third sprite directly after the second.
	 __pBg3->setPosition(Vec2(2 * (bgWidth - 1), 0));

	this->addChild(__pBg1, 0);
	this->addChild(__pBg2, 0);
	this->addChild(__pBg3, 0);

	this->scheduleUpdate();

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuMainSceneCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void HelloWorld::update(float delta)
{
	updateBgPosition(__pBg1);
	updateBgPosition(__pBg2);
	updateBgPosition(__pBg3);
}

void HelloWorld::updateBgPosition(Sprite* bg)
{
	if (bg)
	{
		Vec2 bgPos = bg->getPosition();
		bgPos.x -= 1;
		float bgWidth = bg->getContentSize().width;
		if (bgPos.x < -bgWidth)
		{
			bgPos.x = 2 * bgWidth - 4;
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			bg->retain();
			this->removeChild(bg, false);
			this->addChild(bg);
		};
		bg->setPosition(bgPos);
	}
}
