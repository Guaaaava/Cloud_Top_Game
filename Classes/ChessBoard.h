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
#include <map>

#define BDSZ_X 9	//整个棋盘的长
#define BDSZ_Y 6	//整个棋盘的宽

//区域类型
#define STAND 0//站立区域
#define OTHER 1//其他区域

/* 表示坐标的结构体 */
struct POS
{
	int _type = OTHER;
	int _x = -1;		//点阵横坐标
	int _y = -1;		//点阵纵坐标

	void operator=(const POS& x) {
		this->_type = x._type;
		this->_x = x._x;
		this->_y = x._y;
	}
};

class ChessBoard : public Ref
{
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

private:
	// 记录我方棋子集合（Sprite*可以换成Hero*）
	std::list<Hero*> _myHeroes;

	// 记录敌方棋子集合（Sprite*可以换成Hero*）
	std::list<Hero*> _enemyHeroes;

	// 记录我方棋子编号
	std::map<Hero*, int> _myHeroesIdx;

	//虚拟棋盘
	std::vector<std::vector<Hero*>> _BOARD;

	//虚拟备战席
	std::vector<Hero*>_STAND;
};