#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;



#include"HeroAction.h"

#define WORDS_GAME_NAME 1001	// �������֮ս������
#define WORDS_START     1002	// ����ʼ������
#define WORDS_SHOP      1003	// ���̵ꡱ����
#define WORDS_EXIT      1004	// ���˳�������

/****************************************************
 * ���ܣ���ʾ�����֮ս����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��7��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class CTGScene : public Scene
{
public:
	CREATE_FUNC(CTGScene);		// ���� create() ����

	virtual bool init();

	// ����һ��ͨ�ð�ť
	static MenuItemImage* createGameButton(std::string name, const ccMenuCallback& callback);

private:
	// ��¼������
	Node* prt_backGround;

	// ��¼�̵갴ť��Сλ��
	Rect prt_shopButtonSize;

	// ��Ϸ��ʼ��ť�ĵ���¼�
	void menuStartCallback(Ref* sender);

	// ���̵갴ť�ĵ���¼�
	void menuOpenShopCallback(Ref* sender);

	// �˳���Ϸ��ť�ĵ���¼�
	void menuExitGameCallback(Ref* sender);

	// ���°�ť�Ļص�
	virtual bool onTouchBegan(Touch* touch, Event* event);

	// �ͷŰ�ť�Ļص�
	virtual void onTouchEnded(Touch* touch, Event* event);

	// ����һ���̵���
	void createShopNode();


};