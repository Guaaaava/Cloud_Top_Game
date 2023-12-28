#include"Hero.h"

bool Hero::init(Vec2& start_pos )
{
	if (!Sprite::init())return false;
	return true;
}


/****************************************************
 * 功能：Samurai类成员函数
 * _hp=100
 * _ap=10
 * _mp=0
 * _lv=1
 * _vec=Vec2(5,5)
 * _max_mp=5
 * 作者：卞思涵
 ****************************************************/
bool Samurai::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);
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
	return Animation::createWithSpriteFrames(images, 1.f / 8);//改为一秒钟播放一次完整的帧动画
}
void Samurai::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void Samurai::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void Samurai::heroAttack()
{
		// 创建攻击帧动画并绑定回调函数
		_attack = createPlistAnimation("Samurai/Samurai_Attack.plist", "_Samurai_Attack", 4);
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
void Samurai::heroSkill()
{
	   _skill= createPlistAnimation("Samurai/Samurai_Skill.plist", "_Samurai_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if(_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Samurai::heroRunToEnemyPos(Vec2& end_pos)
{
    // 通过plist文件创建帧动画
    _run = createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run", 8);
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
        heroAction(); // 由heroAction动画进行选择播放
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
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);
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
	return Animation::createWithSpriteFrames(images, 1.f / photonums);
}


void Knight::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void Knight::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void Knight::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("Knight/Knight_Attack.plist", "_Knight_Attack", 4);
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
void Knight::heroSkill()
{
	_skill = createPlistAnimation("Knight/Knight_Skill.plist", "_Knight_Skill", 6);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Knight::heroRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
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
		heroAction(); // 由heroAction动画进行选择播放
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
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);

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
	return Animation::createWithSpriteFrames(images, 1.f / photonums);
}


void Kunoichi::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void Kunoichi::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void Kunoichi::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("Kunoichi/Kunoichi_Attack.plist", "_Kunoichi_Attack", 6);
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
void Kunoichi::heroSkill()
{
	_skill = createPlistAnimation("Kunoichi/Kunoichi_Skill.plist", "_Kunoichi_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Kunoichi::heroRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("Kunoichi/Kunoichi_Run.plist", "_Kunoichi_Run", 8);
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
		heroAction(); // 由heroAction动画进行选择播放
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
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);

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
	return Animation::createWithSpriteFrames(images, 1.f / photonums);
}

void LightningMage::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void LightningMage::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void LightningMage::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("LightningMage/LightningMage_Attack.plist", "_LightningMage_Attack", 4);
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
void LightningMage::heroSkill()
{
	_skill = createPlistAnimation("LightningMage/LightningMage_Skill.plist", "_LightningMage_Skill", 9);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void LightningMage::heroRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("LightningMage/LightningMage_Run.plist", "_LightningMage_Run", 8);
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
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：FireVizard类成员函数
 * 作者：卞思涵
 ****************************************************/
bool FireVizard::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);

	return true;
}
Animation* FireVizard::createPlistAnimation(std::string filename, std::string framename, int photonums)
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
	return Animation::createWithSpriteFrames(images, 1.f / photonums);
}

void FireVizard::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void FireVizard::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void FireVizard::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("FireVizard/FireVizard_Attack.plist", "_FireVizard_Attack", 4);
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
void FireVizard::heroSkill()
{
	_skill = createPlistAnimation("FireVizard/FireVizard_Skill.plist", "_FireVizard_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void FireVizard::heroRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("FireVizard/FireVizard_Run.plist", "_FireVizard_Run", 8);
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
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * 功能：WandererMagican类成员函数
 * 作者：卞思涵
 ****************************************************/
bool WandererMagican::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 100;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_vec = Vec2(5, 5);

	return true;
}
Animation* WandererMagican::createPlistAnimation(std::string filename, std::string framename, int photonums)
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
	return Animation::createWithSpriteFrames(images, 1.f / photonums);
}

void WandererMagican::getHurted(int enemy_ap)
{
	_hp -= enemy_ap;
}
void WandererMagican::heroAction()
{
	if (_hp <= 0)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroSkill();
		_mp = 0; // 重置 mp
	}
	else
	{
		_sprite->setVisible(false); // 隐藏精灵
		this->heroAttack();
		_mp++;
	}
}

void WandererMagican::heroAttack()
{
	// 创建攻击帧动画并绑定回调函数
	_attack = createPlistAnimation("WandererMagican/WandererMagican_Attack.plist", "_WandererMagican_Attack", 6);
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
void WandererMagican::heroSkill()
{
	_skill = createPlistAnimation("WandererMagican/WandererMagican_Skill.plist", "_WandererMagican_Skill", 7);
	auto animate = Animate::create(_skill);
	if (_reverse)
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
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void WandererMagican::heroRunToEnemyPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("WandererMagican/WandererMagican_Run.plist", "_WandererMagican_Run", 8);
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
		heroAction(); // 由heroAction动画进行选择播放
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}