#pragma once

/**************
* 功能:游戏逻辑控制器
* 作者:尹泽河
* 时间:2023年12月28日
**************/

#include "cocos2d.h"
USING_NS_CC;

#include "ChessBoard.h"

#include "Shop.h"

#include "Hero.h"

#include "CTGScene.h"

/* 游戏相关 */

// 商店
const int MONEY_ADD_EXP = 4;	// 花4块钱买一次经验
const int EXP_ADD_ONCE = 4;		// 买一次加4点经验
const int REFRESH_ONCE = 2;		// 刷新一次商店2块钱

// 等级
const int MAX_LEVEL = 6;
const int EXP_LEVEL[MAX_LEVEL + 5] = { 0, 6, 6 + 10, 6 + 10 + 14, 6 + 10 + 14 + 18, 6 + 10 + 14 + 18 + 22, 6 + 10 + 14 + 18 + 22 + 26 };

//游戏胜负判断
#define DRAW 0		//平局
#define M_WIN 1		//我方胜利
#define E_WIN 2		//敌方胜利

class GameController
{
public:
	GameController();						//构造函数
	~GameController();						//析构函数
	static GameController* getInstance();	//获得一个实例
	static void destroyInstance();			//销毁实例

	// 获取棋盘对象
	ChessBoard* getChessBoard() { return _chessBoard; };

	// 获取商店对象
	Shop* getShop() { return _shop; };

	void createStandOrigin();								//创建站立区域

	Vec2 getStandPos(int x,int y);							//获取站立块坐标

	POS getSizePos(Vec2 pos);								//获取点阵坐标

	inline int isInStand(Vec2 pos);						//判断点是否在站立区域

	inline bool isInMyBound(struct POS pos);			//判断点是否在我方棋盘内
	inline bool hasHero(struct POS pos);				//判断该位置是否有棋子
	inline bool placeHero(Hero* hero,struct POS pos);	//放置英雄
	int isEnd();										//判定游戏结束


	// 在棋盘创建英雄精灵
	void createHeroInChessBoard(int idxOfHero);

	// 出售英雄
	void sellHero(Hero* soldSprite);

	// （获得金币等）改变商店金币，允许升级和刷新按钮，并且使得这俩按钮显示为可用状态（注意不要和满级时冲突）

	Sprite* _standOrigin[BDSZ_Y + 2][BDSZ_X];		//站立区域

private:
	static GameController* _instance;				//实例对象
	Shop* _shop;									// 记录一个商店对象
	ChessBoard* _chessBoard;						//虚拟棋盘

	Size _standSize;								//每个站立区域的大小
	Vec2 _standPos[8];								//每个站立区域的位置(左下角)

	int enemyMoney;									// 敌方金币
	int enemyExp;									// 敌方经验
	int enemyLevel;									// 敌方等级
};