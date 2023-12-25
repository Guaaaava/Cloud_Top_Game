#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	virtual bool init(Vec2&start_pos= Vec2(Director::getInstance()->getVisibleSize() / 2));
	//ʵ��Ӣ���ܲ���Vec2(x,y)����
	/*virtual void heroRun(Vec2& end_pos)=0;*/
	//ʵ��Ӣ�۹�������
	virtual void heroAttack() = 0;
	//ʵ��Ӣ����������
	virtual void heroDead() = 0;
	//�ƶ���ĳһ�㲢����
	virtual void heroRunAndAttack(Vec2 &end_pos)=0;
protected:
	int _hp;
	int _mp;
	int _ap;
	int _dp;
	int _lv;
	int _dis;
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
	void heroRunAndAttack(Vec2& end_pos);
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
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
	void heroRunAndAttack(Vec2& end_pos);
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
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
	void heroRunAndAttack(Vec2& end_pos);
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
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
	void heroRunAndAttack(Vec2& end_pos);
private:
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Vec2 _postion;
};