#include "CTGScene.h"
#include "ConfigController.h"
#include "SimpleAudioEngine.h"

/****************************************************
 * ���ܣ���ʼ������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��7��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
LayerColor* CTGScene::layer = nullptr;			// Ϊ��̬��Ա����ռ䣨��Ҫ������
bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	/* Ԥ�������� */
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("mainScene/undertale.mp3");

	/* �������� */
	audio->playBackgroundMusic("mainScene/undertale.mp3", true);

	// ��ȡ��Ļ���ĵ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ������
	layer = LayerColor::create(Color4B::WHITE);	// ��������ɫΪ��ɫ
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// ��ս���������飩
	auto spriteChessBoard = Sprite::create("ChessBoardScene.png");
	spriteChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(spriteChessBoard, 1);			// ��ս���� z ֵΪ 1

	// �̵ꡢ���̣�
	Shop* shop = GameController::getInstance()->getShop();
	ChessBoard* chessBoard = GameController::getInstance()->getChessBoard();

	// ���������¼�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	// �����¼���û
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CTGScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	touchingSprite = nullptr;

	return true;
}

/****************************************************
 * ���ܣ��������Ļص�����
 * ����ֵ�������������Ӣ�������ڣ�����true
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	// ���λ��
	Point touchPoint = touch->getLocation();

	// ��ȡ��ѡ�еľ���
	touchingSprite = judgePointInSprite(touchPoint);

	//��ȡ��ʼλ��
	firstPos = touchingSprite->getPosition();

	if (touchingSprite != nullptr)	// �ھ����������򷵻�true
	{
		return true;
	}
	return false;
}

/****************************************************
 * ���ܣ��ɿ����Ļص�������Ӣ�۸�������ƶ�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::onTouchMoved(Touch* touch, Event* event)
{
	touchingSprite->setPosition(touchingSprite->getPosition() + touch->getDelta());

	auto controller = GameController::getInstance();

	auto touchPoint = touch->getLocation();							//��ȡ�����
	auto loc = controller->getSizePos(touchPoint);					//��ȡ��������

	auto spriteSellOrigin = controller->getShop()->getSellOrigin();	//��ȡ��������
	auto rectSellOrigin = spriteSellOrigin->getBoundingBox();		//��ȡ����������ײ��

	if (rectSellOrigin.containsPoint(touchPoint))
	{
		spriteSellOrigin->setOpacity(255);
	}// ����������ʽ�仯
	else {
		spriteSellOrigin->setOpacity(80);
	}

	if(loc._type==STAND){
		controller->_standOrigin[loc._y][loc._x]->setVisible(true);//����λ����Ϊ�ɼ�
		for (int i = 0; i < BDSZ_Y + 2; i++) {
			for (int j = 0; j < BDSZ_X; j++) {
				if (i != loc._y || j != loc._x)
					controller->_standOrigin[i][j]->setVisible(false);
			}
		}//��սϯ������Ϊ���ɼ�
	}//��սϯ
	else {
		for (int i = 0; i < BDSZ_Y + 2; i++) {
			for (int j = 0; j < BDSZ_X; j++) {
				controller->_standOrigin[i][j]->setVisible(false);
			}
		}//��սϯ������Ϊ���ɼ�
	}
}

/****************************************************
 * ���ܣ��ɿ����Ļص�����
 * ˵�������ڳ����������ɿ�����������Ӣ��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::onTouchEnded(Touch* touch, Event* event)
{
	auto controller = GameController::getInstance();

	auto touchEndedPoint = touch->getLocation();
	auto spriteSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();
	auto rectSellOrigin = spriteSellOrigin->getBoundingBox();

	auto loc = controller->getSizePos(touchEndedPoint);

	if (rectSellOrigin.containsPoint(touchEndedPoint))
	{
		// ����Ӣ�ۡ�ά���̵ꡢ���̵ȼ��ϣ���ӽ�ң����±�ǩ�����°�ť״̬
		GameController::getInstance()->sellHero(touchingSprite);
		touchingSprite = nullptr;	// �޸�
	}

	if (loc._type == STAND) {
		Vec2 pos = controller->_standOrigin[loc._y][loc._x]->getPosition();
		touchingSprite->setPosition(pos);
		controller->_standOrigin[loc._y][loc._x]->setVisible(false);//����λ����Ϊ���ɼ�
	}
	else {
		touchingSprite->setPosition(firstPos);
	}
}

/****************************************************
 * ���ܣ��жϴ������Ƿ������о��������ڣ�
 * ����ֵ�����򷵻ظþ��飬���򷵻�nullptr
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
Hero* CTGScene::judgePointInSprite(Point pnt)
{
	auto myHeroes = GameController::getInstance()->getChessBoard()->getMyHeroes();
	if (myHeroes == nullptr)
	{
		return nullptr;
	}

	std::list<Hero*>::iterator it;
	for (it = myHeroes->begin(); it != myHeroes->end(); it++)
	{
		auto rectOfSprite = (*it)->getBoundingBox();
		if (rectOfSprite.containsPoint(pnt))
		{
			return (*it);
		}
	}

	return nullptr;
}
