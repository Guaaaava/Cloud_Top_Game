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

	// ��Ϸ��ʼ
	GameController::getInstance()->gameStart();

	// ���������¼�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	// �����¼���û
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CTGScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	touchingHero.init(nullptr, nullptr, -1, -1, -1);

	return true;
}

/****************************************************
 * ���ܣ��������Ļص�����
 * ����ֵ�������������Ӣ�������ڣ�����true
 * ע�⣺��ʼ��ս���ܱ�ѡ�У�����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	// ���λ��
	Point touchPoint = touch->getLocation();

	// ��ȡ��ѡ�е�Ӣ�ۡ�����
	touchingHero = judgePointInSprite(touchPoint);

	if (touchingHero.silentSprite != nullptr)	// �ھ����������򷵻�true
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
	auto touchingSprite = touchingHero.silentSprite;
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
		// ����Ӣ�ۡ�ά���̵ꡢ���̵ȼ��ϣ���ӽ�ң����±�ǩ�����°�ť״̬
		GameController::getInstance()->sellHero(touchingHero);
		touchingHero.init(nullptr, nullptr, -1, -1, -1);	// �޸�
	}
}

/****************************************************
 * ���ܣ��жϴ������Ƿ�������Ӣ�������ڣ�
 * ����ֵ�����򷵻ظ�Ӣ�ۣ����򷵻�nullptr
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��27��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
HeroMsg CTGScene::judgePointInSprite(Point pnt)
{
	HeroMsg res;
	res.init(nullptr, nullptr, -1, -1, -1);

	auto myHeroes = GameController::getInstance()->getChessBoard()->getMyHeroes();
	if (myHeroes == nullptr)
	{
		return res;
	}

	std::list<HeroMsg>::iterator it;
	for (it = myHeroes->begin(); it != myHeroes->end(); it++)
	{
		auto rectOfSprite = it->silentSprite->getBoundingBox();
		if (rectOfSprite.containsPoint(pnt))
		{
			return (*it);
		}
	}

	return res;
}
