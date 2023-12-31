/**************
* 功能:金铲铲之战开始场景
* 作者:尹泽河
* 时间:2023年12月21日
**************/

#include "startScene.h"

USING_NS_CC;

/*************
* 函数名称:createScene()
* 函数参数:无
* 函数功能:场景STARTScne的创建
* 返回值  :无
*************/
Scene* STARTScene::createScene()
{
	return STARTScene::create();
}

/*************
* 函数名称:problemLoading()
* 函数参数:const char*fileName:文件名
* 函数功能:无法打开文件时报错
* 返回值  :无
*************/
static void problemLoading(const char*fileName)
{
	printf("Error while loading: %s\n", fileName);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in startScene.cpp\n");
}

/*************
* 函数名称:init()
* 函数参数:无
* 函数功能:开始场景STARTScne的初始化
* 返回值  :true:场景成功创建;
*          fasle:场景创建失败  
*************/
bool STARTScene::init()
{
	/* 父类创建成功是前提 */
	if (!Scene::init())
		return false;

	/* 获取屏幕基础信息 */
	auto visibleSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //获取可视区域原点(左下角)

	/* 1.黑色背景层 */
	auto layer = LayerColor::create(Color4B::BLACK);//设置背景层颜色
	layer->setPosition(origin);					    //设置背景层位置
	layer->setContentSize(visibleSize);			    //设置背景层大小
	this->addChild(layer);						    //将背景层加入场景

	/* 2.JDStar标签 */
	const float JDSTAR_size = 45;	   //大小
	const Vec2 JDSTAR_pos(origin.x,
		origin.y + visibleSize.height);//位置
	const int JDSTAR_zOrder = 1;	   //显示顺序
	/**********
	* 类型:标签
	* 内容:JDStar
	* 字体:Genshin.ttf
	* 大小:JDSTAR_size
	* 位置:JDSTAR_pos
	**********/
	auto JDSTARLabel = Label::createWithTTF("JDStar", "fonts/Genshin.ttf", JDSTAR_size);

	if (JDSTARLabel == nullptr) {
		problemLoading("fonts / Genshin.ttf");
	}
	else {
		JDSTARLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);	//锚点设置

		JDSTARLabel->setPosition(JDSTAR_pos);				//位置设置

		layer->addChild(JDSTARLabel, JDSTAR_zOrder);		//加入层中
	}

	/* 3.金铲铲之战标签 */
	const float GCC_size = 64;		   //大小
	const Vec2 GCC_pos(origin.x + visibleSize.width / 2,
					   origin.y + visibleSize.height / 2 + 100);//位置
	const int GCC_zOrder = 2;		   //显示顺序
	/**********
	* 类型:标签
	* 内容:金铲铲之战
	* 字体:TJL.ttf
	* 大小:GCC_size
	* 位置:GCC_pos
	**********/
	std::string gameName = ConfigController::getInstance()->getCNByID(WORDS_GAME_NAME);
	auto GCCLabel = Label::createWithTTF(gameName, "fonts/TJL.ttf", GCC_size);
	if (GCCLabel == nullptr) {
		problemLoading("fonts/TJL.ttf");
	}
	else {
		GCCLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//锚点设置

		GCCLabel->setPosition(GCC_pos);//位置设置

		GCCLabel->setColor(Color3B::YELLOW);//颜色设置

		layer->addChild(GCCLabel, GCC_zOrder);//加入场景中
	}

	/* 4.游戏菜单 */
	Vector<MenuItem*>MenuItems;

	/* 4.1开始游戏菜单项 */
	const Vec2 startGameItem_pos(GCCLabel->getPosition() + Vec2(0, -60 - GCCLabel->getContentSize().height));//位置
	/**********
	* 类型:菜单项
	* 内容:训练模式
	* 位置:trainingModeItem_pos
	**********/
	/* 创建图片菜单项 */
	std::string gemeStart = ConfigController::getInstance()->getCNByID(WORDS_GAME_START);
	auto startGame = creatMenuItem(gemeStart, CC_CALLBACK_1(STARTScene::menuStartCallback, this));
	startGame->setPosition(startGameItem_pos);//位置设置
	MenuItems.pushBack(startGame);	  //加入菜单

	/* 4.2退出游戏菜单项 */
	const Vec2 closeGame_pos(startGame->getPosition() + Vec2(0,-20-startGame->getContentSize().height));//位置
	/**********
	* 类型:菜单项
	* 内容:联机模式
	* 位置:onlineModeItem_pos
	**********/
	/* 创建图片菜单项 */
	std::string gameClose = ConfigController::getInstance()->getCNByID(WORDS_GAME_CLOSE);
	auto closeGame = creatMenuItem(gameClose, CC_CALLBACK_1(STARTScene::menuCloseCallback, this));
	closeGame->setPosition(closeGame_pos);		//位置设置
	MenuItems.pushBack(closeGame);				//加入菜单
	
	auto menu = Menu::createWithArray(MenuItems);//创建菜单
	menu->setPosition(Vec2::ZERO);				 //设置菜单位置
	layer->addChild(menu);						 //将菜单加入场景

	/* 5.背景音效 */

	/**********
	* 类型:音乐
	* 内容:startMusic
	**********/
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("startScene/Lonely Warrior.mp3", true);
	if (audio == nullptr) {
		problemLoading("startScene/Lonely Warrior.mp3");
	}


	/* 6.静音按钮 */
	const Vec2 silenceBtn_pos(origin + visibleSize - Vec2(20, 20));//位置
	/**********
	* 类型:开关菜单项
	* 内容:静音按钮
	**********/
	this->musicON = true;//默认播放音乐
	auto bgm = SimpleAudioEngine::getInstance();
	bgm->playBackgroundMusic("startScene/startMusic.mp3", true);
	auto silenceBtn = Button::create("startScene/silenceBtnON.png");
	silenceBtn->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);//设置锚点
	silenceBtn->setPosition(silenceBtn_pos);		   //设置位置
	layer->addChild(silenceBtn);					   //加入层
	/* 回调函数 */
	silenceBtn->addClickEventListener([this](cocos2d::Ref* pSender) {
		Button* Btn = dynamic_cast<Button*>(pSender);
		if (musicON == true) {
			/* 切换状态 */
			musicON = false;
			/* 切换图标 */
			Btn->loadTextures("startScene/silenceBtnOFF.png", "startScene/silenceBtnOFF.png", "startScene/silenceBtnOFF.png");
			/* 暂停音乐 */
			auto audio = SimpleAudioEngine::getInstance();
			audio->pauseBackgroundMusic();

		}//正在播放
		else {
			/* 切换状态 */
			musicON = true;
			/* 切换图标 */
			Btn->loadTextures("startScene/silenceBtnON.png", "startScene/silenceBtnON.png", "startScene/silenceBtnON.png");
			/* 恢复音乐 */
			auto audio = SimpleAudioEngine::getInstance();
			audio->resumeBackgroundMusic();
		}//已经暂停
		});

	return true;
}

/*************
* 函数名称:creatMenuItem()
* 函数参数:std::string name:菜单项内容
*          const ccMenuCallback& callback:菜单项回调函数
* 函数功能:创建一个通用菜单项
* 返回值  :指向菜单项的指针
*************/
MenuItemImage* STARTScene::creatMenuItem(std::string name, const ccMenuCallback& callback)
{
	/* 创建一个通用图片菜单项 */
	auto item = MenuItemImage::create("startScene/BtnNormal.png", "startScene/BtnSelected.png", callback);
	if (item == nullptr) {
		problemLoading("startScene / BtnNormal.png");
	}
	else {
		/* 加入标签名称 */
		auto label = Label::createWithTTF(name, "fonts/TJL.ttf", 32);//创建标签
		if (label == nullptr) {
			problemLoading("fonts/TJL.ttf");
		}
		else {
			label->setPosition(item->getContentSize() / 2);//设置位置为菜单项中央
			item->addChild(label);//加入标签
		}
	}

	return item;
}

/*************
* 函数名称:menuTrainingModeCallback()
* 函数参数:cocos2d::Ref* pSender
* 函数功能:训练模式按钮的回调函数，进入训练模式场景
* 返回值  :无
*************/
void STARTScene::menuStartCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
	/* 获取下一个场景 */
	auto nextScene = MAINScene::create();
	/* 切换至下一个场景 */
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, nextScene, Color3B::WHITE));
}

/*************
* 函数名称:menuCloseCallback()
* 函数参数:cocos2d::Ref* pSender
* 函数功能:退出游戏按钮的回调函数，结束游戏
* 返回值  :无
*************/
void STARTScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	/* 结束游戏 */
	Director::getInstance()->end();

	return;
}
