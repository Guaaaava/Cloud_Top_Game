#include "ChessBoard.h"

/****************************************************
 * 功能：初始化棋盘，初始化成功返回true，反之返回false
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
bool ChessBoard::init()
{
	// 初始化成员
	_BOARD.resize(BDSZ_Y);
	for (int i = 0; i < BDSZ_Y; i++) {
		_BOARD[i].resize(BDSZ_X);
	}

	_STAND.resize(BDSZ_X);

	return true;
}

/****************************************************
 * 功能：查询我方场上是否存在指定英雄，若存在则返回编号，否则返回-1
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
int ChessBoard::findHero(Hero* hero)
{
	std::list<Hero*>::iterator it;
	for (it = _myHeroes.begin(); it != _myHeroes.end(); it++)
	{
		if ((*it) == hero)
		{
			return _myHeroesIdx[hero];
		}
	}

	return -1;
}