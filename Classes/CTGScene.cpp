#include "CTGScene.h"
<<<<<<< Updated upstream
=======
#include "ConfigController.h"
#include "ShopController.h"
>>>>>>> Stashed changes

bool CTGScene::init()
{
	if (!Scene::init())
		return false;

<<<<<<< Updated upstream
	// 金铲铲之战名称标签
=======
	// 获取屏幕中心点
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建背景层
	layer = LayerColor::create(Color4B::WHITE);	// 背景层颜色为白色
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// 对战场景（精灵）
	auto sceneChessBoard = Sprite::create("ChessBoardScene.png");
	sceneChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(sceneChessBoard, 1);			// 对战场景 z 值为 1

	// 创建单点事件监听器（已禁用）
/*
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);		// 设置事件吞没
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);		// 设置按下按钮的回调
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);		// 设置释放按钮的回调
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
*/
>>>>>>> Stashed changes

	// 升级按钮
	std::string normalPicPath = "NormalLevelUpBotton.png";		// 未被选中时按钮样式
	std::string selectedPicPath = "SelectedLevelUpBotton.png";	// 被选中时按钮样式
	auto buttonLevelUp = Button::create(normalPicPath, selectedPicPath);// 创建按钮
	std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);	// 获取中文“升级”
	buttonLevelUp->setTitleText(words);						// 设置按钮文字
	buttonLevelUp->setTitleFontName("fonts/simkai.ttf");	// 设置字体
	buttonLevelUp->setTitleFontSize(24.0f);					// 设置字号
	buttonLevelUp->setTitleColor(Color3B::BLACK);			// 设置颜色
	buttonLevelUp->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f));	// 设置位置
	layer->addChild(buttonLevelUp, 2);						// 按钮 z 值为 2

<<<<<<< Updated upstream
	// 对战场景（精灵）

	// 开始游戏按钮

	// 打开商店按钮

	// 退出游戏按钮

	// 金铲铲之战LOGO

=======
	// 经验值标签

	// 刷新商店按钮
	normalPicPath = "NormalRefreshShopBotton.png";		// 未被选中时按钮样式
	selectedPicPath = "SelectedRefreshShopBotton.png";	// 被选中时按钮样式
	auto buttonRefreshShop = Button::create(normalPicPath, selectedPicPath);
	words = ConfigController::getInstance()->getCNByID(WORDS_REFRESH);	// 获取中文“刷新”
	buttonRefreshShop->setTitleText(words);						// 设置按钮文字
	buttonRefreshShop->setTitleFontName("fonts/simkai.ttf");	// 设置字体
	buttonRefreshShop->setTitleFontSize(24.0f);					// 设置字号
	buttonRefreshShop->setTitleColor(Color3B::BLACK);			// 设置颜色
	buttonRefreshShop->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.25f));	// 设置位置
	layer->addChild(buttonRefreshShop, 2);						// 按钮 z 值为 2
	
	// 剩余金币标签

	// 创建商店（由五个卡牌组成）
	normalPicPath = static_cast<std::string>("chessButton/0.png");		// 未被选中时按钮样式
	selectedPicPath = static_cast<std::string>("chessButton/0.png");	// 被选中时按钮样式
	for (int num = 1; num <= 5; num++)
	{
		const int normalPathLength = normalPicPath.size();
		const int selectedPathLength = selectedPicPath.size();
		normalPicPath[12]++;
		selectedPicPath[12]++;

		auto chessPosition = ShopController::getChessPosition(num);
		auto buttonChess = ShopController::createChessButton(normalPicPath, selectedPicPath, chessPosition);
		layer->addChild(buttonChess, 2);	// 按钮 z 值为 2
	}
	
	
>>>>>>> Stashed changes

	return true;
}
