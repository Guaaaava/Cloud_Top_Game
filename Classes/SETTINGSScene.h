#pragma once

/**************
* ����:�����֮ս�˵�����
* ����:�����
* ʱ��:2023��12��24��
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define pic_BG_path  "settings/background.png"						//���ñ���ͼ·��
#define pic_MS_BK_path "settings/MusicSlider_Back_test.png"			//����������ͼ·��
#define pic_MS_NODE_path "settings/musicSlider_NodeNormal_test.png"	//������ͼ·��
#define pic_MS_PB_path "settings/musicSLider_pressBar_test.png"		//���������ͼ·��
#define NUM_RCB 3													//Ƶ�ʸ�ѡ��ĸ���Ϊ3
#define pic_RCB_NOR_path "settings/CheckBox_Normal.png"				//��ѡ������ͼ·��
#define pic_RCB_RRE_path "settings/CheckBox_Press.png"				//��ѡ��ѡ��ͼ·��
#define pic_RCBNODE_path "settings/CheckBoxNode_Normal.png"			//��ѡ�������·��
#define pic_RCB_DIS_path "settings/CheckBox_Disable.png"			//��ѡ�򲻿�ѡ��ͼ·��
#define pic_RCBNODE_DIS_path "settings/CheckBoxNode_Disable.png"	//��ѡ������ﲻ��ѡ��ͼ·��
#define pic_CLOSE_NOR_path "settings/closeNormal.png"				//�رհ�ť����ͼƬ·��
#define pic_CLOSE_SEL_path "settings.closeSelected.png"				//�رհ�ťѡ��ͼƬ·��

class SETTINGSScene :public Scene
{
private:
	Sprite* _background;					//���ñ�������
	Sprite* ProgressTimer;                  //����ʱ�������
	Sprite* Lable;                          //����ʱ���ǩ
	Sprite* progress;                       //����ʱ�������
	Sprite* countdownCallback;              //��������ʱ
	Sprite* CountdownSprite;                //��������ʱ������
	Slider* _musicSlider;					//���ִ�С������
	CheckBox* _rateCheckBox[NUM_RCB];		//Ƶ�ʸ�ѡ������
	Button* _close;							//�˳���ť
public:
	static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ������

	CREATE_FUNC(SETTINGSScene);
private:
	Sprite* createBackground(Vec2 pos);														//������������

	Slider* createMusicSlider(Vec2 pos,const Slider::ccSliderCallback&callback);			//�������ֻ�����

	//Sprite* creatProgressTimer(Vec2 pos);                                                   //��������ʱ

	Sprite* createCountdownSprite(Vec2 pos);                                            //��������ʱ������        

	//Sprite* creatLable(Vec2 pos);                                                           //��������ʱ��ʱ���ǩ

	CheckBox* createRateCheckbox(Vec2 pos, const CheckBox::ccCheckBoxCallback& callback);	//����֡�ʸ�ѡ��

	Label* createLabel(const std::string& text, Vec2 pos);										//������ǩ

	Button* SETTINGSScene::createButton(const std::string& normalImage,
		const std::string& selectedImage, Vec2 pos, const Button::ccWidgetClickCallback& callback);	//�����˳���ť

	void musicSliderCallBack(Ref* pSender);													//���ֻ������ص�����

	void rateCheckboxCallBack(Ref* pSender);												//Ƶ�ʸ�ѡ��ص�����

	void closeCallBack(Ref* pSender);														//�رհ�ť�ص�����
};