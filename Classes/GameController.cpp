#include "GameController.h"

/****************************************************
 * 功能：游戏控制器默认函数
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

	myMoney = shop->getMoney();
	myExp = shop->getExp();
	myLevel = shop->getLevel();

	enemyMoney = 0;
	enemyExp = 0;
	enemyLevel = 0;
}
GameController::~GameController()
{
	// 销毁商店对象
	CC_SAFE_DELETE(shop);

	GameController::destroyInstance();
}

