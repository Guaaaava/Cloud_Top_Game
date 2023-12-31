#include "GameController.h"
#include "CTGScene.h"
/**************
* ����:��Ϸ�߼�������
* ����:�����
* ʱ��:2023��12��28��
**************/

GameController* GameController::_instance = nullptr;

/*************
* ��������: ��
* ��������: ���캯��
*	����ֵ: ��
* ************/
GameController::GameController()
{
	// ��ʼ�����������
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);

	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

	_myLittleHero = LittleHero::create();
	CC_SAFE_RETAIN(_myLittleHero);

	_enemyLittleHero = LittleHero::create();
	CC_SAFE_RETAIN(_enemyLittleHero);

	// ССӢ�۶���
	_myLittleHero->heroRunToPos(Vec2(150, 300));
	CTGScene::getLayer()->addChild(_myLittleHero, 3);
	_enemyLittleHero->heroRunToPos(Vec2(950, 750));
	CTGScene::getLayer()->addChild(_enemyLittleHero, 3);

	roundCounter = 1;
	heroTagCounter = 1;

	timeLeft = 0;

	enemyMoney = 0;	//�з����
	enemyExp = 0;	//�з�����
	enemyLevel = 0;	//�з��ȼ�
}

/*************
* ��������: ��
* ��������: ��������
*	����ֵ: ��
* ************/
GameController::~GameController()
{
	// ���ٴ���ʱRetain��Hero
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

	// �����̵����
	CC_SAFE_DELETE(_shop);

	// �������̶���
	CC_SAFE_DELETE(_chessBoard);

	// ����ССӢ�۶���
	CC_SAFE_DELETE(_myLittleHero);
	CC_SAFE_DELETE(_enemyLittleHero);

	GameController::destroyInstance();
}

/*************
* ��������: ��
* ��������: ��ȡʵ��
*	����ֵ: ʵ��
* ************/
GameController* GameController::getInstance()
{
	if (_instance == nullptr) {
		_instance = new GameController();
	}

	return _instance;
}

/*************
* ��������: ��
* ��������: ����ʵ��
*	����ֵ: ʵ��
* ************/
void GameController::destroyInstance()
{
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}
}

/*************
* ��������: Command pos:Ҫ�жϵĵ�
* ��������: �ж�һ���Ƿ����ҷ�������
*	����ֵ: true:���ҷ�����;
*			false:�����ҷ�����
* ************/
inline bool GameController::isInMyBound(Command pos)
{
	if ((pos._x >= 0) && (pos._x < BDSZ_X / 2) && (pos._y >= 0) && (pos._y < BDSZ_Y / 2)) {
		return true;
	}

	return false;
}

/*************
* ��������: Command& pos:Ҫ�жϵ�����
* ��������: �жϸõ��Ƿ�������
*	����ֵ: true:�õ�������;
*			false:�õ�û������
* ************/
inline bool GameController::hasHero(Command pos)
{
	/* �õ㲻���ҷ������ڻ��߸õ���Ӣ�۾���Ϊ�õ������� */
	auto board = _chessBoard->getBoard();
	if (!isInMyBound(pos) || (*board)[pos._x][pos._y].hero != nullptr) {
		return true;
	}

	return false;
}

/*************
* ��������: Command pos:Ҫ���õ�λ��
*			Hero* hero:Ҫ���õ�����
* ��������: ��ĳ���������
*	����ֵ: ��
* ************/
inline bool GameController::placeHero(Hero* hero, Command pos)
{
	auto board = _chessBoard->getBoard();
	(*board)[pos._x][pos._y].hero = hero;
	return false;
}

/*************
* ��������: ��
* ��������: �ж���Ϸ�Ƿ����
*	����ֵ: DRAW:ƽ��
*			M_WIN:�ҷ�ʤ��
*			E_WIN:�з�ʤ��
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
 * ���ܣ��������ϴ���Ӣ�ۣ�z ֵΪ 3
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::createHeroInChessBoard(const int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d�����������%d��Ӣ�۴���ʧ�ܣ�\n", idxOfHero, NUM_CHESS);
		return;
	}

	// ������ֹ����
	std::string picPath = ConfigController::getInstance()->getPathByID(PATH_SILENT_SPRITE[idxOfHero]);
	auto newSilentSprite = Sprite::create(picPath);

	// ���ϡ�ά��Ӣ��list
	HeroMsg newHeroMsg;
	newHeroMsg.init(nullptr, newSilentSprite, heroTagCounter, idxOfHero, 1);
	heroTagCounter++;	// ������++
	_chessBoard->getMyHeroes()->push_front(newHeroMsg);
	
	// ��ֹ�������ԣ�λ�ô����̻�ȡ��
	auto relaxPos = Vec2(80 * idxOfHero, 300);
	newSilentSprite->setPosition(relaxPos);
	CTGScene::getLayer()->addChild(newSilentSprite, 3);

	// �ϳɾ��飨���Σ��������ǵ������
	mergeHero();
	mergeHero();
}

/****************************************************
 * ���ܣ����ݱ�Ŵ���Ӣ��
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��30��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
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
 * ���ܣ�����Ӣ�ۣ����ӽ�ң����±�ǩ�����°�ť״̬
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::sellHero(HeroMsg soldHero)
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("��������Ӣ�ۣ�Ӣ�۳���ʧ�ܣ�\n");
		return;
	}

	// �ҷ�Ӣ�ۼ�����ɾ����Ӣ��
	myHeroes->remove(soldHero);

	// �ӽ������Ƴ��þ�ֹ����
	soldHero.silentSprite->removeFromParentAndCleanup(true);
	// �����ҷ����
	_shop->addMoney(_shop->getHeroPrice(soldHero.heroIdx));
	// ���±�ǩ
	_shop->updateLevelLabel();
	_shop->updateMoneyLabel();
	// ���°�ť״̬
	_shop->updateButtonState();
}

/****************************************************
 * ���ܣ���������ʱ
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��30��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::createCountDown()
{
	// ��������ʱ��ǩ��ʾ����ʱ
	labelTimeCountDown = Label::createWithTTF("5", "fonts/simkai.ttf", 64);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	labelTimeCountDown->setPosition(Vec2(visibleSize.width * 0.075f, visibleSize.height * 0.925f));
	labelTimeCountDown->setTextColor(Color4B::ORANGE);
	CTGScene::getLayer()->addChild(labelTimeCountDown, 3);

	// ������ʱ����ÿ����µ���ʱ
	timeLeft = 5;
	auto myScheduler = Director::getInstance()->getScheduler();
	myScheduler->schedule(
		CC_CALLBACK_1(GameController::updateCountDown, this), this, 1.0f ,false, "timer"
	);
}

/****************************************************
 * ���ܣ���������ʱ
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��30��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::updateCountDown(float dt)
{
	timeLeft--;
	labelTimeCountDown->setString(std::to_string(timeLeft));

	// ��Ϸ����������
	if (_myLittleHero->isDead())
	{
		// ��ʾʧ��
		auto label = Label::createWithTTF("YOU LOSE!", "fonts/simkai.ttf", 256);
		label->setPosition(Director::getInstance()->getVisibleSize() / 2);
		label->setTextColor(Color4B::WHITE);
		CTGScene::getLayer()->addChild(label, 4);

		auto myScheduler = Director::getInstance()->getScheduler();
		myScheduler->unschedule("timer", this);		// ֹͣ����ʱ
	}
	else if (_enemyLittleHero->isDead())
	{
		// ��ʾʤ��
		auto label = Label::createWithTTF("YOU WIN!", "fonts/simkai.ttf", 256);
		label->setPosition(Director::getInstance()->getVisibleSize() / 2);
		label->setTextColor(Color4B::WHITE);
		CTGScene::getLayer()->addChild(label, 4);

		auto myScheduler = Director::getInstance()->getScheduler();
		myScheduler->unschedule("timer", this);		// ֹͣ����ʱ
	}

	if (timeLeft == 0)
	{
		if (roundCounter % 2 == 0)
		{
			switch (stopFight())	// �����ûغ϶�ս������˭Ӯ��
			{
			case ME:
				_enemyLittleHero->getHurted();
				break;
			case ENEMY:
				_myLittleHero->getHurted();
				break;
			case PEACE:
				_enemyLittleHero->getHurted();
				_myLittleHero->getHurted();
				break;
			default:
				break;
			}

			timeLeft = 5;
			roundCounter++;
		}
		else
		{
			startFight();	// ����ʱ�����Ϳ�ʼ�ûغ϶�ս
			timeLeft = 15;
			roundCounter++;
		}
	}
}

/****************************************************
 * ���ܣ��ϳ�Ӣ��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��31��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
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
						// erase�����ʧ��
						(it1->level)++;
						it1->silentSprite->setScale(it1->level);
						return;	// ��������merge
					}
				}
			}
		}
	}
}

/****************************************************
 * ���ܣ���ȡ����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��30��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::getEnemy()
{
	auto enemyHeroes = _chessBoard->getEnemyHeroes();
	for (int i = 1; i <= 3; i++)
	{
		// ����Ӣ��
		// auto eHero = createHero(i);
		// eHero->changeMsg(ENEMY);

		std::string picPath = ConfigController::getInstance()->getPathByID(PATH_SILENT_SPRITE[i]);
		auto eSprite = Sprite::create(picPath);

		HeroMsg enemyHero;
		enemyHero.init(nullptr, eSprite, i, i, 1);

		enemyHeroes->push_front(enemyHero);

		// ��ֹ�������ԣ�λ�ô����̻�ȡ��
		auto relaxPos = Vec2(80 * i, 600);
		eSprite->setPosition(relaxPos);
		CTGScene::getLayer()->addChild(eSprite, 3);
	}
}

/****************************************************
 * ���ܣ���Ϸ��ʼ
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��30��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::gameStart()
{
	getEnemy();
	createCountDown();
}

/****************************************************
 * ���ܣ���ʼ��ս
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��31��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::startFight()
{
	// ��ȡ�ҷ���Ϣ
	auto myHeroes = _chessBoard->getMyHeroes();
	
	// ��ȡ�Է���Ϣ
	auto enemyHeroes = _chessBoard->getEnemyHeroes();

	// ���ϵص�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 myGatherPos = Vec2(visibleSize.width / 2 + 40, visibleSize.height / 2);
	Vec2 enemyGatherPos = Vec2(visibleSize.width / 2 - 40, visibleSize.height / 2);

	// ��������Ӣ�ۣ���ȡ�������󣬸��¶�����ʼλ�ã����ؾ�ֹ����
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

		// ��ʼ����
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

		// ��ʼ����
		Vec2 startPos = spriteNow->getPosition();
		heroNow->initPos(startPos);
		heroNow->getEnemyInfor(*myHeroes);
		heroNow->heroRunToEnemyPos(enemyGatherPos);
		CTGScene::getLayer()->addChild(heroNow, 3);

		spriteNow->setVisible(false);
	}
}

/****************************************************
 * ���ܣ�������ս
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��31��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
int GameController::stopFight()
{
	int myHp = 0;
	int enemyHp = 0;

	// ��ȡ�ҷ���Ϣ
	auto myHeroes = _chessBoard->getMyHeroes();

	// ��ȡ�Է���Ϣ
	auto enemyHeroes = _chessBoard->getEnemyHeroes();

	// ��������Ӣ�ۣ��Ƴ�����
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