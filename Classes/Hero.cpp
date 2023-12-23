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
	sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void Samurai::heroRun(float x, float y)
{
	//通过plist文件创建帧动画
	run=createPlistAnimation("Samurai/Samurai_Run.plist",8);
	auto animate = Animate::create(run);
	sprite->runAction(RepeatForever::create(animate)); // 动画不停播放
	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, Vec2(x, y)); // 时间、目标位置
	sprite->runAction(moveTo);
}

void Samurai::heroAttack()
{
	//通过plist文件创建帧动画
	attack=createPlistAnimation("Samurai/Samurai_Attack.plist", 4);
	auto animate = Animate::create(attack);
	auto animateforever = RepeatForever::create(animate);
	sprite->runAction(animate);//动画不停播放
}
void Samurai::heroDead()
{
	//通过plist文件创建帧动画
	dead=createPlistAnimation("Samurai/Samurai_Dead.plist", 6);
	
	auto animate = Animate::create(dead);
	sprite->runAction(animate);
}

Animation* Knight::createPlistAnimation(std::string filename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	sprite = Sprite::createWithSpriteFrameName("1");
	this->addChild(sprite);
	sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}

void Knight::heroAttack()
{
	//通过plist文件创建帧动画
	attack=createPlistAnimation("Knight/Knight_Attack.plist", 4);
	auto animate = Animate::create(attack);
	auto animateforever = RepeatForever::create(animate);
	sprite->runAction(animateforever);//动画不停播放
}

void Knight::heroDead()
{
	//通过plist文件创建帧动画
	dead=createPlistAnimation("Knight/Knight_Dead.plist", 6);

	auto animate = Animate::create(dead);
	sprite->runAction(animate);
}
void Knight::heroRun(float x, float y)
{
	//通过plist文件创建帧动画
	run=createPlistAnimation("Knight/Knight_Run.plist", 7);
	auto animate = Animate::create(run);
	sprite->runAction(RepeatForever::create(animate)); // 动画不停播放
	// 创建移动动作
	MoveBy* moveBy = MoveBy::create(3, Vec2(x, y)); // 时间、位移向量
	sprite->runAction(moveBy); // 开始移动和停止动画的序列动作
}