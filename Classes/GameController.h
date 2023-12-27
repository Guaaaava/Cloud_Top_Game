#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

#include "Shop.h"
#include "ChessBoard.h"

			/* 游戏相关 */
// 商店
const int MONEY_ADD_EXP = 4;	// 花4块钱买一次经验
const int EXP_ADD_ONCE = 4;		// 买一次加4点经验
const int REFRESH_ONCE = 2;		// 刷新一次商店2块钱

// 等级
const int MAX_LEVEL = 6;
const int EXP_LEVEL[MAX_LEVEL + 5] = { 0, 6, 6 + 10, 6 + 10 + 14, 6 + 10 + 14 + 18, 6 + 10 + 14 + 18 + 22, 6 + 10 + 14 + 18 + 22 + 26 };

/****************************************************
 * 功能：游戏逻辑控制器
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class GameController
{
public:
	static GameController* getInstance();
	static void destroyInstance();
	GameController();
	~GameController();

	// 获取商店对象
	Shop* getShop() { return shop; };

	// 获取棋盘对象
	ChessBoard* getChessBoard() { return chessBoard; };

	// 胜负判定


	// 在棋盘创建英雄精灵
	void createHeroInChessBoard(int idxOfHero);

	// 出售英雄
	void sellHero(Sprite* soldSprite);

	// （获得金币等）改变商店金币，允许升级和刷新按钮，并且使得这俩按钮显示为可用状态（注意不要和满级时冲突）


private:
	static GameController* instance;

	// 记录一个商店对象
	Shop* shop;

	// 记录一个棋盘对象
	ChessBoard* chessBoard;

	int enemyMoney;		// 敌方金币
	int enemyExp;		// 敌方经验
	int enemyLevel;		// 敌方等级
};