#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

#include "Hero.h"
#include "ChessBoard.h"
#include "WebSocketClient.h"

const float SHOP_HEIGHT = 210.0f;		// �̵꿨�Ƹ߶�
const float CHESSBOARD_WIDTH = 1150.0f;	// ����ͼƬ���
const float CHESSBOARD_HEIGHT = 950.0f;	// ����ͼƬ�߶�

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

	virtual bool init();		// ��ʼ������

	static LayerColor* getLayer() { return layer; };	// ��ȡ�����㣨��̬��Ա��
	
	//static websocket_endpoint* getEndpoint() { return client; };

	//~CTGScene() { CC_SAFE_DELETE(client); };
private:

	static LayerColor* layer;	// ��¼�����㣨��̬��Ա��

	HeroMsg touchingHero;		// ��ѡ�е�Ӣ��
	Vec2 firstPos;				//��ѡ�е�Ӣ�۵ĳ�ʼλ��

	virtual bool onTouchBegan(Touch* touch, Event* event);	// �������Ļص�
	virtual void onTouchMoved(Touch* touch, Event* event);	// �ƶ����Ļص�
	virtual void onTouchEnded(Touch* touch, Event* event);	// �ͷ����Ļص�

	HeroMsg judgePointInSprite(Point pnt);	// �жϴ������Ƿ�������Ӣ�������ڣ����򷵻ظ�Ӣ�ۣ����򷵻�nullptr

	//static websocket_endpoint* client; // �ͻ���
};