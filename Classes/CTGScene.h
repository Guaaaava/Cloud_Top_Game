#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;



#include"HeroAction.h"

#define WORDS_GAME_NAME 1001	// “金铲铲之战”编码
#define WORDS_START     1002	// “开始”编码
#define WORDS_SHOP      1003	// “商店”编码
#define WORDS_EXIT      1004	// “退出”编码

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

	// 创建一个通用按钮
	static MenuItemImage* createGameButton(std::string name, const ccMenuCallback& callback);

private:
	// 记录背景层
	Node* prt_backGround;

	// 记录商店按钮大小位置
	Rect prt_shopButtonSize;

	// 游戏开始按钮的点击事件
	void menuStartCallback(Ref* sender);

	// 打开商店按钮的点击事件
	void menuOpenShopCallback(Ref* sender);

	// 退出游戏按钮的点击事件
	void menuExitGameCallback(Ref* sender);

	// 按下按钮的回调
	virtual bool onTouchBegan(Touch* touch, Event* event);

	// 释放按钮的回调
	virtual void onTouchEnded(Touch* touch, Event* event);

	// 创建一个商店结点
	void createShopNode();


};