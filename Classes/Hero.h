#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	virtual bool init();
	//ʵ��Ӣ���ܲ���Vec2(x,y)����
	virtual void heroRun( float x, float y)=0;
	//ʵ��Ӣ�۹�������
	virtual void heroAttack() = 0;
	//ʵ��Ӣ����������
	virtual void heroDead() = 0;
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
	bool init();
	Animation* createPlistAnimation(std::string filename,int photonums);
	void heroRun(float x, float y);
	void heroAttack();
	void heroDead();
private:
	Sprite* sprite;
	Animation* run;
	Animation* attack;
	Animation* dead;
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	bool init();
	Animation* createPlistAnimation(std::string filename, int photonums);
	void heroRun(float x, float y);
	void heroAttack();
	void heroDead();
private:
	Sprite* sprite;
	Animation* run;
	Animation* attack;
	Animation* dead;

};