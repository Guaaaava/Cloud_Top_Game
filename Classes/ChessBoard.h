#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <list>
#include <map>

/****************************************************
 * ���ܣ�������������
 * ˵����Ref�����࣬�Զ��ͷ��ڴ�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��26��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class ChessBoard : public Ref
{
public:
	CREATE_FUNC(ChessBoard);
	
	virtual bool init();

	// ��ȡ�ҷ����Ӽ��ϣ�get��
	std::list<Sprite*>* getMyHeroes() { return &myHeroes; };

	// ��ȡ�з����Ӽ��ϣ�get��
	std::list<Sprite*>* getEnemyHeroes() { return &enemyHeroes; };
	
	// ��ȡ�ҷ����ӱ��map��get��
	std::map<Sprite*, int>* getMyHeroesIdxMap() { return &myHeroesIdx; };

	// ��ѯ�ҷ������Ƿ����ָ��Ӣ�ۣ��������򷵻ر�ţ����򷵻�-1
	int findHero(Sprite* hero);

private:
	// ��¼�ҷ����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Sprite*> myHeroes;

	// ��¼�з����Ӽ��ϣ�Sprite*���Ի���Hero*��
	std::list<Sprite*> enemyHeroes;

	// ��¼�ҷ����ӱ��
	std::map<Sprite*, int> myHeroesIdx;
};