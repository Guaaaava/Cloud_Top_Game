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
	_sprite->setPosition(_postion);//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
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
		_sprite->setVisible(false); // ���ؾ���
		this->monsterDead();
	}
	//else if (_mp >= _max_mp)
	//{
	//	_sprite->setVisible(false); // ���ؾ���
	//	//this->MonsterSkill();
	//	this->getHurted();
	//	_mp = 0; // ���� mp
	//}
	else
	{
		_sprite->setVisible(false); // ���ؾ���
		this->monsterAttack();
		this->getHurted();
		_mp++;
	}
}
void Monster::createHealthBar()
{
	// ����ͷ��Ѫ��
	_healthBar = ProgressTimer::create(Sprite::create("StatusBar/HealthBar.png"));
	_healthBar->setLocalZOrder(10000);
	// ����͸����
	//_healthBar->setOpacity(255);

	_healthBar->setType(ProgressTimerType::BAR);
	_healthBar->setMidpoint(Vec2(0, 0.5));
	_healthBar->setBarChangeRate(Vec2(1, 0));
	_healthBar->setPercentage(100.0f);  // ��ʼΪ��Ѫ
	_healthBar->setAnchorPoint(Vec2(0, 0.5)); // ����ê����Ѫ��������м�
	// ��ȡӢ�۵�ê��
	Vec2 anchorPoint = _postion;
	// ����Ѫ����λ�ã���ê���Ϸ���
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
	// ����Ѫ��λ��

	if (_healthBar)
	{
		_healthBar->setPosition(Vec2(0, _sprite->getContentSize().height));
		_healthBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
	}

	// ����ͷ��Ѫ��λ��
	//_healthBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
}
void Monster::updateHealthBar(float dt) {
	// ģ��Ӣ�۵�Ѫ���仯��ʵ����Ӧ������Ϸ�߼�����
	_hp -= 1;

	// ����Ѫ����ʾ
	float healthPercentage;
	if (_hp <= 0)
		healthPercentage = 0;
	else
		healthPercentage = static_cast<float>(_hp) / _max_hp * 100.0f;
	_healthBar->setScaleX(healthPercentage / 100.0f);

	// ���Ѫ��С�ڵ���0������������ִ����Ӧ���߼�������Ӣ������
	if (_hp <= 0) {
		unschedule(CC_SCHEDULE_SELECTOR(Monster::updateHealthBar));
		// ������ִ����Ӧ���߼���������Ϸ������
	}
}

void Monster::createMagicBar()
{
	// ����ͷ������
	_magicBar = ProgressTimer::create(Sprite::create("StatusBar/MagicBar.png"));
	_magicBar->setLocalZOrder(10000);
	// ����͸����
	//_magicBar->setOpacity(255);

	_magicBar->setType(ProgressTimerType::BAR);
	_magicBar->setMidpoint(Vec2(0, 0.5));
	_magicBar->setBarChangeRate(Vec2(1, 0));
	_magicBar->setPercentage(100.0f);  // ��ʼΪ��Ѫ
	_magicBar->setAnchorPoint(Vec2(0, 0.5)); // ����ê��������������м�
	// ��ȡӢ�۵�ê��
	Vec2 anchorPoint = _postion;
	// ����������λ�ã���ê���Ϸ���
	Vec2 healthBarPosition = Vec2(anchorPoint.x - 60, anchorPoint.y + 90);
	_magicBar->setPosition(healthBarPosition);
	_magicBar->setScaleY(0.5f);
	//_magicBar->setPosition(Vec2(100, 100));
	this->addChild(_magicBar);
}

void Monster::updateMagicBarPosition()
{
	// ��������λ��

	if (_magicBar)
	{
		_magicBar->setPosition(Vec2(0, _sprite->getContentSize().height));
		_magicBar->setPosition(Vec2(getContentSize().width / 2, getContentSize().height + 10));
	}
}

void Monster::updateMagicBar(float dt) {
	// ģ��Ӣ�۵������仯��ʵ����Ӧ������Ϸ�߼�����

	// ����������ʾ
	float magicPercentage;
	if (_mp <= 0)
		magicPercentage = 0;
	else
		magicPercentage = static_cast<float>(_mp) / _max_mp * 100.0f;
	_magicBar->setScaleX(magicPercentage / 100.0f);
}


/****************************************************
 * ���ܣ�BlueSlime���Ա����
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ�ĲӾ��
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
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("BlueSlime/BlueSlime_Attack.plist", "_BlueSlime_Attack", 4);
	if (_reverse)
		_sprite->setFlippedX(true);
	auto animate = Animate::create(_attack);
	auto callback = CallFunc::create([this]() {

		this->monsterAction();
		});
	auto sequence = Sequence::create(animate, callback, NULL);

	// ���Ź���֡����
	_sprite->runAction(sequence);

}

void BlueSlime::monsterDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("BlueSlime/BlueSlime_Dead.plist", "_BlueSlime_Dead", 3);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlueSlime::monsterRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("BlueSlime/BlueSlime_Run.plist", "_BlueSlime_Run", 7);
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
	MoveTo* healthBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 100));
	//MoveTo* magicBarMoveTo = MoveTo::create(3, Vec2(end_pos.x - 40, end_pos.y + 90));
	_postion = end_pos;//����Ӣ������
	_healthBar->runAction(healthBarMoveTo);//
	//_magicBar->runAction(magicBarMoveTo);
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		monsterAction(); // ��monsterAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
