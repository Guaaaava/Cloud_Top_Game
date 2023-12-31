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
	/* �̵��ʼ�� */
	_shop = Shop::create();
	CC_SAFE_RETAIN(_shop);	// �������

	/* ���̳�ʼ�� */
	_chessBoard = ChessBoard::create();
	CC_SAFE_RETAIN(_chessBoard);

	/* �����Ļ */
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* վ�����ĳ�ʼ�� */
	auto width = visibleSize.width * 0.6;							//ÿ��վ�����Ŀ��
	auto height = visibleSize.height * 0.4 / 6;						//ÿ��վ�����ĸ߶�
	_standSize = Size(width, height);								//ÿ��վ�����Ĵ�С
	
	_standPos[0] = origin + visibleSize / 2 - Vec2(width / 2, height * 4 - 10);//ÿ��վ���������½�
	
	for (int i = 1; i < 8; i++) {
		if (i == 1 || i == 7) {
			_standPos[i] = _standPos[i - 1] + Vec2(0, height + 30);
		}
		else {
			_standPos[i] = _standPos[i - 1] + Vec2(0, height);
		}
	}

	/* ����վ������ */
	createStandOrigin();

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
}

/*************
* ��������: 
* ��������: ��������
*	����ֵ: ��
* ************/
void GameController::createStandOrigin()
{
	std::string pic_pth = "standOrigin.png";	//վ������ͼƬ
	auto sigWidth = _standSize.width / BDSZ_X;	//������Ŀ��
	auto sigHeight = _standSize.height;			//������ĸ߶�
	Size sigSize(sigWidth, sigHeight);			//������Ĵ�С

	/* ��������� */
	for (int i = 0; i < BDSZ_Y+2; i++) {
		for (int j = 0; j < BDSZ_X; j++) {
			auto sprite = Sprite::create(pic_pth);	//����ͼƬ
			Vec2 pos = getStandPos(j, i);			//���λ��

			if (sprite == nullptr) {
				CCLOG("���򴴽�ʧ��!");
			}
			else {
				sprite->setContentSize(sigSize);			//���ô�С
				sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//����ê��
				sprite->setPosition(pos);					//����λ��
				sprite->setVisible(false);					//��Ϊ���ɼ�
				CTGScene::getLayer()->addChild(sprite, 3);	//�������
				_standOrigin[i][j] = sprite;
			}
		}
	}
	

	return;
}

/*************
* ��������: ����λ��
* ��������: ͨ������λ�û����ʵλ��
*	����ֵ: ��ʵλ��
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
* ��������: ��ʵλ��
* ��������: ͨ����ʵλ�û�õ���λ��
*	����ֵ: ����λ��
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
* ��������: ʵ��λ��
* ��������: �жϵ��Ƿ��ڱ�սϯ����
*	����ֵ: true:�ڱ�սϯ����;
*			false:���ڱ�սϯ
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
* ��������: Command pos:Ҫ�жϵĵ�
* ��������: �ж�һ���Ƿ����ҷ�������
*	����ֵ: true:���ҷ�����;
*			false:�����ҷ�����
* ************/
inline bool GameController::isInMyBound(struct POS pos)
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
inline bool GameController::hasHero(struct POS pos)
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
inline bool GameController::placeHero(Hero* hero, struct POS pos)
{
	/* ���Ӽ����������� */
	auto board = _chessBoard->getBoard();
	(*board)[pos._x][pos._y] = hero;

	/* ���Ӽ�����ʵ���� */
	//hero->setPosition(getTruePos(pos._type, pos._x, pos._y));

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

	auto newHero = Annie::create();		// ����Ӣ��

	// Ӣ������
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	auto pos = _standOrigin[0][0]->getPosition();
	newHero->setPosition(pos);

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
