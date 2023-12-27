#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	virtual bool init(Vec2&start_pos= Vec2(Director::getInstance()->getVisibleSize() / 2));
	//实现英雄跑步到Vec2(x,y)动画
	/*virtual void heroRun(Vec2& end_pos)=0;*/
	//实现英雄攻击动画
	virtual void heroAttack() = 0;
	//实现英雄死亡动画
	virtual void heroDead() = 0;
	//移动到某一点并攻击
	virtual void heroSkill()=0;
	virtual void heroAction()=0;
protected:
	int _hp;
	int _mp;
	int _ap;
	int _lv;
	int _max_mp;
	Vec2 _vec;
};

class Samurai :public Hero
{
public:
	CREATE_FUNC(Samurai);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	//void heroRun(Vec2& end_pos);
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Animation* _skill;
	bool _reverse = false;
	Vec2 _postion;
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename,std::string framename, int photonums);
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
	Animation* _skill;
	bool _reverse = false;
};

class Kunoichi :public Hero
{
public:
	CREATE_FUNC(Kunoichi);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
	Animation* _skill;
	bool _reverse = false;
};

class LightningMage :public Hero
{
public:
	CREATE_FUNC(LightningMage);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
	Animation* _skill;
	bool _reverse = false;
};

class FireVizard :public Hero
{
public:
	CREATE_FUNC(FireVizard);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
	Animation* _skill;
	bool _reverse = false;
};

class WandererMagican :public Hero
{
public:
	CREATE_FUNC(WandererMagican);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();
	void heroAction();
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
	Animation* _skill;
	bool _reverse = false;
};