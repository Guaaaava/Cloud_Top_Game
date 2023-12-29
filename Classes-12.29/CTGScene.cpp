#include "CTGScene.h"
#include "ConfigController.h"
#include "GameController.h"
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

	// ����������ʽ�仯
	auto touchPoint = touch->getLocation();
	auto spriteSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();
	auto rectSellOrigin = spriteSellOrigin->getBoundingBox();
	if (rectSellOrigin.containsPoint(touchPoint))
	{
		spriteSellOrigin->setOpacity(255);
	}
	else
	{
		spriteSellOrigin->setOpacity(80);
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
	auto touchEndedPoint = touch->getLocation();
	auto spriteSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();
	auto rectSellOrigin = spriteSellOrigin->getBoundingBox();

	if (rectSellOrigin.containsPoint(touchEndedPoint))
	{
		// ����Ӣ�ۡ�ά���̵ꡢ���̵ȼ��ϣ����ӽ�ң����±�ǩ�����°�ť״̬
		GameController::getInstance()->sellHero(touchingSprite);
		touchingSprite = nullptr;	// �޸�
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
