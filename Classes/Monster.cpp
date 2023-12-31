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
	else if (_mp >= _max_mp)
	{
		_sprite->setVisible(false); // ���ؾ���
		//this->MonsterSkill();
		this->getHurted();
		_mp = 0; // ���� mp
	}
	else
	{
		_sprite->setVisible(false); // ���ؾ���
		this->monsterAttack();
		this->getHurted();
		_mp++;
	}
}
/****************************************************
 * ���ܣ�BlackWerewolf���Ա����
 * _hp=320
 * _ap=13
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ���˼��
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
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("BlackWerewolf/BlackWerewolf_Attack.plist", "_BlackWerewolf_Attack", 4);
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
void BlackWerewolf::monsterDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("BlackWerewolf/BlackWerewolf_Dead.plist", "_BlackWerewolf_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlackWerewolf::monsterRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("BlackWerewolf/BlackWerewolf_Run.plist", "_BlackWerewolf_Run", 8);
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
		monsterAction(); // ��monsterAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�SkeletonWarrior���Ա����
 * _hp=350
 * _ap=8
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=5
 * ���ߣ���˼��
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
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Attack.plist", "_SkeletonWarrior_Attack", 4);
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

void SkeletonWarrior::monsterDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Dead.plist", "_SkeletonWarrior_Dead", 6);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void SkeletonWarrior::monsterRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("SkeletonWarrior/SkeletonWarrior_Run.plist", "_SkeletonWarrior_Run", 7);
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
		monsterAction(); // ��monsterAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�BlueSlime���Ա����
 * _hp=290
 * _ap=15
 * _mp=0
 * _lv=1
 *_skill_ap=1.5*_ap
 * _max_mp=4
 * ���ߣ���˼��
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
	// ��������֡�������󶨻ص�����
	_attack = createPlistAnimation("BlueSlime/BlueSlime_Attack.plist", "_BlueSlime_Attack", 6);
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
	_dead = createPlistAnimation("BlueSlime/BlueSlime_Dead.plist", "_BlueSlime_Dead", 5);
	auto animate = Animate::create(_dead);
	if (_reverse)
		_sprite->setFlippedX(true);
	_sprite->runAction(animate);
}

void BlueSlime::monsterRunToEnemyPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("BlueSlime/BlueSlime_Run.plist", "_BlueSlime_Run", 8);
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
		monsterAction(); // ��monsterAction��������ѡ�񲥷�
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
