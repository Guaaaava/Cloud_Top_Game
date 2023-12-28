#pragma once

/**************
* 功能:金铲铲之战菜单场景
* 作者:尹泽河
* 时间:2023年12月24日
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define pic_BG_path  "settings/background.png"						//设置背景图路径
#define pic_MS_BK_path "settings/MusicSlider_Back_test.png"			//滑动条背景图路径
#define pic_MS_NODE_path "settings/musicSlider_NodeNormal_test.png"	//滑动球图路径
#define pic_MS_PB_path "settings/musicSLider_pressBar_test.png"		//滑动条填充图路径
#define NUM_RCB 3													//频率复选框的个数为3
#define pic_RCB_NOR_path "settings/CheckBox_Normal.png"				//复选框正常图路径
#define pic_RCB_RRE_path "settings/CheckBox_Press.png"				//复选框选中图路径
#define pic_RCBNODE_path "settings/CheckBoxNode_Normal.png"			//复选框填充物路径
#define pic_RCB_DIS_path "settings/CheckBox_Disable.png"			//复选框不可选中图路径
#define pic_RCBNODE_DIS_path "settings/CheckBoxNode_Disable.png"	//复选框填充物不可选中图路径
#define pic_CLOSE_NOR_path "settings/closeNormal.png"				//关闭按钮正常图片路径
#define pic_CLOSE_SEL_path "settings.closeSelected.png"				//关闭按钮选中图片路径

class SETTINGSScene :public Scene
{
private:
	Sprite* _background;					//设置背景精灵
	Slider* _musicSlider;					//音乐大小滑动条
	CheckBox* _rateCheckBox[NUM_RCB];		//频率复选框数组
	Button* _close;							//退出按钮
public:
	static cocos2d::Scene* createScene();

	virtual bool init();//初始化函数

	CREATE_FUNC(SETTINGSScene);
private:
	Sprite* createBackground(Vec2 pos);														//背景创建函数

	Slider* createMusicSlider(Vec2 pos,const Slider::ccSliderCallback&callback);			//创建音乐滑动条

	CheckBox* createRateCheckbox(Vec2 pos, const CheckBox::ccCheckBoxCallback& callback);	//创建帧率复选框

	Label* createMyLabel(std::string& text,Vec2 pos);										//创建标签

	Button* createCloseBtn(Vec2 pos, const Button::ccWidgetClickCallback& callback);		//创建退出按钮

	void musicSliderCallBack(Ref* pSender);													//音乐滑动条回调函数

	void rateCheckboxCallBack(Ref* pSender);												//频率复选框回调函数

	void closeCallBack(Ref* pSender);														//关闭按钮回调函数
};