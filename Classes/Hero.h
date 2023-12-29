#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	void heroAction();
	void upLevel(int lv) { _lv+=lv; _hp *= _lv; _ap *= _lv; };//��lv��
	void getHurted() { _hp -= _enemy_ap; };
	void setEnemyAp(int ap) { _enemy_ap = ap; };//��ȡ���˹�����
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	virtual bool init(Vec2&start_pos= Vec2(Director::getInstance()->getVisibleSize() / 2));
	//ʵ��Ӣ�۹�������
	virtual void heroAttack() = 0;
	//ʵ��Ӣ����������
	virtual void heroDead() = 0;
	//�ƶ���ĳһ�㲢����
	virtual void heroSkill() = 0;
	
protected:
	int _hp;
	int _mp;
	int _ap;
	int _lv;
	int _max_mp;

	int _enemy_ap;

	bool _reverse = false;//�ƶ�ʱ�Ƿ�ת
	Vec2 _postion;//��ǰλ��
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Animation* _skill;
};

class Samurai :public Hero
{
public:
	CREATE_FUNC(Samurai);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};
class Berserker :public Hero
{
public:
	CREATE_FUNC(Berserker);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};

class Kunoichi :public Hero
{
public:
	CREATE_FUNC(Kunoichi);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();

};

class LightningMage :public Hero
{
public:
	CREATE_FUNC(LightningMage);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class FireVizard :public Hero
{
public:
	CREATE_FUNC(FireVizard);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};

class WandererMagican :public Hero
{
public:
	CREATE_FUNC(WandererMagican);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};
class NinjaMonk:public Hero
{
public:
	CREATE_FUNC(NinjaMonk);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};
class NinjaPeasant :public Hero
{
public:
	CREATE_FUNC(NinjaPeasant);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};
class SamuraiCommander :public Hero
{
public:
	CREATE_FUNC(SamuraiCommander);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};