#ifndef __BalloonRide__AnimatedObject__
#define __BalloonRide__AnimatedObject__

#include "cocos2d.h"
USING_NS_CC;

class AnimatedObject : public Node
{
public:

	void testme() {};
	AnimatedObject();

	/**
	* Tags used to indicate a sprite sheet.
	*/
	enum AnimTag
	{
		ANIM_BALLOON_SPRITESHEET,
		ANIM_PLANE_SPRITESHEET,
		ANIM_TWITTER_SPRITESHEET
	};

	void init(
		std::string textureFileName,
		std::string frameNamePrefix,
		int frameCount,
		float delay,
		Scene* parent,
		AnimTag spriteSheetTag);

	void init(
		__String textureFileName,
		Scene* parent,
		AnimTag spriteTag);

	void setPosition(Vec2 pos);
	Size& getSize();
protected:
	/**
	* Sprite sheet holding game object animation frames.
	*/
	SpriteBatchNode* 			__pSpriteSheet;

	/**
	* Array holding animation frames of game object sprite.
	*/
	Vector<SpriteFrame*> 		__pAnimationFrames;

	/**
	* Game object sprite.
	*/
	Sprite*						__pSprite;

	/**
	* Action describing game object animation.
	*/
	Action* 					__pAnimationAction;
};

#endif // __BalloonRide__AnimatedObject__
