#pragma once

/**************
* 功能:金铲铲之战主场景
* 作者:尹泽河
* 时间:2023年12月23日
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include"SETTINGSScene.h"
#include"CTGScene.h"

class MAINScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();//初始化函数

	CREATE_FUNC(MAINScene);

	static int getGameMode() { return gameMode; };

private:
	static int gameMode;

	void menuTrainingModeCallback(cocos2d::Ref* pSender);//训练模式按钮的回调函数

	void menuOnlineModeCallback(cocos2d::Ref* pSender);//联机模式按钮的回调函数

};
