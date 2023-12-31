#pragma once

/**************
* ����:�������ʵ��
* ����:�����
* ʱ��:2023��12��28��
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"Hero.h"

#include <list>

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
public:
	CREATE_FUNC(ChessBoard);

	virtual bool init();			//��ʼ������

	std::list<HeroMsg>* getMyHeroes() { return &_myHeroes; };			// ��ȡ�ҷ�Ӣ������
	std::list<HeroMsg>* getEnemyHeroes() { return &_enemyHeroes; };	// ��ȡ�з�Ӣ������

	// ��ñ�սϯ
	std::vector<HeroMsg>* getRelaxHeroes() { return &_RELAX; };

	// �����������
	std::vector< std::vector<HeroMsg> >* getBoard() { return &_BOARD; };

private:
	std::list<HeroMsg> _myHeroes;			// ��¼�ҷ�Ӣ��
	std::list<HeroMsg> _enemyHeroes;		// ��¼�з�Ӣ��

	// ��սϯ
	std::vector<HeroMsg> _RELAX;

	// ��������
	std::vector< std::vector<HeroMsg> > _BOARD;
};