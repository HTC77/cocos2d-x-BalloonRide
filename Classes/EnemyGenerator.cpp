#include "EnemyGenerator.h"
#include "Enemy.h"


EnemyGenerator::EnemyGenerator()
	: __pParent(NULL),
	__enemySpeed(0)
{
}

/**
* Set balloon properties and schedule movement update.
* @param parent Layer that will hold sprites of generated objects.
*/
bool EnemyGenerator::init(Scene* parent)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	__winSize = Director::getInstance()->getWinSize();
	__pParent = parent;
	__pParent->addChild(this);
	__enemySpeed = 200.0f;
    return true;
}

EnemyGenerator* EnemyGenerator::create(Scene* parent)
{
	auto pRet = new(std::nothrow) EnemyGenerator();
	if (pRet && pRet->init(parent)) {
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void EnemyGenerator::onEnter()
{
	Node::onEnter();

	schedule(schedule_selector(EnemyGenerator::generate), 0.5f);
}

Vector<Node*> EnemyGenerator::getEnemies()
{
	return __pEnemies;
}

void EnemyGenerator::remove(Vector<Node*> pEnemies)
{
	for (auto enemy : pEnemies)
	{
		auto pEnemy = dynamic_cast<Enemy*>(enemy);
		pEnemy->destroy();
	}
	__pEnemies.eraseObjectsInArray(pEnemies);
}

void EnemyGenerator::generate(float deta)
{
	//create new enemy object
	auto enemy = Enemy::create(__enemySpeed);
	__enemySpeed += 1.0f;

	__String textureFileName = "plane.png";
	auto tag = AnimatedObject::ANIM_PLANE_SPRITESHEET;

	int r = rand() % 100;
	if (r > 50)
	{
		// Change enemy
		textureFileName = "twitter.png";
		tag = AnimatedObject::ANIM_TWITTER_SPRITESHEET;
	}

	enemy->init(textureFileName, __pParent, tag);

	// Choose random starting position
	auto enemySize = enemy->getSize();
	r = rand() % static_cast<int>(__winSize.height - enemySize.height) + enemySize.height / 2;
	float x = __winSize.width + enemySize.width;
	float y = r;
	enemy->setPosition(Vec2(x, y));
	__pEnemies.pushBack(enemy);
	__pParent->addChild(enemy);
	enemy->go();
}

