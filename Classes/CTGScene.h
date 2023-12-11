#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;


/****************************************************
 * 功能：显示金铲铲之战场景
 * 作者：黄辰宇
 * 时间：2023年12月7日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class CTGScene : public Scene
{
public:
	CREATE_FUNC(CTGScene);		// 创建 create() 函数

	virtual bool init();
};