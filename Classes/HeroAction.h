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
	//英雄出现
	void showHero();
	//英雄跑步（原地）
	void heroRun();
	//英雄跑动（动作）
	void heroOnMouseMove();
	
};