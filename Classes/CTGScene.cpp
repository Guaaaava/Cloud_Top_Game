#include "CTGScene.h"
#include "ConfigController.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CTGScene::CTGScene()
	: touchingSprite(nullptr)
{

}

CTGScene::~CTGScene()
{

}

bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	/* Ô¤¼ÓÔØÒôÀÖ */
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("mainScene/undertale.mp3");

	/* ±³¾°ÒôÀÖ */
	audio->playBackgroundMusic("mainScene/undertale.mp3", true);

	// »ñÈ¡ÆÁÄ»ÖÐÐÄµã
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ±³¾°²ã
	layer = LayerColor::create(Color4B::WHITE);
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// ¶ÔÕ½³¡¾°£¨¾«Áé£©
	auto spriteChessBoard = Sprite::create("ChessBoardScene.png");
	spriteChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(spriteChessBoard, 1);

	// ÉÌµê¡¢ÆåÅÌ£¿
	Shop* shop = GameController::getInstance()->getShop();
	ChessBoard* chessBoard = GameController::getInstance()->getChessBoard();

	// ´´½¨´¥ÃþÊÂ¼þ¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CTGScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	Point touchPoint = touch->getLocation();
	touchingSprite = judgePointInSprite(touchPoint);
	return touchingSprite != nullptr;
}

void CTGScene::onTouchMoved(Touch* touch, Event* event)
{
	if (touchingSprite != nullptr) {
		touchingSprite->setPosition(touchingSprite->getPosition() + touch->getDelta());

		auto touchPoint = touch->getLocation();
		auto spriteSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();
		auto rectSellOrigin = spriteSellOrigin->getBoundingBox();
		spriteSellOrigin->setOpacity(rectSellOrigin.containsPoint(touchPoint) ? 255 : 80);
	}
}

void CTGScene::onTouchEnded(Touch* touch, Event* event)
{
	if (touchingSprite != nullptr) {
		auto touchEndedPoint = touch->getLocation();
		auto spriteSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();
		auto rectSellOrigin = spriteSellOrigin->getBoundingBox();

		if (rectSellOrigin.containsPoint(touchEndedPoint)) {
			GameController::getInstance()->sellHero(touchingSprite);
		}

		touchingSprite = nullptr;
	}
}

Hero* CTGScene::judgePointInSprite(Point pnt)
{
	auto myHeroes = GameController::getInstance()->getChessBoard()->getMyHeroes();
	if (myHeroes == nullptr)
	{
		return nullptr;
	}

	for (auto hero : *myHeroes)
	{
		auto rectOfSprite = hero->getBoundingBox();
		if (rectOfSprite.containsPoint(pnt))
		{
			return hero;
		}
	}

	return nullptr;
}