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
	//else if (_mp >= _max_mp)
	//{
	//	_sprite->setVisible(false); // 隐藏精灵
	//	//this->MonsterSkill();
	//	this->getHurted();
	//	_mp = 0; // 重置 mp
	//}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->monsterAttack();
		this->getHurted();
		_mp++;
	}
}
void Monster::createHealthBar()
{
	// 创建头顶血条
	_healthBar = ProgressTimer::create(Sprite::create("StatusBar/HealthBar.png"));
	_healthBar->setLocalZOrder(10000);
	// 设置透明度
	//_healthBar->setOpacity(255);

	_healthBar->setType(ProgressTimerType::BAR);
	_healthBar->setMidpoint(Vec2(0, 0.5));
	_healthBar->setBarChangeRate(Vec2(1, 0));
	_healthBar->setPercentage(100.0f);  // 初始为满血
	_healthBar->setAnchorPoint(Vec2(0, 0.5)); // 设置锚点在血条的左侧中间
	// 获取英雄的锚点
	Vec2 anchorPoint = _postion;
	// 计算血条的位置（在锚点上方）
	//Vec2 healthBarPosition = Vec2(this->getContentSize().width * anchorPoint.x,
		//this->getContentSize().height * (1.0 + anchorPoint.y));
	Vec2 healthBarPosition = Vec2(anchorPoint.x - 60, anchorPoint.y + 100);
	_healthBar->setPosition(healthBarPosition);
	_healthBar->setScaleY(0.5f);
	//_healthBar->setPosition(Vec2(100, 100));
	this->addChild(_healthBar);
}

void Monster::updateHealthBarPosition()
{
	// 更新血条位置

	if (_healthBar)
	{
		_healthBar->setPosition(Vec2(0, _sprite->getContentSize().height));
		_healthBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
	}

	// 更新头顶血条位置
	//_healthBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
}
void Monster::updateHealthBar(float dt) {
	// 模拟英雄的血量变化（实际中应根据游戏逻辑处理）
	_hp -= 1;

	// 更新血条显示
	float healthPercentage;
	if (_hp <= 0)
		healthPercentage = 0;
	else
		healthPercentage = static_cast<float>(_hp) / _max_hp * 100.0f;
	_healthBar->setScaleX(healthPercentage / 100.0f);

	// 如果血量小于等于0，可以在这里执行相应的逻辑，比如英雄死亡
	if (_hp <= 0) {
		unschedule(CC_SCHEDULE_SELECTOR(Monster::updateHealthBar));
		// 在这里执行相应的逻辑，比如游戏结束等
	}
}

void Monster::createMagicBar()
{
	// 创建头顶蓝条
	_magicBar = ProgressTimer::create(Sprite::create("StatusBar/MagicBar.png"));
	_magicBar->setLocalZOrder(10000);
	// 设置透明度
	//_magicBar->setOpacity(255);

	_magicBar->setType(ProgressTimerType::BAR);
	_magicBar->setMidpoint(Vec2(0, 0.5));
	_magicBar->setBarChangeRate(Vec2(1, 0));
	_magicBar->setPercentage(100.0f);  // 初始为满血
	_magicBar->setAnchorPoint(Vec2(0, 0.5)); // 设置锚点在蓝条的左侧中间
	// 获取英雄的锚点
	Vec2 anchorPoint = _postion;
	// 计算蓝条的位置（在锚点上方）
	Vec2 healthBarPosition = Vec2(anchorPoint.x - 60, anchorPoint.y + 90);
	_magicBar->setPosition(healthBarPosition);
	_magicBar->setScaleY(0.5f);
	//_magicBar->setPosition(Vec2(100, 100));
	this->addChild(_magicBar);
}

void Monster::updateMagicBarPosition()
{
	// 更新蓝条位置

	if (_magicBar)
	{
		_magicBar->setPosition(Vec2(0, _sprite->getContentSize().height));
		_magicBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
	}
}

void Monster::updateMagicBar(float dt) {
	// 模拟英雄的蓝量变化（实际中应根据游戏逻辑处理）

	// 更新蓝条显示
	float magicPercentage;
	if (_mp <= 0)
		magicPercentage = 0;
	else
		magicPercentage = static_cast<float>(_mp) / _max_mp * 100.0f;
	_magicBar->setScaleX(magicPercentage / 100.0f);
}


/****************************************************
 * 功能：BlueSlime类成员函数
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：牟泳祯
 ****************************************************/
bool BlueSlime::init(Vec2& start_pos)
{
	if (!Monster::init())return false;
	_postion = start_pos;
	_hp = 290;
	_ap = 15;
	_mp = 0;
	_lv = 1;
	_max_mp = 4;
	//skill_ap = 1.5 * _ap;
	this->createHealthBar();
	//this->createMagicBar();
	return true;
}


void BlueSlime::monsterAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("BlueSlime/BlueSlime_Attack.plist", "_BlueSlime_Attack", 4);
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
	_dead = createPlistAnimation("BlueSlime/BlueSlime_Dead.plist", "_BlueSlime_Dead", 3);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlueSlime::monsterRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("BlueSlime/BlueSlime_Run.plist", "_BlueSlime_Run", 7);
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
	MoveTo* healthBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 100));
	//MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));
	_postion = end_pos;//更新英雄坐标
	_healthBar->runAction(healthBarMoveTo);//
	//_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		monsterAction(); // 由monsterAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
