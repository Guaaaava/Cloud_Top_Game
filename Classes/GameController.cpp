#include "GameController.h"
/**************
* 功能:游戏逻辑控制器
* 作者:尹泽河
* 时间:2023年12月28日
**************/

GameController* GameController::_instance = nullptr;

/*************
* 函数参数: 无
* 函数功能: 构造函数
*	返回值: 无
* ************/
GameController::GameController()
{
	// 初始化
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);	// 加入计数

	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

	enemyMoney = 0;	//敌方金币
	enemyExp = 0;	//敌方经验
	enemyLevel = 0;	//敌方等级
}

/*************
* 函数参数: 无
* 函数功能: 析构函数
*	返回值: 无
* ************/
GameController::~GameController()
{
	// 销毁商店对象
	CC_SAFE_DELETE(_shop);

	// 销毁棋盘对象
	CC_SAFE_DELETE(_chessBoard);

	GameController::destroyInstance();
}

/*************
* 函数参数: 无
* 函数功能: 获取实例
*	返回值: 实例
* ************/
GameController* GameController::getInstance()
{
	if (_instance == nullptr) {
		_instance = new GameController();
	}

	return _instance;
}

/*************
* 函数参数: 无
* 函数功能: 销毁实例
*	返回值: 实例
* ************/
void GameController::destroyInstance()
{
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}

	return;
}

/*************
* 函数参数: Command pos:要判断的点
* 函数功能: 判断一点是否在我方棋盘内
*	返回值: true:在我方棋盘;
*			false:不在我方棋盘
* ************/
inline bool GameController::isInMyBound(Command pos)
{
	if ((pos._x >= 0) && (pos._x < BDSZ_X/2) && (pos._y >= 0) && (pos._y < BDSZ_Y / 2)) {
		return true;
	}

	return false;
}

/*************
* 函数参数: Command& pos:要判断的坐标
* 函数功能: 判断该点是否有棋子
*	返回值: true:该点有棋子;
*			false:该点没有棋子
* ************/
inline bool GameController::hasHero(Command pos)
{
	/* 该点不在我方棋盘内或者该点有英雄均视为该点有棋子 */
	auto board = _chessBoard->getBoard();
	if (!isInMyBound(pos) || (*board)[pos._x][pos._y] != nullptr) {
		return true;
	}

	return false;
}

/*************
* 函数参数: Command pos:要放置的位置
*			Hero* hero:要放置的棋子
* 函数功能: 在某点放置棋子
*	返回值: 无
* ************/
inline bool GameController::placeHero(Hero* hero, Command pos)
{
	auto board = _chessBoard->getBoard();
	(*board)[pos._x][pos._y] = hero;
	return false;
}

/*************
* 函数参数: 无
* 函数功能: 判断游戏是否结束
*	返回值: DRAW:平局
*			M_WIN:我方胜利
*			E_WIN:敌方胜利
* ************/
int GameController::isEnd()
{
	bool myWin = true;
	bool enemyWin = true;

	if (myWin) {
		return M_WIN;
	}
	else if (enemyWin) {
		return E_WIN;
	}
	else {
		return DRAW;
	}

	return false;
}

/****************************************************
 * 功能：在棋盘上创建英雄，z 值为 3
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月28日
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

	auto newHero = Samurai::create();		// 创建英雄

	// 英雄属性
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	newHero->setPosition(500, 600);

	// 维护棋盘成员集合、编号map
	_chessBoard->getMyHeroes()->push_back(newHero);
	_chessBoard->getMyHeroesIdxMap()->insert({ newHero, idxOfHero });
}

/****************************************************
 * 功能：出售英雄，添加金币，更新标签，更新按钮状态
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月28日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::sellHero(Hero* soldHero)
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("棋盘内无英雄，英雄出售失败！\n");
		return;
	}

	int idxOfHero = _chessBoard->findHero(soldHero);
	if (idxOfHero == -1)
	{
		CCLOG("不存在编号为%d的英雄，出售失败！\n", idxOfHero);
		return;
	}

	myHeroes->remove(soldHero);	// 从棋盘对象里，我方棋子集合中删除该英雄
	soldHero->removeFromParentAndCleanup(true);	// 从界面上移除该精灵
	// 增加我方金币
	_shop->addMoney(_shop->getHeroPrice(idxOfHero));
	// 更新标签
	_shop->updateLevelLabel();
	_shop->updateMoneyLabel();
	// 更新按钮状态
	_shop->updateButtonState();
}
