#pragma once

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

#include "ConfigController.h"

#include <random>		// C++11产生随机数
#include <ctime>

const int NUM_CHESS_SHOP = 4;	// 当前商店展示四张卡牌
const int NUM_CHESS = 10;		// 当前牌库10张牌

/****************************************************
 * 功能：商店数据类型
 * 说明：Ref派生类，自动释放内存
 * 作者：黄辰宇
 * 时间：2023年12月22日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class Shop : public Ref
{
public:
	CREATE_FUNC(Shop);

	// 初始化商店对象（重写）
	virtual bool init();

	void initAllChessPrice();			// 初始化所有英雄价格
	void getChessPrice();				// 获取当前卡牌价格

	// 创建通用的卡牌按钮
	void createChessButton(int numOFChess, int index);

	void createInitialChessButton();	// 创建开始的卡牌按钮
	void createLevelUpButton();			// 创建升级按钮
	void createRefreshShopButton();		// 创建刷新商店按钮
	void createLevelLabel();			// 创建经验值标签
	void createMoneyLabel();			// 创建金币标签
	void createSellSprite();			// 创建出售区域精灵
	
	// 获取从左到右第numofChess张卡牌中心位置
	Vec2 getChessPosition(const int numofChess);

	void updateLevelLabel();		// 更新等级标签
	void updateMoneyLabel();		// 更新金币标签
	void updateButtonState();		// 更新按钮禁用状态

	void transformExpToLevel();			// 经验转化为等级
	void refreshShop();					// （根据等级）刷新商店

	int getHeroPrice(int idxOfHero);	// 获取编号为idx的英雄价格
	Sprite* getSellOrigin() { return spriteSellOrigin; };	// 获取出售区域碰撞箱
	int getMoney() { return money; };	// 获取当前金币
	int getExp() { return expr; };		// 获取当前经验
	int getLevel() { return level; };	// 获取当前等级

	void addMoney(int moneyAdded) { money += moneyAdded; };	// 加钱函数，记得加完后更新标签，更新按钮状态
	void addExp(int expAdded) { expr += expAdded; };		// 加经验函数，记得加完后转化为等级，更新标签，更新按钮状态，改变可上场英雄数

private:
	const float shopStart_x = (Director::getInstance()->getVisibleSize()).width * 0.15f;			// 商店开始横坐标
	const float shopWidth = (Director::getInstance()->getVisibleSize()).width - 2 * shopStart_x;	// 商店长度
	const float chessWidth = shopWidth / NUM_CHESS_SHOP;											// 卡牌长度

	const std::string words_level_1 = ConfigController::getInstance()->getCNByID(WORDS_LEVEL_1);	// 等级标签1
	const std::string words_level_2 = ConfigController::getInstance()->getCNByID(WORDS_LEVEL_2);	// 等级标签2
	const std::string words_money = ConfigController::getInstance()->getCNByID(WORDS_MONEY);		// 金币标签

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Button* buttonLevelUp;			// 升级按钮
	Button* buttonRefreshShop;		// 刷新商店按钮

	Sprite* spriteLevelLabel;		// 经验值标签背景精灵
	Label* labelLevel;				// 经验值背景精灵上标签
	Sprite* spriteMoneyLabel;		// 金币标签背景精灵
	Label* labelMoney;				// 金币背景精灵上标签

	Sprite* spriteSellOrigin;			// 出售区域
	Label* labelSellOrigin;				// 出售区域上标签

	int allChessPrice[NUM_CHESS + 5];	// 存所有英雄价格

	Button* chessButton[NUM_CHESS_SHOP + 5];	// 存当前卡牌按钮
	int chessPrice[NUM_CHESS_SHOP + 5];			// 存当前卡牌价格

	int money;	// 金币
	int expr;	// 经验
	int level;	// 等级
};