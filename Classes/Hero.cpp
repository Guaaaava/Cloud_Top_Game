#include"Hero.h"

bool Hero::init(Vec2& start_pos )
{
	if (!Sprite::init())return false;
	return true;
}


/****************************************************
 * 功能：Samurai类成员函数
 * 作者：卞思涵
 ****************************************************/
bool Samurai::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	return true;
}

Animation* Samurai::createPlistAnimation(std::string filename,std::string framename,int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1"+framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


//void Samurai::heroRun(Vec2&end_pos)
//{
//	//通过plist文件创建帧动画
//	_run=createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run",8);
//	auto animate = Animate::create (_run);
//	_sprite->runAction(RepeatForever::create(animate)); // 动画不停播放
//	// 创建移动动作
//	MoveTo* moveTo = MoveTo::create(3, end_pos); // 时间、目标位置
//	_sprite->runAction(moveTo);
//	_postion = end_pos;//更新英雄坐标
//}

void Samurai::heroAttack()
{

	//通过plist文件创建帧动画
	_attack=createPlistAnimation("Samurai/Samurai_Attack.plist","_Samurai_Attack", 4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//动画不停播放
}
void Samurai::heroDead()
{
	//通过plist文件创建帧动画
	_dead=createPlistAnimation("Samurai/Samurai_Dead.plist", "_Samurai_Dead", 6);
	
	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Samurai::heroRunAndAttack(Vec2& end_pos)
{
    // 通过plist文件创建帧动画
    _run = createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run", 8);
    auto runAnimate = Animate::create(_run);
    auto runAction = RepeatForever::create(runAnimate);
    _sprite->runAction(runAction); // 播放跑步动画

    // 创建移动动作
    MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
    auto moveCallback = CallFunc::create([this]() {
        _sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
        heroAttack(); // 播放攻击动画
    });
    auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
    _sprite->runAction(sequence);
}
/****************************************************
 * 功能：Knight类成员函数
 * 作者：卞思涵
 ****************************************************/
bool Knight::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	return true;
}

Animation* Knight::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}

//void Knight::heroRun(Vec2& end_pos)
//{
//	//通过plist文件创建帧动画
//	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
//	auto animate = Animate::create(_run);
//	_sprite->runAction(RepeatForever::create(animate)); // 动画不停播放
//	// 创建移动动作
//	MoveBy* moveBy = MoveBy::create(3, end_pos); // 时间、位移向量
//	_sprite->runAction(moveBy); // 开始移动和停止动画的序列动作
//	_postion = end_pos;//更新英雄坐标
//}
void Knight::heroAttack()
{
	//通过plist文件创建帧动画
	_attack=createPlistAnimation("Knight/Knight_Attack.plist","_Knight_Attack",4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever->clone());//动画不停播放
	//sprite->runAction(Sequence::createWithTwoActions(
	//	Repeat::create(animate, 3),
	//	CallFunc::create([sprite]() {sprite->removeFromParent();
	//		})
	//));

}

void Knight::heroDead()
{
	//通过plist文件创建帧动画
	_dead=createPlistAnimation("Knight/Knight_Dead.plist", "_Knight_Dead", 6);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Knight::heroRunAndAttack(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画
	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAttack(); // 播放攻击动画
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}

/****************************************************
 * 功能：Kunoichi类成员函数
 * 作者：卞思涵
 ****************************************************/
bool Kunoichi::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;

	return true;
}
Animation* Kunoichi::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void Kunoichi::heroAttack()
{

	//通过plist文件创建帧动画
	_attack = createPlistAnimation("Kunoichi/Kunoichi_Attack.plist", "_Kunoichi_Attack", 6);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//动画不停播放
}
void Kunoichi::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("Kunoichi/Kunoichi_Dead.plist", "_Kunoichi_Dead", 5);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Kunoichi::heroRunAndAttack(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Kunoichi/Kunoichi_Run.plist", "_Kunoichi_Run", 8);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画

	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAttack(); // 播放攻击动画
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：LightningMage类成员函数
 * 作者：卞思涵
 ****************************************************/
bool LightningMage::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;

	return true;
}
Animation* LightningMage::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void LightningMage::heroAttack()
{

	//通过plist文件创建帧动画
	_attack = createPlistAnimation("LightningMage/LightningMage_Attack.plist", "_LightningMage_Attack", 4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//动画不停播放
}
void LightningMage::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("LightningMage/LightningMage_Dead.plist", "_LightningMage_Dead", 5);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void LightningMage::heroRunAndAttack(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("LightningMage/LightningMage_Run.plist", "_LightningMage_Run", 8);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画

	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAttack(); // 播放攻击动画
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}