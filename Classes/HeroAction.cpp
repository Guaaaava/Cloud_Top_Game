#include"HeroAction.h"

bool HeroAction::init()
{
	if (!Scene::init())return false;

	 //演示动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Samurai/Samurai_Run.plist");
	Sprite* SamuraiSprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(SamuraiSprite);
	SamuraiSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= 8; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	//创建动画对象
	Animation* animation = Animation::createWithSpriteFrames(images, 1.f / 8);
	auto animate = Animate::create(animation);
	SamuraiSprite->runAction(RepeatForever::create(animate));//动画不停播放


	//移动
	MoveBy* moveBy = MoveBy::create(3, Vec2(500, 0));//时间，位移向量
	SamuraiSprite->runAction(moveBy);
	 return true;
}


void HeroAction::heroRun()
{
	//通过plist文件创建帧动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Samurai/Samurai_Run.plist");
	Sprite* SamuraiSprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(SamuraiSprite);
	SamuraiSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= 8; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	//创建动画对象
	Animation* animation = Animation::createWithSpriteFrames(images, 1.f / 8);
	auto animate = Animate::create(animation);
	SamuraiSprite->runAction(RepeatForever::create(animate));//动画不停播放


	//移动
	MoveBy* moveBy = MoveBy::create(3, Vec2(500, 0));//时间，位移向量
	SamuraiSprite->runAction(moveBy);
}