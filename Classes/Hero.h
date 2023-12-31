#pragma once

/**************
* 功能:英雄类(测试用)
* 作者:尹泽河
* 时间:2023年12月29日
**************/

#include "cocos2d.h"
USING_NS_CC;


class Hero :public cocos2d::Sprite
{
public:
	CREATE_FUNC(Hero);//创建静态create函数

	virtual bool init();//初始化函数
};

class Annie :public Hero
{
public:
	CREATE_FUNC(Annie);//创建静态create函数

	virtual bool init();//初始化函数
};