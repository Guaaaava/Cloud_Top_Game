#include "Monster.h"

bool Monster::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	return true;
}

Animation* Monster::createPlistAnimation(std::string filename, std::string framename, int photonums)
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

void Monster::monsterAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->monsterDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		//this->MonsterSkill();
		this->getHurted();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->monsterAttack();
		this->getHurted();
		_mp++;
	}
}
/****************************************************
 * 功能：BlackWerewolf类成员函数
 * _hp=320
 * _ap=13
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：卞思涵
 ****************************************************/
bool BlackWerewolf::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 320;
	_ap = 13;
	_mp = 0;
	_lv = 1;
	_max_mp = 4;
	_skill_ap = 1.5 * _ap;
	return true;
}


void BlackWerewolf::monsterAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("BlackWerewolf/BlackWerewolf_Attack.plist", "_BlackWerewolf_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->monsterAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);
}
void BlackWerewolf::monsterDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("BlackWerewolf/BlackWerewolf_Dead.plist", "_BlackWerewolf_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlackWerewolf::monsterRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("BlackWerewolf/BlackWerewolf_Run.plist", "_BlackWerewolf_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// 翻转精灵
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画

	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		monsterAction(); // 由monsterAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：SkeletonWarrior类成员函数
 * _hp=350
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=5
 * 作者：卞思涵
 ****************************************************/
bool SkeletonWarrior::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 350;
	_ap = 8;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_skill_ap = 1.5 * _ap;
	return true;
}

void SkeletonWarrior::monsterAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Attack.plist", "_SkeletonWarrior_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->monsterAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}

void SkeletonWarrior::monsterDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Dead.plist", "_SkeletonWarrior_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void SkeletonWarrior::monsterRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Run.plist", "_SkeletonWarrior_Run", 7);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// 翻转精灵
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画

	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		monsterAction(); // 由monsterAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：BlueSlime类成员函数
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：卞思涵
 ****************************************************/
bool BlueSlime::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 290;
	_ap = 15;
	_mp = 0;
	_lv = 1;
	_max_mp = 4;
	_skill_ap = 1.5 * _ap;
	return true;
}


void BlueSlime::monsterAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("BlueSlime/BlueSlime_Attack.plist", "_BlueSlime_Attack", 6);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->monsterAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}

void BlueSlime::monsterDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("BlueSlime/BlueSlime_Dead.plist", "_BlueSlime_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlueSlime::monsterRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("BlueSlime/BlueSlime_Run.plist", "_BlueSlime_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// 翻转精灵
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // 播放跑步动画

	// 创建移动动作
	MoveTo* moveTo = MoveTo::create(3, end_pos); // 移动到目标位置
	_postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		monsterAction(); // 由monsterAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
