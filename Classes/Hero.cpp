#include"Hero.h"

void Hero::initPos(Vec2 start_pos)
{
}

Animation* Hero::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;

	_sprite->setScale(_lv);//放大_lv倍

	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}

void Hero::heroAction()
{
	if (_hp <= 0)
	{
		_mp = 0;
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		schedule(CC_SCHEDULE_SELECTOR(Samurai::updateHealthBar), 0.1f);
		schedule(CC_SCHEDULE_SELECTOR(Samurai::updateMagicBar), 0.1f);
		this->heroSkill();
		this->getHurted();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		schedule(CC_SCHEDULE_SELECTOR(Samurai::updateHealthBar), 0.1f);
		schedule(CC_SCHEDULE_SELECTOR(Samurai::updateMagicBar), 0.1f);
		this->heroAttack();
		this->getHurted();
		_mp++;
	}
}


void Hero::createHealthBar()
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

void Hero::updateHealthBarPosition()
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

void Hero::updateHealthBar(float dt) {
	// 更新血条显示
	float healthPercentage;
	if (_hp <= 0)
		healthPercentage = 0;
	else
		healthPercentage = static_cast<float>(_hp) / _max_hp * 100.0f;
	_healthBar->setScaleX(healthPercentage / 100.0f);

	// 如果血量小于等于0，可以在这里执行相应的逻辑，比如英雄死亡
	if (_hp <= 0) {
		unschedule(CC_SCHEDULE_SELECTOR(Hero::updateHealthBar));
		// 在这里执行相应的逻辑，比如游戏结束等
	}
}

void Hero::createMagicBar()
{
	// 创建头顶蓝条
	_magicBar = ProgressTimer::create(Sprite::create("StatusBar/MagicBar.png"));
	_magicBar->setLocalZOrder(10000);
	// 设置透明度


	_magicBar->setType(ProgressTimerType::BAR);
	_magicBar->setMidpoint(Vec2(0, 0.5));
	_magicBar->setBarChangeRate(Vec2(1, 0));
	_magicBar->setPercentage(100);  // 初始为满血
	_magicBar->setOpacity(0);
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

void Hero::updateMagicBarPosition()
{
	// 更新蓝条位置

	if (_magicBar)
	{
		_magicBar->setPosition(Vec2(0, _sprite->getContentSize().height));
		_magicBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
	}
}

void Hero::updateMagicBar(float dt) {
	// 模拟英雄的蓝量变化（实际中应根据游戏逻辑处理）

	// 更新蓝条显示
	float magicPercentage;
	if (_mp < 0)
		magicPercentage = 0;
	else if (_mp > _max_mp)
		magicPercentage = _max_mp;
	else
		magicPercentage = static_cast<float>(_mp) / _max_mp * 100.0f;
	_magicBar->setOpacity(255);
	_magicBar->setScaleX(magicPercentage / 100.0f);
}

/****************************************************
 * 功能：Samurai类成员函数
 * _hp=320
 * _ap=13
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：卞思涵
 ****************************************************/
void Samurai::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}


void Samurai::heroAttack()
{
		// 创建攻击帧动画并绑定回调函数
		_attack = createPlistAnimation("Samurai/Samurai_Attack.plist", "_Samurai_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {
		
		this->heroAction(); 
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);
}
void Samurai::heroSkill()
{
	   _skill= createPlistAnimation("Samurai/Samurai_Skill.plist", "_Samurai_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack(); 
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);
	
}
void Samurai::heroDead()
{
	//通过plist文件创建帧动画
	_dead=createPlistAnimation("Samurai/Samurai_Dead.plist", "_Samurai_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Samurai::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();

    // 通过plist文件创建帧动画
    _run = createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));
	
	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);

    auto moveCallback = CallFunc::create([this]() {
        _sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
        heroAction(); // 由heroAction动画进行选择播放
    });
    auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
    _sprite->runAction(sequence);
}
/****************************************************
 * 功能：Knight类成员函数
 * _hp=350
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=5
 * 作者：卞思涵
 ****************************************************/
void Knight::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void Knight::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("Knight/Knight_Attack.plist", "_Knight_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void Knight::heroSkill()
{
	_skill = createPlistAnimation("Knight/Knight_Skill.plist", "_Knight_Skill", 6);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Knight::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("Knight/Knight_Dead.plist", "_Knight_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Knight::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：Kunoichi类成员函数
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：卞思涵
 ****************************************************/
void Kunoichi::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}


void Kunoichi::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("Kunoichi/Kunoichi_Attack.plist", "_Kunoichi_Attack", 6);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void Kunoichi::heroSkill()
{
	_skill = createPlistAnimation("Kunoichi/Kunoichi_Skill.plist", "_Kunoichi_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Kunoichi::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("Kunoichi/Kunoichi_Dead.plist", "_Kunoichi_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Kunoichi::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Kunoichi/Kunoichi_Run.plist", "_Kunoichi_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：LightningMage类成员函数
 * _hp=280
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.7*_ap
 * _max_mp=5
 * 作者：卞思涵
 ****************************************************/
void LightningMage::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}



void LightningMage::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("LightningMage/LightningMage_Attack.plist", "_LightningMage_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void LightningMage::heroSkill()
{
	_skill = createPlistAnimation("LightningMage/LightningMage_Skill.plist", "_LightningMage_Skill", 9);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void LightningMage::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("LightningMage/LightningMage_Dead.plist", "_LightningMage_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void LightningMage::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("LightningMage/LightningMage_Run.plist", "_LightningMage_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：FireVizard类成员函数
 * _hp=300
 * _ap=16
 * _mp=0
 * _lv=1
 *_skill_ap=2.5*_ap
 * _max_mp=6
 * 作者：卞思涵
 ****************************************************/
void FireVizard::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}



void FireVizard::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("FireVizard/FireVizard_Attack.plist", "_FireVizard_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void FireVizard::heroSkill()
{
	_skill = createPlistAnimation("FireVizard/FireVizard_Skill.plist", "_FireVizard_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void FireVizard::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("FireVizard/FireVizard_Dead.plist", "_FireVizard_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void FireVizard::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("FireVizard/FireVizard_Run.plist", "_FireVizard_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo); _postion = end_pos;//更新英雄坐标
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：WandererMagican类成员函数
 * _hp=280
 * _ap=17
 * _mp=0
 * _lv=1
 *_skill_ap=2*_ap
 * _max_mp=5
 * 作者：卞思涵
 ****************************************************/
void WandererMagican::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void WandererMagican::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("WandererMagican/WandererMagican_Attack.plist", "_WandererMagican_Attack", 6);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void WandererMagican::heroSkill()
{
	_skill = createPlistAnimation("WandererMagican/WandererMagican_Skill.plist", "_WandererMagican_Skill", 7);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void WandererMagican::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("WandererMagican/WandererMagican_Dead.plist", "_WandererMagican_Dead", 4);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void WandererMagican::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("WandererMagican/WandererMagican_Run.plist", "_WandererMagican_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：NinjaMonk类成员函数
 * _hp=300
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.1*_ap
 * _max_mp=2
 * 作者：卞思涵
 ****************************************************/
void NinjaMonk::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void NinjaMonk::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("NinjaMonk/NinjaMonk_Attack.plist", "_NinjaMonk_Attack", 5);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void NinjaMonk::heroSkill()
{
	_skill = createPlistAnimation("NinjaMonk/NinjaMonk_Skill.plist", "_NinjaMonk_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void NinjaMonk::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("NinjaMonk/NinjaMonk_Dead.plist", "_NinjaMonk_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void NinjaMonk::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("NinjaMonk/NinjaMonk_Run.plist", "_NinjaMonk_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：NinjaPeasant类成员函数
 * _hp=300
 * _ap=9
 * _mp=0
 * _lv=1
 *_skill_ap=1.2*_ap
 * _max_mp=3
 * 作者：卞思涵
 ****************************************************/
void NinjaPeasant::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void NinjaPeasant::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("NinjaPeasant/NinjaPeasant_Attack.plist", "_NinjaPeasant_Attack", 6);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void NinjaPeasant::heroSkill()
{
	_skill = createPlistAnimation("NinjaPeasant/NinjaPeasant_Skill.plist", "_NinjaPeasant_Skill", 4);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void NinjaPeasant::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("NinjaPeasant/NinjaPeasant_Dead.plist", "_NinjaPeasant_Dead", 4);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void NinjaPeasant::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("NinjaPeasant/NinjaPeasant_Run.plist", "_NinjaPeasant_Run", 6);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：SamuraiCommander类成员函数
 * _hp=320
 * _ap=10
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * 作者：卞思涵
 ****************************************************/
void SamuraiCommander::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void SamuraiCommander::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("SamuraiCommander/SamuraiCommander_Attack.plist", "_SamuraiCommander_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void SamuraiCommander::heroSkill()
{
	_skill = createPlistAnimation("SamuraiCommander/SamuraiCommander_Skill.plist", "_SamuraiCommander_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void SamuraiCommander::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("SamuraiCommander/SamuraiCommander_Dead.plist", "_SamuraiCommander_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void SamuraiCommander::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("SamuraiCommander/SamuraiCommander_Run.plist", "_SamuraiCommander_Run", 8);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：Berserker类成员函数
 * _hp=200
 * _ap=20
 * _mp=0
 * _lv=1
 *_skill_ap=2*_ap
 * _max_mp=3
 * 作者：卞思涵
 ****************************************************/
void Berserker::initPos(Vec2 start_pos)
{
	_postion = start_pos;
}

void Berserker::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("Berserker/Berserker_Attack.plist", "_Berserker_Attack", 4);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);

}
void Berserker::heroSkill()
{
	_skill = createPlistAnimation("Berserker/Berserker_Skill.plist", "_Berserker_Skill", 6);
	auto animate = Animate::create(_skill);
	if (_msg == ME)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // 隐藏精灵
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Berserker::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("Berserker/Berserker_Dead.plist", "_Berserker_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_msg == ME)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Berserker::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Berserker/Berserker_Run.plist", "_Berserker_Run", 7);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));

	_postion = end_pos;//更新英雄坐标

	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}

/****************************************************
 * 功能：BlueSlime类成员函数
 * _hp=100
 * _ap=3
 * _mp=0
 * _lv=1
 *_skill_ap=_ap
 * _max_mp=6
 * 作者：牟泳祯
 ****************************************************/
void BlueSlime::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("BlueSlime/BlueSlime_Attack.plist", "_BlueSlime_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// 播放攻击帧动画
	_sprite->runAction(sequence);
}

void BlueSlime::heroDead()
{
	//通过plist文件创建帧动画
	_dead = createPlistAnimation("BlueSlime/BlueSlime_Dead.plist", "_BlueSlime_Dead", 3);
	auto animate = Animate::create(_dead);
	
	_sprite->runAction(animate);
}

void BlueSlime::heroRunToEnemyPos(Vec2& end_pos)
{
	this->createHealthBar();
	this->createMagicBar();
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("BlueSlime/BlueSlime_Run.plist", "_BlueSlime_Run", 7);
	if (end_pos.x < _postion.x)
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
	MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));
	_postion = end_pos;//更新英雄坐标
	_healthBar->runAction(healthBarMoveTo);
	_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // 停止跑步动画
		_sprite->setVisible(false); // 隐藏精灵
		heroAction(); // 由monsterAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}

