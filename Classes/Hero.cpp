#include"Hero.h"

bool Hero::init(Vec2& start_pos )
{
	if (!Sprite::init())return false;
	return true;
}

Animation* Hero::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
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
		_sprite->setVisible(false); // ���ؾ���
		this->heroDead();
	}
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // ���ؾ���
		this->heroSkill();
		this->getHurted();
		_mp = 0; // ���� mp
	}
	else
	{
		_sprite->setVisible(false); // ���ؾ���
		this->heroAttack();
		this->getHurted();
		_mp++;
	}
}
/****************************************************
 * ���ܣ�Samurai���Ա����
 * _hp=320
 * _ap=13
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ���˼��
 ****************************************************/
bool Samurai::init(Vec2& start_pos)
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


void Samurai::heroAttack()
{
		// ��������֡�������󶨻ص�����
		_attack = createPlistAnimation("Samurai/Samurai_Attack.plist", "_Samurai_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {
		
		this->heroAction(); 
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);
}
void Samurai::heroSkill()
{
	   _skill= createPlistAnimation("Samurai/Samurai_Skill.plist", "_Samurai_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack(); 
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);
	
}
void Samurai::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead=createPlistAnimation("Samurai/Samurai_Dead.plist", "_Samurai_Dead", 6);
	auto animate = Animate::create(_dead);
	if(_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Samurai::heroRunToEnemyPos(Vec2& end_pos)
{
    // ͨ��plist�ļ�����֡����
    _run = createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
    auto runAnimate = Animate::create(_run);
    auto runAction = RepeatForever::create(runAnimate);
    _sprite->runAction(runAction); // �����ܲ�����

    // �����ƶ�����
    MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
    auto moveCallback = CallFunc::create([this]() {
        _sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
        heroAction(); // ��heroAction��������ѡ�񲥷�
    });
    auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
    _sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�Knight���Ա����
 * _hp=350
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=5
 * ���ߣ���˼��
 ****************************************************/
bool Knight::init(Vec2& start_pos)
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

void Knight::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("Knight/Knight_Attack.plist", "_Knight_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void Knight::heroSkill()
{
	_skill = createPlistAnimation("Knight/Knight_Skill.plist", "_Knight_Skill", 6);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Knight::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("Knight/Knight_Dead.plist", "_Knight_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Knight::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�Kunoichi���Ա����
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ���˼��
 ****************************************************/
bool Kunoichi::init(Vec2& start_pos)
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


void Kunoichi::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("Kunoichi/Kunoichi_Attack.plist", "_Kunoichi_Attack", 6);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void Kunoichi::heroSkill()
{
	_skill = createPlistAnimation("Kunoichi/Kunoichi_Skill.plist", "_Kunoichi_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Kunoichi::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("Kunoichi/Kunoichi_Dead.plist", "_Kunoichi_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Kunoichi::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("Kunoichi/Kunoichi_Run.plist", "_Kunoichi_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�LightningMage���Ա����
 * _hp=280
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.7*_ap
 * _max_mp=5
 * ���ߣ���˼��
 ****************************************************/
bool LightningMage::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 280;
	_ap = 15;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_skill_ap = 1.7 * _ap;
	return true;
}



void LightningMage::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("LightningMage/LightningMage_Attack.plist", "_LightningMage_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void LightningMage::heroSkill()
{
	_skill = createPlistAnimation("LightningMage/LightningMage_Skill.plist", "_LightningMage_Skill", 9);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void LightningMage::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("LightningMage/LightningMage_Dead.plist", "_LightningMage_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void LightningMage::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("LightningMage/LightningMage_Run.plist", "_LightningMage_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�FireVizard���Ա����
 * _hp=300
 * _ap=16
 * _mp=0
 * _lv=1
 *_skill_ap=2.5*_ap
 * _max_mp=6
 * ���ߣ���˼��
 ****************************************************/
bool FireVizard::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 300;
	_ap = 16;
	_mp = 0;
	_lv = 1;
	_max_mp = 6;
	_skill_ap = 2.5 * _ap;
	return true;
}



void FireVizard::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("FireVizard/FireVizard_Attack.plist", "_FireVizard_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void FireVizard::heroSkill()
{
	_skill = createPlistAnimation("FireVizard/FireVizard_Skill.plist", "_FireVizard_Skill", 8);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void FireVizard::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("FireVizard/FireVizard_Dead.plist", "_FireVizard_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void FireVizard::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("FireVizard/FireVizard_Run.plist", "_FireVizard_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�WandererMagican���Ա����
 * _hp=280
 * _ap=17
 * _mp=0
 * _lv=1
 *_skill_ap=2*_ap
 * _max_mp=5
 * ���ߣ���˼��
 ****************************************************/
bool WandererMagican::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 280;
	_ap = 17;
	_mp = 0;
	_lv = 1;
	_max_mp = 5;
	_skill_ap = 2* _ap;
	return true;
}

void WandererMagican::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("WandererMagican/WandererMagican_Attack.plist", "_WandererMagican_Attack", 6);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void WandererMagican::heroSkill()
{
	_skill = createPlistAnimation("WandererMagican/WandererMagican_Skill.plist", "_WandererMagican_Skill", 7);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void WandererMagican::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("WandererMagican/WandererMagican_Dead.plist", "_WandererMagican_Dead", 4);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void WandererMagican::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("WandererMagican/WandererMagican_Run.plist", "_WandererMagican_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�NinjaMonk���Ա����
 * _hp=300
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.1*_ap
 * _max_mp=2
 * ���ߣ���˼��
 ****************************************************/
bool NinjaMonk::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 300;
	_ap = 8;
	_mp = 0;
	_lv = 1;
	_max_mp = 2;
	_skill_ap = 1.1 * _ap;
	return true;
}

void NinjaMonk::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("NinjaMonk/NinjaMonk_Attack.plist", "_NinjaMonk_Attack", 5);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void NinjaMonk::heroSkill()
{
	_skill = createPlistAnimation("NinjaMonk/NinjaMonk_Skill.plist", "_NinjaMonk_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void NinjaMonk::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("NinjaMonk/NinjaMonk_Dead.plist", "_NinjaMonk_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void NinjaMonk::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("NinjaMonk/NinjaMonk_Run.plist", "_NinjaMonk_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�NinjaPeasant���Ա����
 * _hp=300
 * _ap=9
 * _mp=0
 * _lv=1
 *_skill_ap=1.2*_ap
 * _max_mp=3
 * ���ߣ���˼��
 ****************************************************/
bool NinjaPeasant::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 300;
	_ap = 9;
	_mp = 0;
	_lv = 1;
	_max_mp = 3;
	_skill_ap = 1.2 * _ap;
	return true;
}

void NinjaPeasant::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("NinjaPeasant/NinjaPeasant_Attack.plist", "_NinjaPeasant_Attack", 6);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void NinjaPeasant::heroSkill()
{
	_skill = createPlistAnimation("NinjaPeasant/NinjaPeasant_Skill.plist", "_NinjaPeasant_Skill", 4);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void NinjaPeasant::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("NinjaPeasant/NinjaPeasant_Dead.plist", "_NinjaPeasant_Dead", 4);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void NinjaPeasant::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("NinjaPeasant/NinjaPeasant_Run.plist", "_NinjaPeasant_Run", 6);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�SamuraiCommander���Ա����
 * _hp=320
 * _ap=10
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ���˼��
 ****************************************************/
bool SamuraiCommander::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 320;
	_ap = 10;
	_mp = 0;
	_lv = 1;
	_max_mp = 4;
	_skill_ap = 1.5 * _ap;
	return true;
}

void SamuraiCommander::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("SamuraiCommander/SamuraiCommander_Attack.plist", "_SamuraiCommander_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void SamuraiCommander::heroSkill()
{
	_skill = createPlistAnimation("SamuraiCommander/SamuraiCommander_Skill.plist", "_SamuraiCommander_Skill", 5);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void SamuraiCommander::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("SamuraiCommander/SamuraiCommander_Dead.plist", "_SamuraiCommander", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void SamuraiCommander::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("SamuraiCommander/SamuraiCommander_Run.plist", "_SamuraiCommander_Run", 8);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�Berserker���Ա����
 * _hp=200
 * _ap=20
 * _mp=0
 * _lv=1
 *_skill_ap=2*_ap
 * _max_mp=3
 * ���ߣ���˼��
 ****************************************************/
bool Berserker::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	_hp = 200;
	_ap = 20;
	_mp = 0;
	_lv = 1;
	_max_mp = 3;
	_skill_ap = 2 * _ap;
	return true;
}

void Berserker::heroAttack()
{
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("Berserker/Berserker_Attack.plist", "_Berserker_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->heroAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}
void Berserker::heroSkill()
{
	_skill = createPlistAnimation("Berserker/Berserker_Skill.plist", "_Berserker_Skill", 6);
	auto animate = Animate::create(_skill);
	if (_reverse)
		_sprite->setFlippedX(true);

	auto callback = CallFunc::create([this]() {
		_sprite->setVisible(false); // ���ؾ���
		_sprite->stopAllActions();
		this->heroAttack();
		});

	auto sequence = Sequence::create(animate, callback, nullptr);
	_sprite->runAction(sequence);

}
void Berserker::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("Berserker/Berserker_Dead.plist", "_Berserker_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void Berserker::heroRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("Berserker/Berserker_Run.plist", "_Berserker_Run", 7);
	if (end_pos.x < _postion.x + Director::getInstance()->getVisibleSize().width / 2)
	{
		// ��ת����
		_reverse = true;
		_sprite->setFlippedX(true);
	}
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAction(); // ��heroAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}