/**************
* 功能:金铲铲之战菜单场景
* 作者:尹泽河
* 时间:2023年12月24日
**************/

#include "SETTINGSScene.h"

USING_NS_CC;

/*************
* 函数名称:createScene()
* 函数参数:无
* 函数功能:场景SETTINGSScene的创建
* 返回值  :场景的指针
*************/
cocos2d::Scene* SETTINGSScene::createScene()
{
    return SETTINGSScene::create();
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
* 函数功能:开始场景SETTINGSScene的初始化
* 返回值  :true:场景成功创建;
*          fasle:场景创建失败
*************/
bool SETTINGSScene::init()
{
	/* 父类创建成功是前提 */
	if (!Scene::init())
		return false;

	/* 获取屏幕基础信息 */
	auto visibleSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //获取可视区域原点(左下角)

	/* 将设置背景加入场景 */
	Vec2 pos_BG = origin + visibleSize / 2;//获取位置
	_background = createBackground(pos_BG);//创建背景
	if (_background == nullptr) {
		problemLoading("");
	}
	else {
		this->addChild(_background);//加入场景
	}

	return true;
}

/*****************
* 函数功能:创建设置背景界面
* 函数参数:Vec2 pos:创建位置
* 返回值  :指向背景的指针
*****************/
Sprite* SETTINGSScene::createBackground(Vec2 pos)
{
	auto sprite = Sprite::create(pic_BG_path);//创建背景精灵

	if (sprite == nullptr) {
		problemLoading("");
	}
	else {
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//设置锚点
		sprite->setPosition(pos);					//设置位置

		/* 1.加入音乐滑动条 */
		Vec2 pos_MS = sprite->getPosition() + Vec2(0, 50);				//音乐滑动条位置
		_musicSlider = createMusicSlider(pos_MS, 
			CC_CALLBACK_1(SETTINGSScene::musicSliderCallBack, this));	//创建音乐滑动条
		sprite->addChild(_musicSlider);									//在背景中加入滑动条
		Vec2 pos_Label_MS = pos_MS + Vec2(-120 - _musicSlider->getContentSize().width / 2, 0);//标签位置
		std::string name_M = ConfigController::getInstance()->getCNByID(WORDS_MUSIC_VOLUME);	//获取名字
		auto label_MS = createMyLabel(name_M, pos_Label_MS);//创建音量大小标签
		sprite->addChild(label_MS);							//在背景中加入标签

		/* 2.加入频率复选框 */
		Vec2 pos_Label_R[NUM_RCB];			//标签数组
		Vec2 pos_RCB[NUM_RCB];				//位置数组
		std::string name_RCB[NUM_RCB];		//名字数组
		name_RCB[0] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_LOW);
		name_RCB[1] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_MID);
		name_RCB[2] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_HIG);
		for (int i = 0; i < NUM_RCB; i++) {
			pos_Label_R[i] =	pos_MS-_musicSlider->getContentSize()/2 
							+ Vec2(i * 100, -50);								//获得标签位置
			auto label = createMyLabel(name_RCB[i],pos_Label_R[i]);				//创建标签
			sprite->addChild(label);											//背景中加入标签
			pos_RCB[i] = label->getPosition() + Vec2(40, 0);					//获得复选框位置
			_rateCheckBox[i] = createRateCheckbox(pos_RCB[i],
					CC_CALLBACK_1(SETTINGSScene::rateCheckboxCallBack, this));	//创建复选框
			_rateCheckBox[i]->setTag(i);										//设置标签
			sprite->addChild(_rateCheckBox[i]);									//背景中加入复选框
		}
		Vec2 pos_Label_RCB = pos_Label_R[0] + Vec2(-120, 0);	//标签位置
		std::string name_R = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_QULITY);//获取名字
		auto label_RCB = createMyLabel(name_R, pos_Label_RCB);	//创建音量大小标签
		sprite->addChild(label_RCB);							//在背景中加入标签
	
		/* 3.加入退出按钮 */
		Vec2 pos_close = pos + Vec2(260, 125);									//关闭按钮位置
		_close = createCloseBtn(pos_close,
			CC_CALLBACK_1(SETTINGSScene::closeCallBack, this));					//创建关闭按钮
		sprite->addChild(_close);												//加入场景
	}

	return sprite;
}

/*****************
* 函数功能:创建音乐滑动条
* 函数参数:Vec2 pos:创建位置;
*		   const Slider::ccSliderCallback& callback
* 返回值  :指向滑动条的指针
*****************/
Slider* SETTINGSScene::createMusicSlider(Vec2 pos, const Slider::ccSliderCallback& callback)
{
	/* 创建一个滑动条 */
	auto slider = Slider::create();
	slider->loadBarTexture(pic_MS_BK_path);
	slider->loadSlidBallTextures(pic_MS_NODE_path);
	slider->loadProgressBarTexture(pic_MS_PB_path);

	if (slider == nullptr) {
		problemLoading("");
	}
	else {
		slider->setPercent(50);//设置初始大小

		slider->setAnchorPoint(Vec2::ANCHOR_MIDDLE);	//设置锚点
		slider->setPosition(pos);						//设置位置
		slider->addEventListener(callback);				//添加监听事件
	}

	return slider;
}

/*****************
* 函数功能:创建通用的帧率复选框
* 函数参数:Vec2 posn:位置
*          int tag:相应标签
* 返回值  :指向复选框的指针
*****************/
CheckBox* SETTINGSScene::createRateCheckbox(Vec2 pos, const CheckBox::ccCheckBoxCallback& callback)
{
	auto checkbox = CheckBox::create(pic_RCB_NOR_path,
		pic_RCB_RRE_path,
		pic_RCBNODE_path,
		pic_RCB_DIS_path,
		pic_RCBNODE_DIS_path);//建立通用复选框

	if (checkbox == nullptr) {
		problemLoading("");
	}
	else {
		checkbox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);			//设置锚点
		checkbox->setPosition(pos);									//设置位置
		checkbox->addEventListener(callback);						//添加监听事件
	}

	return checkbox;
}

/*****************
* 函数功能:创建通用的标签
* 函数参数:std::string& text:文本内容
* 返回值  :指向标签的指针
*****************/
Label* SETTINGSScene::createMyLabel(std::string& text,Vec2 pos)
{
	auto label = Label::createWithTTF(text, "fonts/Genshin.ttf", 24);	//创建标签
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);					//设置锚点
	label->setPosition(pos);											//设置位置

	return label;
}

/*****************
* 函数功能:创建退出按钮
* 函数参数:Vec2 pos:位置
* 返回值  :指向按钮的指针
*****************/
Button* SETTINGSScene::createCloseBtn(Vec2 pos, const Button::ccWidgetClickCallback& callback)
{
	auto button = Button::create(pic_CLOSE_NOR_path, pic_CLOSE_SEL_path);	//创建按钮

	if (button == nullptr) {
		problemLoading("");
	}
	else {
		button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);						//设置锚点
		button->setPosition(pos);											//设置位置
		button->addClickEventListener(callback);							//添加监听事件
	}

	return button;
}

/*****************
* 函数功能:音乐滑动条回调函数
* 函数参数:Ref* pSender
* 返回值  :无
*****************/
void SETTINGSScene::musicSliderCallBack(Ref* pSender)
{
	Slider* slider = dynamic_cast<Slider*>(pSender);

	if (slider != nullptr) {
		int per = slider->getPercent();
		auto ridio = SimpleAudioEngine::getInstance();

		ridio->setBackgroundMusicVolume(static_cast<float>(per) / 100);
	}

	return;
}

/*****************
* 函数功能:频率复选框回调函数
* 函数参数:Ref* pSender
* 返回值  :无
*****************/
void SETTINGSScene::rateCheckboxCallBack(Ref* pSender)
{
	if (pSender == nullptr) {
		return;
	}
	/* 获取选中复选框的序号 */
	int tag = dynamic_cast<CheckBox*>(pSender)->getTag();
	/* 先将所有复选框设为未选 */
	for (int i = 0; i < NUM_RCB; i++) {
		_rateCheckBox[i]->setSelected(false);
	}
	/* 将选中复选框设为已选 */
	_rateCheckBox[tag]->setSelected(true);
	///* 切换相应的帧率 */
	//auto director = Director::getInstance();
	//director->setAnimationInterval(1.0f / 40 + tag * 10);

	return;

}

/*****************
* 函数功能:关闭按钮回调函数
* 函数参数:Ref* pSender
* 返回值  :无
*****************/
void SETTINGSScene::closeCallBack(Ref* pSender)
{
	auto director = Director::getInstance();
	director->popScene();

	return;
}
