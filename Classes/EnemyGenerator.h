#ifndef __BalloonRide__EnemyGenerator__
#define __BalloonRide__EnemyGenerator__

#include "cocos2d.h"
USING_NS_CC;

class EnemyGenerator : public Node
{
public:
	EnemyGenerator();
	virtual bool init(Scene* parent);

	static EnemyGenerator* create(Scene* parent);

	void onEnter() override;

	Vector<Node*> getEnemies();
private:
	/**
	* Generated objects will be added as children of this layer.
	* It should be the MainLayer.
	*/
	Scene*	 				__pParent;

	/**
	* Holds generated enemy objects.
	*/
	Vector<Node*>	  		__pEnemies;

	/**
	* Size of the screen.
	*/
	Size					__winSize;

	/**
	* This value is increased with every new enemy.
	*/
	float					__enemySpeed;

	void generate(float deta);
};

#endif // __BalloonRide__EnemyGenerator__
