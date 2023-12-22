#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

/****************************************************
 * 功能：商店控制器
 * 作者：黄辰宇
 * 时间：2023年12月22日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class ShopController
{
public:
	static ShopController* getInstance();
	static void destroyInstance();
	~ShopController();

	// 创建卡牌按钮（静态成员，可以直接调用）
	static Button* createChessButton(const std::string normalPicPath, const std::string selectedPicPath, const Vec2 position);

	// 获取从左到右五张卡牌中心位置（静态成员，可以直接调用）
	static Vec2 getChessPosition(const int numofChess);

private:
	const float shopStart_x = (Director::getInstance()->getVisibleSize()).width * 0.15f;			// 商店开始横坐标
	const float shopWidth = (Director::getInstance()->getVisibleSize()).width - 2 * shopStart_x;	// 商店长度
	const float chessWidth = shopWidth / 5.0f;														// 卡牌长度

	static ShopController* instance;

};