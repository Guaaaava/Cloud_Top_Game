#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class HeroAction :public Scene
{
public:
	CREATE_FUNC(HeroAction);

	virtual bool init();
	

private:
	//Ӣ�۳���
	void showHero();
	//Ӣ���ܲ���ԭ�أ�
	void heroRun();
	//Ӣ���ܶ���������
	void heroOnMouseMove();
	
};