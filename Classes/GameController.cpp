#include "GameController.h"
#include "CTGScene.h"

/****************************************************
 * 功能：游戏逻辑控制器默认函数
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
GameController* GameController::instance = nullptr;		// 给静态成员分配空间
GameController* GameController::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameController();
	}
	return instance;
}
void GameController::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
GameController::GameController()
{
	// 初始化
	shop = Shop::create();
	CC_SAFE_RETAIN(shop);	// 加入计数

	chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(chessBoard);

	enemyMoney = 0;
	enemyExp = 0;
	enemyLevel = 0;
}
GameController::~GameController()
{
	// 销毁商店对象
	CC_SAFE_DELETE(shop);

	// 销毁棋盘对象
	CC_SAFE_DELETE(chessBoard);

	GameController::destroyInstance();
}

/****************************************************
 * 功能：在棋盘上创建英雄，z 值为 3
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::createHeroInChessBoard(int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d超过了最大编号%d，英雄创建失败！\n", idxOfHero, NUM_CHESS);
		return;
	}

	std::string heroPicPath = ConfigController::getInstance()->getPathByID(PATH_NORMAL[idxOfHero]);
	auto newHero = Sprite::create(heroPicPath);		// 创建英雄

	// 英雄属性
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	newHero->setPosition(500, 600);

	// 维护棋盘成员集合
	chessBoard->getMyHeroes()->pushBack(newHero);
}

