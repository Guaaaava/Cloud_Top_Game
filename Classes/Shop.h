#pragma once

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

#include "ConfigController.h"

#include <random>		// C++11���������
#include <ctime>

const int NUM_CHESS_SHOP = 4;	// ��ǰ�̵�չʾ���ſ���
const int NUM_CHESS = 10;		// ��ǰ�ƿ�10����

/****************************************************
 * ���ܣ��̵���������
 * ˵����Ref�����࣬�Զ��ͷ��ڴ�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class Shop : public Ref
{
public:
	CREATE_FUNC(Shop);

	// ��ʼ���̵������д��
	virtual bool init();

	void initAllChess();				// ��ʼ���ƿ�
	void initAllChessButton();			// ��ʼ�����п��ư�ť

	void createInitChessButton();		// ������ʼ�Ŀ��ư�ť

	void createLevelUpButton();			// ����������ť
	void levelUpButton_onClick(Ref* sender, Widget::TouchEventType type);	// ������ť�Ļص�����
	
	void getChessPrice();				// ��ȡ��ǰ���Ƽ۸�

	void createRefreshShopButton();		// ����ˢ���̵갴ť
	void refreshShopButton_onClick(Ref* sender, Widget::TouchEventType type);	// ˢ���̵�Ļص�����

	void createLevelLabel();			// ��������ֵ��ǩ
	void createMoneyLabel();			// ������ұ�ǩ

	// ��ȡ�����ҵ�numofChess�ſ�������λ��
	Vec2 getChessPosition(const int numofChess);

	void transformExpToLevel();			// ����ת��Ϊ�ȼ�
	std::string getLevelLabelStr();		// �õ��ȼ���ǩ���º������
	
	void refreshShop();					// �����ݵȼ���ˢ���̵�
	std::string getMoneyLabelStr();		// �õ���ұ�ǩ���º������

	void updateButtonState();			// ���°�ť����״̬

	int getMoney() { return money; };	// ��ȡ��ǰ���
	int getExp() { return expr; };		// ��ȡ��ǰ����
	int getLevel() { return level; };	// ��ȡ��ǰ�ȼ�

private:
	const float shopStart_x = (Director::getInstance()->getVisibleSize()).width * 0.15f;			// �̵꿪ʼ������
	const float shopWidth = (Director::getInstance()->getVisibleSize()).width - 2 * shopStart_x;	// �̵곤��
	const float chessWidth = shopWidth / NUM_CHESS_SHOP;											// ���Ƴ���

	const std::string words_level_1 = ConfigController::getInstance()->getCNByID(WORDS_LEVEL_1);	// �ȼ���ǩ1
	const std::string words_level_2 = ConfigController::getInstance()->getCNByID(WORDS_LEVEL_2);	// �ȼ���ǩ2
	const std::string words_money = ConfigController::getInstance()->getCNByID(WORDS_MONEY);		// ��ұ�ǩ

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Button* buttonLevelUp;			// ������ť
	Button* buttonRefreshShop;		// ˢ���̵갴ť

	Sprite* spriteLevelLabel;		// ����ֵ��ǩ��������
	Label* labelLevel;				// ����ֵ���������ϱ�ǩ
	Sprite* spriteMoneyLabel;		// ��ұ�ǩ��������
	Label* labelMoney;				// ��ұ��������ϱ�ǩ

	int allChess[NUM_CHESS + 5];			// ���п��ƣ�init�󲻿ɸı䣩
	Button* allChessButton[NUM_CHESS + 5];	// ���п��ư�ť��init�󲻿ɸı䣩

	int chess[NUM_CHESS_SHOP + 5];			// �浱ǰ����
	Button* chessButton[NUM_CHESS_SHOP + 5];	// �浱ǰ���ư�ť
	int chessPrice[NUM_CHESS_SHOP + 5];			// �浱ǰ���Ƽ۸�

	int money;	// ���
	int expr;	// ����
	int level;	// �ȼ�
};