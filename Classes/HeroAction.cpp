#include"HeroAction.h"

bool HeroAction::init()
{
	if (!Scene::init())return false;

	 //��ʾ����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Samurai/Samurai_Run.plist");
	Sprite* SamuraiSprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(SamuraiSprite);
	SamuraiSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= 8; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	//������������
	Animation* animation = Animation::createWithSpriteFrames(images, 1.f / 8);
	auto animate = Animate::create(animation);
	SamuraiSprite->runAction(RepeatForever::create(animate));//������ͣ����


	//�ƶ�
	MoveBy* moveBy = MoveBy::create(3, Vec2(500, 0));//ʱ�䣬λ������
	SamuraiSprite->runAction(moveBy);
	 return true;
}


void HeroAction::heroRun()
{
	//ͨ��plist�ļ�����֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Samurai/Samurai_Run.plist");
	Sprite* SamuraiSprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(SamuraiSprite);
	SamuraiSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= 8; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	//������������
	Animation* animation = Animation::createWithSpriteFrames(images, 1.f / 8);
	auto animate = Animate::create(animation);
	SamuraiSprite->runAction(RepeatForever::create(animate));//������ͣ����


	//�ƶ�
	MoveBy* moveBy = MoveBy::create(3, Vec2(500, 0));//ʱ�䣬λ������
	SamuraiSprite->runAction(moveBy);
}