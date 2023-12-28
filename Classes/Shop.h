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

	void initAllChessPrice();			// ��ʼ������Ӣ�ۼ۸�
	void getChessPrice();				// ��ȡ��ǰ���Ƽ۸�

	// ����ͨ�õĿ��ư�ť
	void createChessButton(int numOFChess, int index);

	void createInitialChessButton();	// ������ʼ�Ŀ��ư�ť
	void createLevelUpButton();			// ����������ť
	void createRefreshShopButton();		// ����ˢ���̵갴ť
	void createLevelLabel();			// ��������ֵ��ǩ
	void createMoneyLabel();			// ������ұ�ǩ
	void createSellSprite();			// ��������������
	
	// ��ȡ�����ҵ�numofChess�ſ�������λ��
	Vec2 getChessPosition(const int numofChess);

	void updateLevelLabel();		// ���µȼ���ǩ
	void updateMoneyLabel();		// ���½�ұ�ǩ
	void updateButtonState();		// ���°�ť����״̬

	void transformExpToLevel();			// ����ת��Ϊ�ȼ�
	void refreshShop();					// �����ݵȼ���ˢ���̵�

	int getHeroPrice(int idxOfHero);	// ��ȡ���Ϊidx��Ӣ�ۼ۸�
	Sprite* getSellOrigin() { return spriteSellOrigin; };	// ��ȡ����������ײ��
	int getMoney() { return money; };	// ��ȡ��ǰ���
	int getExp() { return expr; };		// ��ȡ��ǰ����
	int getLevel() { return level; };	// ��ȡ��ǰ�ȼ�

	void addMoney(int moneyAdded) { money += moneyAdded; };	// ��Ǯ�������ǵü������±�ǩ�����°�ť״̬
	void addExp(int expAdded) { expr += expAdded; };		// �Ӿ��麯�����ǵü����ת��Ϊ�ȼ������±�ǩ�����°�ť״̬���ı���ϳ�Ӣ����

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

	Sprite* spriteSellOrigin;			// ��������
	Label* labelSellOrigin;				// ���������ϱ�ǩ

	int allChessPrice[NUM_CHESS + 5];	// ������Ӣ�ۼ۸�

	Button* chessButton[NUM_CHESS_SHOP + 5];	// �浱ǰ���ư�ť
	int chessPrice[NUM_CHESS_SHOP + 5];			// �浱ǰ���Ƽ۸�

	int money;	// ���
	int expr;	// ����
	int level;	// �ȼ�
};