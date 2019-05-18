#include "AnimatedObject.h"

AnimatedObject::AnimatedObject():
__pSpriteSheet(NULL),
__pSprite(NULL),
__pAnimationAction(NULL)
{
}

/**
* This initializing method should be used if game object has animation frames.
* It loads a new sprite sheet for the game object, if it isn't already loaded.
* Next it creates animation frames using the sprite sheet.
* After that, it creates a new sprite and adds it as a child of the sprite sheet.
*
* @param textureFileName Name of a file containing game object textures.
* @param frameNamePrefix Frames are described in plist file in "prefixNumber" format, e.g. "balloon2.png".
* 						  This param describes the prefix, e.g. "balloon".
* @param frameCount	  The number of animation frames.
* @param delay			  Time in seconds between animation frames.
* @param parent			  Parent that will hold the sprite sheet.
* @param spriteSheetTag  Tag describing the sprite sheet.
*/
void AnimatedObject::init(std::string textureFileName,
	std::string frameNamePrefix,
	int frameCount, float delay,
	Scene* parent, AnimTag spriteSheetTag)
{
	// Get the sprite sheet.
	__pSpriteSheet = dynamic_cast<SpriteBatchNode*>(parent->getChildByTag(spriteSheetTag));
	if (__pSpriteSheet == NULL)
	{
		// Create a new sprite sheet if it doesn't exit.
		const char* textureFileNameC = textureFileName.c_str();
		__pSpriteSheet = SpriteBatchNode::create(textureFileNameC);
		__pSpriteSheet->setTag(spriteSheetTag);
		parent->addChild(__pSpriteSheet, 1);
	}

	// Get animation frames.
	for (int i = 1; i <= frameCount; ++i)
	{
		std::string f = "%s%d.png";
		auto frameName = StringUtils::format(f.c_str(), frameNamePrefix.c_str(), i);
		const auto frameNameC = static_cast<const char*>(frameName.c_str());
		const auto spriteFrame =
			SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNameC);
		__pAnimationFrames.pushBack(spriteFrame);
	}

	// Create animation
	auto animation = Animation::createWithSpriteFrames(__pAnimationFrames, delay);
	__pAnimationAction = RepeatForever::create(Animate::create(animation));

	auto size = Director::getInstance()->getWinSize();
	std::string f = "%s1.png";
	auto frameName = StringUtils::format(f.c_str(), frameNamePrefix.c_str());

	// Create game object sprite and add it to the sprite sheet.
	const auto frameNameC = frameName.c_str();
	__pSprite = Sprite::createWithSpriteFrameName(frameNameC);
	__pSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	__pSprite->runAction(__pAnimationAction);
	__pSpriteSheet->addChild(__pSprite);
}

/**
* This initializing method should be used if game object doesn't have animation frames.
* It loads a new sprite sheet for the game object, if it isn't already loaded.
* After that, it creates a new sprite and adds it as a child of the sprite sheet.
*
* @param textureFileName Name of a file containing game object textures.
* @param parent			  Layer that will hold the sprite sheet.
* @param spriteSheetTag  Tag describing the sprite sheet.
*/
void AnimatedObject::init(
	__String textureFileName,
	Scene* parent,
	AnimTag spriteSheetTag)
{
	//Get the sprite sheet.
	__pSpriteSheet = dynamic_cast<SpriteBatchNode*>(parent->getChildByTag(spriteSheetTag));
	if (__pSpriteSheet == NULL)
	{
		//Create a new sprite sheet if it doesn't exit.
		__pSpriteSheet = SpriteBatchNode::create(textureFileName.getCString());
		__pSpriteSheet->setTag(spriteSheetTag);
		parent->addChild(__pSpriteSheet, 1);
	}

	auto size = Director::getInstance()->getWinSize();

	//Create game object sprite and add it to the sprite sheet.
	__pSprite = Sprite::create(textureFileName.getCString());
	__pSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	__pSpriteSheet->addChild(__pSprite);
}

void AnimatedObject::setPosition(Vec2 pos)
{
	__pSprite->setPosition(pos);
}

Size& AnimatedObject::getSize()
{
	return __pSprite->getBoundingBox().size;
}
