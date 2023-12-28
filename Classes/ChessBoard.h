#pragma once

/**************
* 功能:棋盘类的实现
* 作者:尹泽河
* 时间:2023年12月28日
**************/

#include"cocos2d.h"
USING_NS_CC;
#include"Hero.h"

#include"GameController.h"

#include<Vector>

#define BDSZ_X 20	//整个棋盘的长
#define BDSZ_Y 6	//整个棋盘的宽

/* 表示坐标的结构体 */
struct Command
{
	int _x;		//点阵横坐标
	int _y;		//点阵纵坐标
};

class ChessBoard : public Ref
{
private:
	// 记录我方棋子集合（Sprite*可以换成Hero*）
	std::list<Hero*> _myHeroes;

	// 记录敌方棋子集合（Sprite*可以换成Hero*）
	std::list<Hero*> _enemyHeroes;

	// 记录我方棋子编号
	std::map<Hero*, int> _myHeroesIdx;

	//虚拟棋盘
	std::vector<std::vector<Hero*>> _BOARD;
public:
	CREATE_FUNC(ChessBoard);

	virtual bool init();			//初始化函数

	// 获取我方棋子集合（get）
	std::list<Hero*>* getMyHeroes() { return &_myHeroes; };

	// 获取敌方棋子集合（get）
	std::list<Hero*>* getEnemyHeroes() { return &_enemyHeroes; };

	// 获取我方棋子编号map（get）
	std::map<Hero*, int>* getMyHeroesIdxMap() { return &_myHeroesIdx; };

	//获得虚拟棋盘(get)
	std::vector<std::vector<Hero*>>* getBoard() { return &_BOARD; };

	// 查询我方场上是否存在指定英雄，若存在则返回编号，否则返回-1
	int findHero(Hero* hero);
};