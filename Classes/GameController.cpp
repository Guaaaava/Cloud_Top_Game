#include "GameController.h"
#include "CTGScene.h"

/****************************************************
 * ���ܣ���Ϸ�߼�������Ĭ�Ϻ���
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
GameController* GameController::instance = nullptr;		// ����̬��Ա����ռ�
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
	// ��ʼ��
	shop = Shop::create();
	CC_SAFE_RETAIN(shop);	// �������

	chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(chessBoard);

	enemyMoney = 0;
	enemyExp = 0;
	enemyLevel = 0;
}
GameController::~GameController()
{
	// �����̵����
	CC_SAFE_DELETE(shop);

	// �������̶���
	CC_SAFE_DELETE(chessBoard);

	GameController::destroyInstance();
}

/****************************************************
 * ���ܣ��������ϴ���Ӣ�ۣ�z ֵΪ 3
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::createHeroInChessBoard(int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d�����������%d��Ӣ�۴���ʧ�ܣ�\n", idxOfHero, NUM_CHESS);
		return;
	}

	std::string heroPicPath = ConfigController::getInstance()->getPathByID(PATH_NORMAL[idxOfHero]);
	auto newHero = Sprite::create(heroPicPath);		// ����Ӣ��

	// Ӣ������
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	newHero->setPosition(500, 600);

	// ά�����̳�Ա���ϡ����map
	chessBoard->getMyHeroes()->push_back(newHero);
	chessBoard->getMyHeroesIdxMap()->insert({ newHero, idxOfHero });
}

/****************************************************
 * ���ܣ�����Ӣ�ۣ���ӽ�ң����±�ǩ�����°�ť״̬
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::sellHero(Sprite* soldHero)
{
	auto myHeroes = chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("��������Ӣ�ۣ�Ӣ�۳���ʧ�ܣ�\n");
		return;
	}

	int idxOfHero = chessBoard->findHero(soldHero);
	if (idxOfHero == -1)
	{
		CCLOG("�����ڱ��Ϊ%d��Ӣ�ۣ�����ʧ�ܣ�\n", idxOfHero);
		return;
	}

	myHeroes->remove(soldHero);	// �����̶�����ҷ����Ӽ�����ɾ����Ӣ��
	soldHero->removeFromParentAndCleanup(true);	// �ӽ������Ƴ��þ���
	// �����ҷ����
	shop->addMoney(shop->getHeroPrice(idxOfHero));
	// ���±�ǩ
	shop->updateLevelLabel();
	shop->updateMoneyLabel();
	// ���°�ť״̬
	shop->updateButtonState();
}

