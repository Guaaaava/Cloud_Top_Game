#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

<<<<<<< Updated upstream
=======
#include "ui/CocosGUI.h"
using namespace ui;

#define WORDS_GAME_NAME 1001	// �������֮ս������
#define WORDS_START     1002	// ����ʼ������
#define WORDS_SHOP      1003	// ���̵ꡱ����
#define WORDS_EXIT      1004	// ���˳�������
#define WORDS_LEVELUP	1005	// ������������
#define WORDS_REFRESH	1006	// "ˢ�¡�����

const float SHOP_HEIGHT = 210.0f;
const float CHESSBOARD_WIDTH = 1150.0f;
const float CHESSBOARD_HEIGHT = 950.0f;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
	virtual bool init();
=======
	virtual bool init();		// ��ʼ������

	LayerColor* layer;			// ��¼������

private:
	// virtual bool onTouchBegan(Touch* touch, Event* event);	// ���°�ť�Ļص�

	// virtual void onTouchEnded(Touch* touch, Event* event);	// �ͷŰ�ť�Ļص�
>>>>>>> Stashed changes
};