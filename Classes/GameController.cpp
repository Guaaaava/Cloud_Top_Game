#include "GameController.h"

/****************************************************
 * ���ܣ���Ϸ������Ĭ�Ϻ���
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

	myMoney = shop->getMoney();
	myExp = shop->getExp();
	myLevel = shop->getLevel();

	enemyMoney = 0;
	enemyExp = 0;
	enemyLevel = 0;
}
GameController::~GameController()
{
	// �����̵����
	CC_SAFE_DELETE(shop);

	GameController::destroyInstance();
}

