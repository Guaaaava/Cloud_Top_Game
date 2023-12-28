#include "GameController.h"
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
	// ��ʼ��
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);	// �������

	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

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
	// �����̵����
	CC_SAFE_DELETE(_shop);

	// �������̶���
	CC_SAFE_DELETE(_chessBoard);

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

	return;
}

/*************
* ��������: Command pos:Ҫ�жϵĵ�
* ��������: �ж�һ���Ƿ����ҷ�������
*	����ֵ: true:���ҷ�����;
*			false:�����ҷ�����
* ************/
inline bool GameController::isInMyBound(Command pos)
{
	if ((pos._x >= 0) && (pos._x < BDSZ_X/2) && (pos._y >= 0) && (pos._y < BDSZ_Y / 2)) {
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
	if (!isInMyBound(pos) || (*board)[pos._x][pos._y] != nullptr) {
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
	(*board)[pos._x][pos._y] = hero;
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
void GameController::createHeroInChessBoard(int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d�����������%d��Ӣ�۴���ʧ�ܣ�\n", idxOfHero, NUM_CHESS);
		return;
	}

	auto newHero = Samurai::create();		// ����Ӣ��

	// Ӣ������
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	newHero->setPosition(500, 600);

	// ά�����̳�Ա���ϡ����map
	_chessBoard->getMyHeroes()->push_back(newHero);
	_chessBoard->getMyHeroesIdxMap()->insert({ newHero, idxOfHero });
}

/****************************************************
 * ���ܣ�����Ӣ�ۣ���ӽ�ң����±�ǩ�����°�ť״̬
 * ������Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void GameController::sellHero(Hero* soldHero)
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("��������Ӣ�ۣ�Ӣ�۳���ʧ�ܣ�\n");
		return;
	}

	int idxOfHero = _chessBoard->findHero(soldHero);
	if (idxOfHero == -1)
	{
		CCLOG("�����ڱ��Ϊ%d��Ӣ�ۣ�����ʧ�ܣ�\n", idxOfHero);
		return;
	}

	myHeroes->remove(soldHero);	// �����̶�����ҷ����Ӽ�����ɾ����Ӣ��
	soldHero->removeFromParentAndCleanup(true);	// �ӽ������Ƴ��þ���
	// �����ҷ����
	_shop->addMoney(_shop->getHeroPrice(idxOfHero));
	// ���±�ǩ
	_shop->updateLevelLabel();
	_shop->updateMoneyLabel();
	// ���°�ť״̬
	_shop->updateButtonState();
}
