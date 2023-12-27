#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

#include "Shop.h"
#include "ChessBoard.h"

			/* ��Ϸ��� */
// �̵�
const int MONEY_ADD_EXP = 4;	// ��4��Ǯ��һ�ξ���
const int EXP_ADD_ONCE = 4;		// ��һ�μ�4�㾭��
const int REFRESH_ONCE = 2;		// ˢ��һ���̵�2��Ǯ

// �ȼ�
const int MAX_LEVEL = 6;
const int EXP_LEVEL[MAX_LEVEL + 5] = { 0, 6, 6 + 10, 6 + 10 + 14, 6 + 10 + 14 + 18, 6 + 10 + 14 + 18 + 22, 6 + 10 + 14 + 18 + 22 + 26 };

/****************************************************
 * ���ܣ���Ϸ�߼�������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class GameController
{
public:
	static GameController* getInstance();
	static void destroyInstance();
	GameController();
	~GameController();

	// ��ȡ�̵����
	Shop* getShop() { return shop; };

	// ��ȡ���̶���
	ChessBoard* getChessBoard() { return chessBoard; };

	// ʤ���ж�


	// �����̴���Ӣ�۾���
	void createHeroInChessBoard(int idxOfHero);

	// ����Ӣ��
	void sellHero(Sprite* soldSprite);

	// ����ý�ҵȣ��ı��̵��ң�����������ˢ�°�ť������ʹ��������ť��ʾΪ����״̬��ע�ⲻҪ������ʱ��ͻ��


private:
	static GameController* instance;

	// ��¼һ���̵����
	Shop* shop;

	// ��¼һ�����̶���
	ChessBoard* chessBoard;

	int enemyMoney;		// �з����
	int enemyExp;		// �з�����
	int enemyLevel;		// �з��ȼ�
};