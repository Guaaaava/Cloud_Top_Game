#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <list>
#include <map>

/****************************************************
 * 功能：棋盘数据类型
 * 说明：Ref派生类，自动释放内存
 * 作者：黄辰宇
 * 时间：2023年12月26日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class ChessBoard : public Ref
{
public:
	CREATE_FUNC(ChessBoard);
	
	virtual bool init();

	// 获取我方棋子集合（get）
	std::list<Sprite*>* getMyHeroes() { return &myHeroes; };

	// 获取敌方棋子集合（get）
	std::list<Sprite*>* getEnemyHeroes() { return &enemyHeroes; };
	
	// 获取我方棋子编号map（get）
	std::map<Sprite*, int>* getMyHeroesIdxMap() { return &myHeroesIdx; };

	// 查询我方场上是否存在指定英雄，若存在则返回编号，否则返回-1
	int findHero(Sprite* hero);

private:
	// 记录我方棋子集合（Sprite*可以换成Hero*）
	std::list<Sprite*> myHeroes;

	// 记录敌方棋子集合（Sprite*可以换成Hero*）
	std::list<Sprite*> enemyHeroes;

	// 记录我方棋子编号
	std::map<Sprite*, int> myHeroesIdx;
};