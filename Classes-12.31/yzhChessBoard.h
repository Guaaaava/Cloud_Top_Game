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
#include <map>

#define BDSZ_X 9	//�������̵ĳ�
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

private:
	// ��¼�ҷ����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Hero*> _myHeroes;

	// ��¼�з����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Hero*> _enemyHeroes;

	// ��¼�ҷ����ӱ��
	std::map<Hero*, int> _myHeroesIdx;

	//��������
	std::vector<std::vector<Hero*>> _BOARD;

	//���ⱸսϯ
	std::vector<Hero*>_STAND;
};