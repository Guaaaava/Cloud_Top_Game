#include "ChessBoard.h"

/****************************************************
 * ���ܣ���ʼ�����̣���ʼ���ɹ�����true����֮����false
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool ChessBoard::init()
{
	// ��ʼ����Ա
	_BOARD.resize(BDSZ_Y);
	for (int i = 0; i < BDSZ_Y; i++) {
		_BOARD[i].resize(BDSZ_X);
	}

	_STAND.resize(BDSZ_X);

	return true;
}

/****************************************************
 * ���ܣ���ѯ�ҷ������Ƿ����ָ��Ӣ�ۣ��������򷵻ر�ţ����򷵻�-1
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
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