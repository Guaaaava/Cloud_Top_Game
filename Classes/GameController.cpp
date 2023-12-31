#include "GameController.h"
#include "CTGScene.h"
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
	/* 商店初始化 */
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);	// 加入计数

	/* 棋盘初始化 */
	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

	/* 获得屏幕 */
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* 站立区的初始化 */
	auto width = visibleSize.width * 0.6;							//每个站立区的宽度
	auto height = visibleSize.height * 0.4 / 6;						//每个站立区的高度
	_standSize = Size(width, height);								//每个站立区的大小
	
	_standPos[0] = origin + visibleSize / 2 - Vec2(width / 2, height * 4 - 10);//每个站立区的左下角
	
	for (int i = 1; i < 8; i++) {
		if (i == 1 || i == 7) {
			_standPos[i] = _standPos[i - 1] + Vec2(0, height + 30);
		}
		else {
			_standPos[i] = _standPos[i - 1] + Vec2(0, height);
		}
	}

	/* 创建站立区域 */
	createStandOrigin();

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
}

/*************
* 函数参数: 
* 函数功能: 创建区域
*	返回值: 无
* ************/
void GameController::createStandOrigin()
{
	std::string pic_pth = "standOrigin.png";	//站立区域图片
	auto sigWidth = _standSize.width / BDSZ_X;	//单个格的宽度
	auto sigHeight = _standSize.height;			//单个格的高度
	Size sigSize(sigWidth, sigHeight);			//单个格的大小

	/* 创建多个格 */
	for (int i = 0; i < BDSZ_Y+2; i++) {
		for (int j = 0; j < BDSZ_X; j++) {
			auto sprite = Sprite::create(pic_pth);	//创建图片
			Vec2 pos = getStandPos(j, i);			//获得位置

			if (sprite == nullptr) {
				CCLOG("区域创建失败!");
			}
			else {
				sprite->setContentSize(sigSize);			//设置大小
				sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//设置锚点
				sprite->setPosition(pos);					//设置位置
				sprite->setVisible(false);					//设为不可见
				CTGScene::getLayer()->addChild(sprite, 3);	//加入层中
				_standOrigin[i][j] = sprite;
			}
		}
	}
	

	return;
}

/*************
* 函数参数: 点阵位置
* 函数功能: 通过点阵位置获得真实位置
*	返回值: 真实位置
* ************/
inline Vec2 GameController::getStandPos(int x,int y)
{
	Vec2 origin = _standPos[y];
	Size size = _standSize;
	float sigWidth = _standSize.width / BDSZ_X;
	float sigHeight = _standSize.height;

	return origin + Vec2(sigWidth * (x + 0.5), sigHeight * 0.5);
}

/*************
* 函数参数: 真实位置
* 函数功能: 通过真实位置获得点阵位置
*	返回值: 点阵位置
* ************/
POS GameController::getSizePos(Vec2 pos)
{
	POS loc;

	int i = isInStand(pos);

	if (i != -1) {
		for (int j = 0; j < BDSZ_X; j++) {
			auto size = _standOrigin[i][j]->getContentSize();
			auto origin = _standOrigin[i][j]->getPosition() - size / 2;
			if (pos > origin && pos < origin + size) {
				loc._type = STAND;
				loc._x = j;
				loc._y = i;
			}
		}
	}
	else {
		loc._type = OTHER;
		loc._y = -1;
		loc._x = -1;
	}

	return loc;
}

/*************
* 函数参数: 实际位置
* 函数功能: 判断点是否在备战席区域
*	返回值: true:在备战席区域;
*			false:不在备战席
* ************/
inline int GameController::isInStand(Vec2 pos)
{
	for (int i = 0; i < 8; i++) {
		auto origin = _standPos[i];
		if (pos.x > origin.x &&
			pos.y > origin.y &&
			pos.x < origin.x + _standSize.width &&
			pos.y < origin.y + _standSize.height)
		{
			return i;
		}
	}

	return -1;
}

/*************
* 函数参数: Command pos:要判断的点
* 函数功能: 判断一点是否在我方棋盘内
*	返回值: true:在我方棋盘;
*			false:不在我方棋盘
* ************/
inline bool GameController::isInMyBound(struct POS pos)
{
	if ((pos._x >= 0) && (pos._x < BDSZ_X / 2) && (pos._y >= 0) && (pos._y < BDSZ_Y / 2)) {
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
inline bool GameController::hasHero(struct POS pos)
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
inline bool GameController::placeHero(Hero* hero, struct POS pos)
{
	/* 棋子加入虚拟棋盘 */
	auto board = _chessBoard->getBoard();
	(*board)[pos._x][pos._y] = hero;

	/* 棋子加入真实棋盘 */
	//hero->setPosition(getTruePos(pos._type, pos._x, pos._y));

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

	auto newHero = Annie::create();		// 创建英雄

	// 英雄属性
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	auto pos = _standOrigin[0][0]->getPosition();
	newHero->setPosition(pos);

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
