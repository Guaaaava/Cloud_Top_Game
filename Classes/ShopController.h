#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

/****************************************************
 * ���ܣ��̵������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class ShopController
{
public:
	static ShopController* getInstance();
	static void destroyInstance();
	~ShopController();

	// �������ư�ť����̬��Ա������ֱ�ӵ��ã�
	static Button* createChessButton(const std::string normalPicPath, const std::string selectedPicPath, const Vec2 position);

	// ��ȡ���������ſ�������λ�ã���̬��Ա������ֱ�ӵ��ã�
	static Vec2 getChessPosition(const int numofChess);

private:
	const float shopStart_x = (Director::getInstance()->getVisibleSize()).width * 0.15f;			// �̵꿪ʼ������
	const float shopWidth = (Director::getInstance()->getVisibleSize()).width - 2 * shopStart_x;	// �̵곤��
	const float chessWidth = shopWidth / 5.0f;														// ���Ƴ���

	static ShopController* instance;

};