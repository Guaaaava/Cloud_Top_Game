#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

#include"Hero.h"

#include "GameController.h"

const float SHOP_HEIGHT = 210.0f;		// 商店卡牌高度
const float CHESSBOARD_WIDTH = 1150.0f;	// 棋盘图片宽度
const float CHESSBOARD_HEIGHT = 950.0f;	// 棋盘图片高度

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

	virtual bool init();		// 初始化场景

	static LayerColor* getLayer() { return layer; };	// 获取背景层（静态成员）
	
private:

	static LayerColor* layer;	// 记录背景层（静态成员）

	Hero* touchingSprite;		// 被选中的英雄
	Vec2 firstPos;				//被选中的英雄的初始位置

	virtual bool onTouchBegan(Touch* touch, Event* event);	// 按下鼠标的回调
	virtual void onTouchMoved(Touch* touch, Event* event);	// 移动鼠标的回调
	virtual void onTouchEnded(Touch* touch, Event* event);	// 释放鼠标的回调

	Hero* judgePointInSprite(Point pnt);	// 判断触摸点是否在已有英雄区域内，是则返回该精灵，否则返回nullptr
};