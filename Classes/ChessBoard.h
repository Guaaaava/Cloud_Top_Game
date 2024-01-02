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

//��������
#define STAND 0//վ������
#define OTHER 1//��������

/* ��ʾ����Ľṹ�� */
struct POS
{
	int _type = OTHER;
	int _x = -1;		//���������
	int _y = -1;		//����������

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

	virtual bool init();			//��ʼ������

	std::list<HeroMsg>* getMyHeroes() { return &_myHeroes; };			// ��ȡ�ҷ�Ӣ������
	std::list<HeroMsg>* getEnemyHeroes() { return &_enemyHeroes; };	// ��ȡ�з�Ӣ������

	// ��ñ�սϯ
	std::list<HeroMsg>* getStandHeroes() { return &_STAND; };

	// �����������
	std::vector< std::vector<HeroMsg> >* getBoard() { return &_BOARD; };

private:
	std::list<HeroMsg> _myHeroes;			// ��¼�ҷ�Ӣ��
	std::list<HeroMsg> _enemyHeroes;		// ��¼�з�Ӣ��

	//���ⱸսϯ
	std::list<HeroMsg> _STAND;

	// ��������
	std::vector< std::vector<HeroMsg> > _BOARD;
};