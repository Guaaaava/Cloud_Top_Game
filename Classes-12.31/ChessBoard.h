#pragma once

/**************
* 功能:棋盘类的实现
* 作者:尹泽河
* 时间:2023年12月28日
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"Hero.h"

#include <list>

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
public:
	CREATE_FUNC(ChessBoard);

	virtual bool init();			//初始化函数

	std::list<HeroMsg>* getMyHeroes() { return &_myHeroes; };			// 获取我方英雄链表
	std::list<HeroMsg>* getEnemyHeroes() { return &_enemyHeroes; };	// 获取敌方英雄链表

	// 获得备战席
	std::vector<HeroMsg>* getRelaxHeroes() { return &_RELAX; };

	// 获得虚拟棋盘
	std::vector< std::vector<HeroMsg> >* getBoard() { return &_BOARD; };

private:
	std::list<HeroMsg> _myHeroes;			// 记录我方英雄
	std::list<HeroMsg> _enemyHeroes;		// 记录敌方英雄

	// 备战席
	std::vector<HeroMsg> _RELAX;

	// 虚拟棋盘
	std::vector< std::vector<HeroMsg> > _BOARD;
};