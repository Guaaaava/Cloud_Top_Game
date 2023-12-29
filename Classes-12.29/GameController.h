#pragma once

/**************
* ����:��Ϸ�߼�������
* ����:�����
* ʱ��:2023��12��28��
**************/

#include "cocos2d.h"
USING_NS_CC;

#include "ChessBoard.h"

#include "Shop.h"

#include "Hero.h"

#include "CTGScene.h"

/* ��Ϸ��� */

// �̵�
const int MONEY_ADD_EXP = 4;	// ��4��Ǯ��һ�ξ���
const int EXP_ADD_ONCE = 4;		// ��һ�μ�4�㾭��
const int REFRESH_ONCE = 2;		// ˢ��һ���̵�2��Ǯ

// �ȼ�
const int MAX_LEVEL = 6;
const int EXP_LEVEL[MAX_LEVEL + 5] = { 0, 6, 6 + 10, 6 + 10 + 14, 6 + 10 + 14 + 18, 6 + 10 + 14 + 18 + 22, 6 + 10 + 14 + 18 + 22 + 26 };

//��Ϸʤ���ж�
#define DRAW 0		//ƽ��
#define M_WIN 1		//�ҷ�ʤ��
#define E_WIN 2		//�з�ʤ��

class GameController
{
public:
	GameController();						//���캯��
	~GameController();						//��������
	static GameController* getInstance();	//���һ��ʵ��
	static void destroyInstance();			//����ʵ��

	// ��ȡ���̶���
	ChessBoard* getChessBoard() { return _chessBoard; };

	// ��ȡ�̵����
	Shop* getShop() { return _shop; };

	inline bool isInMyBound(struct Command pos);			//�жϵ��Ƿ����ҷ�������
	inline bool hasHero(struct Command pos);				//�жϸ�λ���Ƿ�������
	inline bool placeHero(Hero* hero,struct Command pos);	//����Ӣ��
	int isEnd();											//�ж���Ϸ����

	// �����̴���Ӣ�۾���
	void createHeroInChessBoard(int idxOfHero);

	// ����Ӣ��
	void sellHero(Hero* soldSprite);

	// ����ý�ҵȣ��ı��̵��ң�����������ˢ�°�ť������ʹ��������ť��ʾΪ����״̬��ע�ⲻҪ������ʱ��ͻ��

private:
	static GameController* _instance;		//ʵ������
	Shop* _shop;							// ��¼һ���̵����
	ChessBoard* _chessBoard;				//��������
	int enemyMoney;							// �з����
	int enemyExp;							// �з�����
	int enemyLevel;							// �з��ȼ�
};