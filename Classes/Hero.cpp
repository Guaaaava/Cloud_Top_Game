#include"Hero.h"

bool Hero::init()
{
	if (!Sprite::init())return false;
	return true;
}
bool Samurai::init()
{
	if (!Sprite::init())return false;
	return true;
}
bool Knight::init()
{
	if (!Sprite::init())return false;
	return true;
}
Animation* Samurai::createPlistAnimation(std::string filename,int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	sprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(sprite);
	sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void Samurai::heroRun(float x, float y)
{
	//ͨ��plist�ļ�����֡����
	run=createPlistAnimation("Samurai/Samurai_Run.plist",8);
	auto animate = Animate::create(run);
	sprite->runAction(RepeatForever::create(animate)); // ������ͣ����
	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, Vec2(x, y)); // ʱ�䡢Ŀ��λ��
	sprite->runAction(moveTo);
}

void Samurai::heroAttack()
{
	//ͨ��plist�ļ�����֡����
	attack=createPlistAnimation("Samurai/Samurai_Attack.plist", 4);
	auto animate = Animate::create(attack);
	auto animateforever = RepeatForever::create(animate);
	sprite->runAction(animate);//������ͣ����
}
void Samurai::heroDead()
{
	//ͨ��plist�ļ�����֡����
	dead=createPlistAnimation("Samurai/Samurai_Dead.plist", 6);
	
	auto animate = Animate::create(dead);
	sprite->runAction(animate);
}

Animation* Knight::createPlistAnimation(std::string filename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	sprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(sprite);
	sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}

void Knight::heroAttack()
{
	//ͨ��plist�ļ�����֡����
	attack=createPlistAnimation("Knight/Knight_Attack.plist", 4);
	auto animate = Animate::create(attack);
	auto animateforever = RepeatForever::create(animate);
	sprite->runAction(animateforever);//������ͣ����
}

void Knight::heroDead()
{
	//ͨ��plist�ļ�����֡����
	dead=createPlistAnimation("Knight/Knight_Dead.plist", 6);

	auto animate = Animate::create(dead);
	sprite->runAction(animate);
}
void Knight::heroRun(float x, float y)
{
	//ͨ��plist�ļ�����֡����
	run=createPlistAnimation("Knight/Knight_Run.plist", 7);
	auto animate = Animate::create(run);
	sprite->runAction(RepeatForever::create(animate)); // ������ͣ����
	// �����ƶ�����
	MoveBy* moveBy = MoveBy::create(3, Vec2(x, y)); // ʱ�䡢λ������
	sprite->runAction(moveBy); // ��ʼ�ƶ���ֹͣ���������ж���
}