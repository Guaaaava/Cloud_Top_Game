#pragma once

/**************
* ����:�������ʵ��
* ����:�����
* ʱ��:2023��12��28��
**************/

#include"cocos2d.h"
USING_NS_CC;
#include"Hero.h"

#include"GameController.h"

#include<Vector>

#define BDSZ_X 20	//�������̵ĳ�
#define BDSZ_Y 6	//�������̵Ŀ�

/* ��ʾ����Ľṹ�� */
struct Command
{
	int _x;		//���������
	int _y;		//����������
};

class ChessBoard : public Ref
{
private:
	// ��¼�ҷ����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Hero*> _myHeroes;

	// ��¼�з����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Hero*> _enemyHeroes;

	// ��¼�ҷ����ӱ��
	std::map<Hero*, int> _myHeroesIdx;

	//��������
	std::vector<std::vector<Hero*>> _BOARD;
public:
	CREATE_FUNC(ChessBoard);

	virtual bool init();			//��ʼ������

	// ��ȡ�ҷ����Ӽ��ϣ�get��
	std::list<Hero*>* getMyHeroes() { return &_myHeroes; };

	// ��ȡ�з����Ӽ��ϣ�get��
	std::list<Hero*>* getEnemyHeroes() { return &_enemyHeroes; };

	// ��ȡ�ҷ����ӱ��map��get��
	std::map<Hero*, int>* getMyHeroesIdxMap() { return &_myHeroesIdx; };

	//�����������(get)
	std::vector<std::vector<Hero*>>* getBoard() { return &_BOARD; };

	// ��ѯ�ҷ������Ƿ����ָ��Ӣ�ۣ��������򷵻ر�ţ����򷵻�-1
	int findHero(Hero* hero);
};