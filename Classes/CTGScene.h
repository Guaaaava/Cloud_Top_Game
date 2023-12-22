#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

<<<<<<< Updated upstream
=======
#include "ui/CocosGUI.h"
using namespace ui;

#define WORDS_GAME_NAME 1001	// “金铲铲之战”编码
#define WORDS_START     1002	// “开始”编码
#define WORDS_SHOP      1003	// “商店”编码
#define WORDS_EXIT      1004	// “退出”编码
#define WORDS_LEVELUP	1005	// “升级”编码
#define WORDS_REFRESH	1006	// "刷新”编码

const float SHOP_HEIGHT = 210.0f;
const float CHESSBOARD_WIDTH = 1150.0f;
const float CHESSBOARD_HEIGHT = 950.0f;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
	virtual bool init();
=======
	virtual bool init();		// 初始化场景

	LayerColor* layer;			// 记录背景层

private:
	// virtual bool onTouchBegan(Touch* touch, Event* event);	// 按下按钮的回调

	// virtual void onTouchEnded(Touch* touch, Event* event);	// 释放按钮的回调
>>>>>>> Stashed changes
};