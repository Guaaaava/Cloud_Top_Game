#include "CTGScene.h"
#include "ConfigController.h"
#include "GameController.h"

/****************************************************
 * 功能：初始化界面
 * 作者：黄辰宇
 * 时间：2023年12月7日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
LayerColor* CTGScene::layer = nullptr;			// 为静态成员分配空间（重要！！）
bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	// 获取屏幕中心点
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景层
	layer = LayerColor::create(Color4B::WHITE);	// 背景层颜色为白色
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// 对战场景（精灵）
	auto spriteChessBoard = Sprite::create("ChessBoardScene.png");
	spriteChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(spriteChessBoard, 1);			// 对战场景 z 值为 1

	// 商店？
	Shop* shop = GameController::getInstance()->getShop();

	// // 测试
	// test = Sprite::create("NormalRefreshShopButton.png");
	// test->setPosition(origin + visibleSize / 2);
	// layer->addChild(test, 2);

	// 创建触摸事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	// 设置事件吞没
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CTGScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	touchingSprite = nullptr;

	return true;
}

/****************************************************
 * 功能：按下鼠标的回调函数
 * 返回值：若点击坐标在英雄区域内，返回true
 * 作者：黄辰宇
 * 时间：2023年12月27日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	// 点击位置
	Point touchPoint = touch->getLocation();

	// 获取被选中的精灵
	touchingSprite = judgePointInSprite(touchPoint);

	if (touchingSprite != nullptr)	// 在精灵区域内则返回true
	{
		return true;
	}
	return false;
}

/****************************************************
 * 功能：松开鼠标的回调函数，英雄跟着鼠标移动
 * 作者：黄辰宇
 * 时间：2023年12月27日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::onTouchMoved(Touch* touch, Event* event)
{
	touchingSprite->setPosition(touchingSprite->getPosition() + touch->getDelta());
}

/****************************************************
 * 功能：松开鼠标的回调函数
 * 说明：若在出售区域内松开，则出售这个英雄
 * 作者：黄辰宇
 * 时间：2023年12月27日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::onTouchEnded(Touch* touch, Event* event)
{
	auto touchEndedPoint = touch->getLocation();
	auto rectSellOrigin = GameController::getInstance()->getShop()->getSellOrigin();

	if (rectSellOrigin.containsPoint(touchEndedPoint))
	{
		// 卖出英雄


		// 维护商店、棋盘等集合
	}
}

/****************************************************
 * 功能：判断触摸点是否在已有精灵区域内，
 * 返回值：是则返回该精灵，否则返回nullptr
 * 作者：黄辰宇
 * 时间：2023年12月27日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
Sprite* CTGScene::judgePointInSprite(Point pnt)
{
	auto sprites = GameController::getInstance()->getChessBoard()->getMyHeroes();
	if (sprites == nullptr)
	{
		return nullptr;
	}

	for (int idx = 0; idx < sprites->size(); idx++)
	{
		auto rectOfSprite = sprites->at(idx)->getBoundingBox();
		if (rectOfSprite.containsPoint(pnt))
		{
			return sprites->at(idx);
		}
	}

	return nullptr;
}
