#pragma once

#include "cocos2d.h"
USING_NS_CC;

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
	Vector<Sprite*>* getMyHeroes() { return &myHeroes; };

	// 获取敌方棋子集合（get）
	Vector<Sprite*>* getEnemyHeroes() { return &enemyHeroes; };

private:
	// 记录我方棋子集合（Sprite*可以换成Hero*）
	Vector<Sprite*> myHeroes;

	// 记录敌方棋子集合（Sprite*可以换成Hero*）
	Vector<Sprite*> enemyHeroes;
};