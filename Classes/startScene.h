#pragma once

/**************
* 功能:金铲铲之战开始场景
* 作者:尹泽河
* 时间:2023年12月21日
**************/

#ifndef _START_SCENE_H
#define _START_SCENE_H

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include"CTGScene.h"

class STARTScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();//初始化函数

	CREATE_FUNC(STARTScene);

	static MenuItemImage* creatMenuItem(std::string name, const ccMenuCallback& callback);//创建通用菜单项

private:
	void menuStartCallback(cocos2d::Ref* pSender);

	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif //_START_SCENE_H