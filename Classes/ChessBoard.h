#pragma once

#include "cocos2d.h"
USING_NS_CC;

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
	Vector<Sprite*>* getMyHeroes() { return &myHeroes; };

	// ��ȡ�з����Ӽ��ϣ�get��
	Vector<Sprite*>* getEnemyHeroes() { return &enemyHeroes; };

private:
	// ��¼�ҷ����Ӽ��ϣ�Sprite*���Ի���Hero*��
	Vector<Sprite*> myHeroes;

	// ��¼�з����Ӽ��ϣ�Sprite*���Ի���Hero*��
	Vector<Sprite*> enemyHeroes;
};