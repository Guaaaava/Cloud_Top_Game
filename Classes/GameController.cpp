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
	// 初始化并加入计数
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);

	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

	_myLittleHero = LittleHero::create();
	CC_SAFE_RETAIN(_myLittleHero);

	_enemyLittleHero = LittleHero::create();
	CC_SAFE_RETAIN(_enemyLittleHero);

	// 小小英雄动画
	_myLittleHero->heroRunToPos(Vec2(150, 300));
	CTGScene::getLayer()->addChild(_myLittleHero, 3);
	_enemyLittleHero->heroRunToPos(Vec2(950, 750));
	CTGScene::getLayer()->addChild(_enemyLittleHero, 3);

	roundCounter = 1;
	heroTagCounter = 1;

	timeLeft = 0;

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
}

/*************
* 函数参数: 无
* 函数功能: 析构函数
*	返回值: 无
* ************/
GameController::~GameController()
{
	// 销毁创建时Retain的Hero
	std::list<HeroMsg>::iterator it;
	auto myHeroes = _chessBoard->getMyHeroes();
	for (it = myHeroes->begin(); it != myHeroes->end(); it++)
	{
		auto _hero = it->hero;
		CC_SAFE_DELETE(_hero);
	}
	auto enemyHeroes = _chessBoard->getEnemyHeroes();
	for (it = enemyHeroes->begin(); it != enemyHeroes->end(); it++)
	{
		auto _hero = it->hero;
		CC_SAFE_DELETE(_hero);
	}

	// 销毁商店对象
	CC_SAFE_DELETE(_shop);

	// 销毁棋盘对象
	CC_SAFE_DELETE(_chessBoard);

	// 销毁小小英雄对象
	CC_SAFE_DELETE(_myLittleHero);
	CC_SAFE_DELETE(_enemyLittleHero);

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
	for (int i = 0; i < BDSZ_Y + 2; i++) {
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
inline Vec2 GameController::getStandPos(int x, int y)
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
	if (!isInMyBound(pos) || (*board)[pos._x][pos._y].silentSprite != nullptr) {
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
inline bool GameController::placeHero(HeroMsg hero, struct POS pos)
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
void GameController::createHeroInChessBoard(const int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d超过了最大编号%d，英雄创建失败！\n", idxOfHero, NUM_CHESS);
		return;
	}

	// 创建静止精灵
	std::string picPath = ConfigController::getInstance()->getPathByID(PATH_SILENT_SPRITE[idxOfHero]);
	auto newSilentSprite = Sprite::create(picPath);

	// 整合、维护英雄list
	HeroMsg newHeroMsg;
	newHeroMsg.init(nullptr, newSilentSprite, heroTagCounter, idxOfHero, 1);
	heroTagCounter++;	// 计数器++
	_chessBoard->getMyHeroes()->push_front(newHeroMsg);
	
	// 静止精灵属性（位置从棋盘获取）
	auto relaxPos = Vec2(200 + 80 * idxOfHero, 300);
	newSilentSprite->setPosition(relaxPos);

	// _chessBoard->getStandHeroes()->push_front(newHeroMsg);

	CTGScene::getLayer()->addChild(newSilentSprite, 3);

	// 合成精灵（两次，三个两星的情况）
	mergeHero();
	mergeHero();
}

/****************************************************
 * 功能：根据编号创建英雄
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月30日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
Hero* GameController::createHero(const int idxOfHero)
{
	Hero* newHero = nullptr;
	switch (idxOfHero)
	{
	case 1:
		newHero = Berserker::create();
		break;
	case 2:
		newHero = FireVizard::create();
		break;
	case 3:
		newHero = Knight::create();
		break;
	case 4:
		newHero = Kunoichi::create();
		break;
	case 5:
		newHero = LightningMage::create();
		break;
	case 6:
		newHero = NinjaMonk::create();
		break;
	case 7:
		newHero = NinjaPeasant::create();
		break;
	case 8:
		newHero = Samurai::create();
		break;
	case 9:
		newHero = SamuraiCommander::create();
		break;
	case 10:
		newHero = WandererMagican::create();
		break;
	default:
		break;
	};
	CC_SAFE_RETAIN(newHero);
	return newHero;
}

/****************************************************
 * 功能：出售英雄，添加金币，更新标签，更新按钮状态
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月28日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::sellHero(HeroMsg soldHero)
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("棋盘内无英雄，英雄出售失败！\n");
		return;
	}

	// 我方英雄集合中删除该英雄
	myHeroes->remove(soldHero);

	// 从界面上移除该静止精灵
	soldHero.silentSprite->removeFromParentAndCleanup(true);
	// 增加我方金币
	_shop->addMoney(_shop->getHeroPrice(soldHero.heroIdx));
	// 更新标签
	_shop->updateLevelLabel();
	_shop->updateMoneyLabel();
	// 更新按钮状态
	_shop->updateButtonState();
}

/****************************************************
 * 功能：创建倒计时
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月30日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::createCountDown()
{
	// 创建倒计时标签显示倒计时
	labelTimeCountDown = Label::createWithTTF("10", "fonts/simkai.ttf", 64);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	labelTimeCountDown->setPosition(Vec2(visibleSize.width * 0.075f, visibleSize.height * 0.925f));
	labelTimeCountDown->setTextColor(Color4B::ORANGE);
	CTGScene::getLayer()->addChild(labelTimeCountDown, 3);

	// 启动定时器，每秒更新倒计时
	timeLeft = 10;
	auto myScheduler = Director::getInstance()->getScheduler();
	myScheduler->schedule(
		CC_CALLBACK_1(GameController::updateCountDown, this), this, 1.0f ,false, "timer"
	);
}

/****************************************************
 * 功能：创建倒计时
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月30日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::updateCountDown(float dt)
{
	timeLeft--;
	labelTimeCountDown->setString(std::to_string(timeLeft));

	// 游戏结束的条件
	if (_myLittleHero->isDead())
	{
		// 提示失败
		auto label = Label::createWithTTF("YOU LOSE!", "fonts/simkai.ttf", 256);
		label->setPosition(Director::getInstance()->getVisibleSize() / 2);
		label->setTextColor(Color4B::WHITE);
		CTGScene::getLayer()->addChild(label, 4);

		auto myScheduler = Director::getInstance()->getScheduler();
		myScheduler->unschedule("timer", this);		// 停止倒计时
	}
	else if (_enemyLittleHero->isDead())
	{
		// 提示胜利
		auto label = Label::createWithTTF("YOU WIN!", "fonts/simkai.ttf", 256);
		label->setPosition(Director::getInstance()->getVisibleSize() / 2);
		label->setTextColor(Color4B::WHITE);
		CTGScene::getLayer()->addChild(label, 4);

		auto myScheduler = Director::getInstance()->getScheduler();
		myScheduler->unschedule("timer", this);		// 停止倒计时
	}

	if (timeLeft == 0)
	{
		if (roundCounter % 2 == 0)
		{
			switch (stopFight())	// 结束该回合对战并返回谁赢了
			{
			case ME:
				_enemyLittleHero->getHurted();
				_shop->addMoney(10);
				_shop->updateMoneyLabel();
				_shop->updateButtonState();
				break;
			case ENEMY:
				_myLittleHero->getHurted();
				_shop->addMoney(20);
				_shop->updateMoneyLabel();
				_shop->updateButtonState();
				break;
			case PEACE:
				_enemyLittleHero->getHurted();
				_myLittleHero->getHurted();
				_shop->addMoney(20);
				_shop->updateMoneyLabel();
				_shop->updateButtonState();
				break;
			default:
				break;
			}

			timeLeft = 10;
			roundCounter++;
		}
		else
		{
			startFight();	// 倒计时结束就开始该回合对战
			timeLeft = 15;
			roundCounter++;
		}
	}
}

/****************************************************
 * 功能：合成英雄
 * 作者：黄辰宇
 * 时间：2023年12月31日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::mergeHero()
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		return;
	}

	std::list<HeroMsg>::iterator it1, it2, it3;
	for (it1 = myHeroes->begin(); it1 != myHeroes->end(); it1++)
	{
		for (it2 = std::next(it1); it2 != myHeroes->end(); it2++)
		{
			if (it2->heroIdx == it1->heroIdx && it2->level == it1->level)
			{
				for (it3 = std::next(it2); it3 != myHeroes->end(); it3++)
				{
					if (it3->heroIdx == it2->heroIdx && it3->level == it2->level)
					{
						it2->silentSprite->removeFromParentAndCleanup(true);
						it3->silentSprite->removeFromParentAndCleanup(true);
						myHeroes->erase(it3);
						myHeroes->erase(it2);
						// erase后就消失了
						(it1->level)++;
						it1->silentSprite->setScale(it1->level);
						return;	// 结束本次merge
					}
				}
			}
		}
	}
}

/****************************************************
 * 功能：获取敌人
 * 作者：黄辰宇
 * 时间：2023年12月30日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::getEnemy()
{
	auto enemyHeroes = _chessBoard->getEnemyHeroes();
	for (int i = 1; i <= 5; i++)
	{
		std::string picPath = ConfigController::getInstance()->getPathByID(PATH_SILENT_SPRITE[i]);
		auto eSprite = Sprite::create(picPath);

		HeroMsg enemyHero;
		enemyHero.init(nullptr, eSprite, i, i, 1);

		enemyHeroes->push_front(enemyHero);

		// 静止精灵属性（位置从棋盘获取）
		auto relaxPos = Vec2(200 + 100 * i, 600);
		eSprite->setPosition(relaxPos);
		CTGScene::getLayer()->addChild(eSprite, 3);
	}
}

/****************************************************
 * 功能：游戏开始
 * 参数：英雄编号
 * 作者：黄辰宇
 * 时间：2023年12月30日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::gameStart()
{
	getEnemy();
	createCountDown();
}

/****************************************************
 * 功能：开始对战
 * 作者：黄辰宇
 * 时间：2023年12月31日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void GameController::startFight()
{
	// 获取我方信息
	auto myHeroes = _chessBoard->getMyHeroes();
	std::list<HeroMsg> myHeroesCopy(*myHeroes);
	
	// 获取对方信息
	auto enemyHeroes = _chessBoard->getEnemyHeroes();

	// 备战区英雄
	auto standHeroes = _chessBoard->getStandHeroes();

	/*
	std::list<HeroMsg>::iterator it;
	for (it = standHeroes->begin(); it != standHeroes->end(); it++)
	{
		myHeroesCopy.remove(*it);
	}
	*/

	// 集合地点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 myGatherPos = Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2);
	Vec2 enemyGatherPos = Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2);

	// 遍历所有英雄，获取攻击对象，更新动画开始位置，隐藏静止精灵
	std::list<HeroMsg>::iterator itMy, itEnemy;
	for (itMy = myHeroes->begin(); itMy != myHeroes->end(); itMy++)
	{
		itMy->hero = createHero(itMy->heroIdx);
		itMy->hero->changeMsg(ME);
		itMy->hero->upLevel(itMy->level - 1);
	}
	for (itEnemy = enemyHeroes->begin(); itEnemy != enemyHeroes->end(); itEnemy++)
	{
		itEnemy->hero = createHero(itEnemy->heroIdx);
		itEnemy->hero->changeMsg(ENEMY);
		itEnemy->hero->upLevel(itEnemy->level - 1);
	}

	for (itMy = myHeroes->begin(); itMy != myHeroes->end(); itMy++)
	{
		auto heroNow = itMy->hero;
		auto spriteNow = itMy->silentSprite;

		// 开始动画
		Vec2 startPos = spriteNow->getPosition();
		heroNow->initPos(startPos);
		heroNow->getEnemyInfor(*enemyHeroes);
		heroNow->heroRunToEnemyPos(myGatherPos);
		CTGScene::getLayer()->addChild(heroNow, 3);

		spriteNow->setVisible(false);
	}
	for (itEnemy = enemyHeroes->begin(); itEnemy != enemyHeroes->end(); itEnemy++)
	{
		auto heroNow = itEnemy->hero;
		auto spriteNow = itEnemy->silentSprite;

		// 开始动画
		Vec2 startPos = spriteNow->getPosition();
		heroNow->initPos(startPos);
		heroNow->getEnemyInfor(*myHeroes);
		heroNow->heroRunToEnemyPos(enemyGatherPos);
		CTGScene::getLayer()->addChild(heroNow, 3);

		spriteNow->setVisible(false);
	}
}

/****************************************************
 * 功能：结束对战
 * 作者：黄辰宇
 * 时间：2023年12月31日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
int GameController::stopFight()
{
	int myHp = 0;
	int enemyHp = 0;

	// 获取我方信息
	auto myHeroes = _chessBoard->getMyHeroes();
	std::list<HeroMsg> myHeroesCopy(*myHeroes);

	// 获取对方信息
	auto enemyHeroes = _chessBoard->getEnemyHeroes();

	// 备战区英雄
	auto standHeroes = _chessBoard->getStandHeroes();

	/*
	std::list<HeroMsg>::iterator it;
	for (it = standHeroes->begin(); it != standHeroes->end(); it++)
	{
		myHeroesCopy.remove(*it);
	}
	*/

	// 遍历所有英雄，移除动画
	std::list<HeroMsg>::iterator itMy, itEnemy;
	for (itMy = myHeroes->begin(); itMy != myHeroes->end(); itMy++)
	{
		myHp += itMy->hero->getHp();

		itMy->hero->removeFromParentAndCleanup(true);
		itMy->hero->stopAllActions();
		CC_SAFE_DELETE(itMy->hero);
		
		itMy->silentSprite->setVisible(true);
	}
	for (itEnemy = enemyHeroes->begin(); itEnemy != enemyHeroes->end(); itEnemy++)
	{
		enemyHp += itEnemy->hero->getHp();

		itEnemy->hero->removeFromParentAndCleanup(true);
		itEnemy->hero->stopAllActions();
		CC_SAFE_DELETE(itEnemy->hero);
		
		itEnemy->silentSprite->setVisible(true);
	}
	
	if (myHp > enemyHp)
		return ME;
	else if (myHp < enemyHp)
		return ENEMY;
	else
		return PEACE;
}
