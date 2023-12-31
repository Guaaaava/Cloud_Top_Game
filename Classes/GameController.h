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

	void createStandOrigin();								//����վ������

	Vec2 getStandPos(int x,int y);							//��ȡվ��������

	POS getSizePos(Vec2 pos);								//��ȡ��������

	inline int isInStand(Vec2 pos);						//�жϵ��Ƿ���վ������

	inline bool isInMyBound(struct POS pos);			//�жϵ��Ƿ����ҷ�������
	inline bool hasHero(struct POS pos);				//�жϸ�λ���Ƿ�������
	inline bool placeHero(Hero* hero,struct POS pos);	//����Ӣ��
	int isEnd();										//�ж���Ϸ����


	// �����̴���Ӣ�۾���
	void createHeroInChessBoard(int idxOfHero);

	// ����Ӣ��
	void sellHero(Hero* soldSprite);

	// ����ý�ҵȣ��ı��̵��ң�����������ˢ�°�ť������ʹ��������ť��ʾΪ����״̬��ע�ⲻҪ������ʱ��ͻ��

	Sprite* _standOrigin[BDSZ_Y + 2][BDSZ_X];		//վ������

private:
	static GameController* _instance;				//ʵ������
	Shop* _shop;									// ��¼һ���̵����
	ChessBoard* _chessBoard;						//��������

	Size _standSize;								//ÿ��վ������Ĵ�С
	Vec2 _standPos[8];								//ÿ��վ�������λ��(���½�)

	int enemyMoney;									// �з����
	int enemyExp;									// �з�����
	int enemyLevel;									// �з��ȼ�
};