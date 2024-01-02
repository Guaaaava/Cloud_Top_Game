/**************
* 功能:金铲铲之战主场景
* 作者:尹泽河
* 时间:2023年12月23日
**************/

#include "MAINScene.h"
#include "CTGScene.h"

USING_NS_CC;

#define SET 1

int MAINScene::gameMode = -1;

/*************
* 函数名称:createScene()
* 函数参数 : 无
* 函数功能 : 场景MAINScne的创建
* 返回值 : 无
* ************/
Scene * MAINScene::createScene()
{
	return MAINScene::create();
}

/*************
* 函数名称:problemLoading()
* 函数参数:const char*fileName:文件名
* 函数功能:无法打开文件时报错
* 返回值  :无
*************/
static void problemLoading(const char* fileName)
{
	printf("Error while loading: %s\n", fileName);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in startScene.cpp\n");
}

/*************
* 函数名称:init()
* 函数参数:无
* 函数功能:开始场景MAINScne的初始化
* 返回值  :true:场景成功创建;
*          fasle:场景创建失败
*************/
bool MAINScene::init()
{
	/* 父类创建成功是前提 */
	if (!Scene::init())
		return false;

	/* 获取屏幕基础信息 */
	auto visibleSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //获取可视区域原点(左下角)

	/* 预加载音乐 */
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("mainScene/Lonely Warrior.mp3");

	/* 1.背景精灵 */
	auto background = Sprite::create("mainScene/mainBackground.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin);
	this->addChild(background);

	/* 2.设置按钮 */
	Vec2 settingsBtn_pos(origin + visibleSize - Vec2(30, 30));
	int settingsBtn_zOrder = 1;
	/**********
	* 类型:按钮
	* 内容:设置按钮
	* 位置:settingsBtn_pos
	* 顺序:settingsBtn_zOrder
	**********/
	auto settingsBtn = Button::create("mainScene/settingsNormal.png", "mainScene/settingsSelected.png", "mainScene/settingsDisabled.png");
	settingsBtn->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);  //设置锚点
	settingsBtn->setPosition(settingsBtn_pos);			  //设置位置
	background->addChild(settingsBtn, settingsBtn_zOrder);//加入场景
	settingsBtn->addClickEventListener([](cocos2d::Ref* pSender)
		{
			/* 获取下一个场景 */
			auto nextScene = SETTINGSScene::create();
			/* 切换至下一个场景 */
			Director::getInstance()->pushScene(nextScene);
		}
	);

	/* 3.游戏菜单 */
	Vector<MenuItem*>MenuItems;

	/* 3.1训练模式菜单项 */
	const Vec2 trainingModeItem_pos(origin+Vec2(background->getContentSize().width/4, background->getContentSize().height / 2));
	/**********
	* 类型:菜单项
	* 内容:训练模式
	* 位置:trainingModeItem_pos
	**********/
	/* 创建图片菜单项 */
	auto trainingModeItem = MenuItemImage::create("mainScene/trainingModeNormal.png", "mainScene/trainingModeSelected.png", CC_CALLBACK_1(MAINScene::menuTrainingModeCallback, this));
	trainingModeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);	//锚点设置
	trainingModeItem->setPosition(trainingModeItem_pos);	//位置设置
	trainingModeItem->setCallback(CC_CALLBACK_1(MAINScene::menuTrainingModeCallback, this));//加入事件
	MenuItems.pushBack(trainingModeItem);					//加入菜单

	/* 3.2联机模式菜单项 */
	const Vec2 onlineModeItem_pos(origin + Vec2(3 * background->getContentSize().width / 4, background->getContentSize().height / 2));//位置
	/**********
	* 类型:菜单项
	* 内容:联机模式
	* 位置:onlineModeItem_pos
	**********/
	/* 创建图片菜单项 */
	auto onlineModeItem = MenuItemImage::create("mainScene/onlineModeNormal.png", "mainScene/onlineModeSelected.png", CC_CALLBACK_1(MAINScene::menuOnlineModeCallback, this));
	onlineModeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//锚点设置
	onlineModeItem->setPosition(onlineModeItem_pos);	//位置设置
	onlineModeItem->setCallback(CC_CALLBACK_1(MAINScene::menuOnlineModeCallback, this));//设置事件
	MenuItems.pushBack(onlineModeItem);					//加入菜单

	auto menu = Menu::createWithArray(MenuItems);//创建菜单
	menu->setPosition(Vec2::ZERO);				 //设置菜单位置
	background->addChild(menu);;				 //将菜单加入背景

	/* 4.背景音乐 */
	audio->playBackgroundMusic("mainScene/Lonely Warrior.mp3", true);
	if (audio == nullptr) {
		problemLoading("mainScene/Lonely Warrior.mp3");
	}

	return true;
}

/*************
* 函数参数:cocos2d::Ref* pSender
* 函数功能:训练模式回调函数
* 返回值  :无
*************/
void MAINScene::menuTrainingModeCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();//暂停当前音乐

	auto director = Director::getInstance();

	/* 改变窗口大小 */
	Size newSize(CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT);
	director->getOpenGLView()->setDesignResolutionSize(newSize.width, newSize.height, ResolutionPolicy::EXACT_FIT);
	director->getOpenGLView()->setFrameSize(newSize.width, newSize.height);

	gameMode = 1;

	/* 下一场景进栈 */
	auto nextScene = CTGScene::create();
	director->pushScene(nextScene);

}

/*************
* 函数参数:cocos2d::Ref* pSender
* 函数功能:联机模式回调函数
* 返回值  :无
*************/
void MAINScene::menuOnlineModeCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();//暂停当前音乐

	auto director = Director::getInstance();

	/* 改变窗口大小 */
	Size newSize(CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT);
	director->getOpenGLView()->setDesignResolutionSize(newSize.width, newSize.height, ResolutionPolicy::EXACT_FIT);
	director->getOpenGLView()->setFrameSize(newSize.width, newSize.height);

	gameMode = 2;

	/* 下一场景进栈 */
	auto nextScene = CTGScene::create();
	director->pushScene(nextScene);
}
