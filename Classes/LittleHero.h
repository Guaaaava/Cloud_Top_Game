#pragma once
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class LittleHero :public Sprite
{
public:
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
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