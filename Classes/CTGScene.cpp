#include "CTGScene.h"
#include "ConfigController.h"

/****************************************************
 * 功能：初始化界面
 * 作者：黄辰宇
 * 时间：2023年12月7日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	// 创建单点事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);		// 设置事件吞没
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);		// 设置按下按钮的回调
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);		// 设置释放按钮的回调
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 获取屏幕中心点
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 设置背景颜色（当前为白色）
	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// 对战场景（精灵）
	auto boardNode = Sprite::create("BoardScene.png");
	boardNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(boardNode, 1);			// 对战场景 z 值为 1
	prt_backGround = boardNode;

	// 棋盘左侧中心，右侧中心
	Vec2 leftOrigin = origin + Vec2(visibleSize.width * 0.05f, visibleSize.height / 2);
	Vec2 rightOrigin = origin + Vec2(visibleSize.width * 0.95f, visibleSize.height / 2);

	// 静音按钮

	// 开始游戏按钮
	std::string words = ConfigController::getInstance()->getCNByID(WORDS_START);
	auto startItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuStartCallback, this));
	float x = leftOrigin.x;
	float y = leftOrigin.y + visibleSize.height * 0.4f;
	startItem->setPosition(Vec2(x, y));			// 在界面左上角

	// 打开商店按钮
	words = ConfigController::getInstance()->getCNByID(WORDS_SHOP);
	auto openShopItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuOpenShopCallback, this));
	x = rightOrigin.x;
	y = rightOrigin.y - visibleSize.height * 0.4f;
	openShopItem->setPosition(Vec2(x, y));		// 在界面右下角

	// 退出游戏按钮
	words = ConfigController::getInstance()->getCNByID(WORDS_EXIT);
	auto exitGameItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuExitGameCallback, this));
	x = leftOrigin.x + exitGameItem->getContentSize().width * 1.5f;
	y = leftOrigin.y + visibleSize.height * 0.4f;
	exitGameItem->setPosition(Vec2(x, y));		// 在界面左上角“开始”按钮右边

	// 创建界面菜单（精灵）
	auto menu = Menu::create(startItem, openShopItem, exitGameItem, nullptr);
	menu->setPosition(origin);
	layer->addChild(menu, 3);			// 界面菜单 z 值为 3

	// 商店按钮大小
	float padding = 100;				// 按钮图片长100像素，宽100像素
	Size shopButtonSize = Size(padding, padding);
	Vec2 _origin = Vec2(rightOrigin.x, rightOrigin.y - visibleSize.height * 0.4f);
	prt_shopButtonSize = Rect(_origin, shopButtonSize);

	return true;
}

/****************************************************
 * 功能：创建通用按钮
 * 作者：黄辰宇
 * 时间：2023年12月11日
 * 参数：name为按钮标签名
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
MenuItemImage* CTGScene::createGameButton(std::string name, const ccMenuCallback& callback)
{
	std::string picPath = "BottonScene_100x100.png";
	// 创建一个图片菜单项
	auto item = MenuItemImage::create(picPath, picPath, callback);

	// 按钮文字标签
	auto label = Label::createWithTTF(name, "fonts/simkai.ttf", 36);	// 设置标签字体和字号（当前为行楷）
	label->setPosition(item->getContentSize() / 2);	// 设置标签坐标
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);		// 设置标签锚点（当前为中心）
	label->setColor(Color3B::BLACK);				// 设置标签颜色（当前为黑色）
	item->addChild(label);

	return item;
}

/****************************************************
 * 功能：实现游戏开始按钮的点击事件
 * 作者：黄辰宇
 * 时间：2023年12月11日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::menuStartCallback(Ref* sender)
{
	// 重置界面
}

/****************************************************
 * 功能：实现打开商店按钮的点击事件
 * 作者：黄辰宇
 * 时间：2023年12月11日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::menuOpenShopCallback(Ref* sender)
{
	// 暂时还不会qwq
}

/****************************************************
 * 功能：实现退出游戏按钮的点击事件
 * 作者：黄辰宇
 * 时间：2023年12月11日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::menuExitGameCallback(Ref* sender)
{
	// 暂时还不会qwq
}

/****************************************************
 * 功能：实现按下按钮的回调
 * 作者：黄辰宇
 * 时间：2023年12月12日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	// 默认触发
	return true;
}

/****************************************************
 * 功能：实现释放按钮的回调（打开商店）
 * 作者：黄辰宇
 * 时间：2023年12月12日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void CTGScene::onTouchEnded(Touch* touch, Event* event)
{
	// 当前触摸的坐标点
	Vec2 position = touch->getLocation();

	// 判断坐标点在不在商店按钮上
	if (prt_shopButtonSize.containsPoint(position))
	{
		// 显示一个商店精灵
		// createShopNode();
	}
}

void CTGScene::createShopNode()
{
	Sprite* shopNode = Sprite::create("ShopScene_1000x400.png");
	// shopNode->setPosition()
	prt_backGround->addChild(shopNode, 4);	// 商店 z 值为 4
}
