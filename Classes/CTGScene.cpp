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
	auto sceneChessBoard = Sprite::create("ChessBoardScene.png");
	sceneChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(sceneChessBoard, 1);			// 对战场景 z 值为 1

	Shop* shop = GameController::getInstance()->getShop();

	return true;
}
