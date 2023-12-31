#pragma once
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class LittleHero :public Sprite
{
public:
	CREATE_FUNC(LittleHero);
	virtual bool init()
	{
		if (!Sprite::init())return false;
		_hp = 10;
		_speed = 250;
		return true;
	}
	void initPos(Vec2 start_pos);
	//Ӣ������ָ���ص�
	void heroRunToPos(Vec2& end_pos);
	//����plist֡����
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	void getHurted() {if(!isDead()) _hp -= 2; };
	bool isDead() {
		if (_hp <= 0)return true;
		else
			return false;
	};

private:
	int _hp;
	Sprite* _sprite;
	Vec2 _postion;
	Animation* _run;
	int _speed;
};