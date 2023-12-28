#pragma once

/**************
* ����:�����֮ս��ʼ����
* ����:�����
* ʱ��:2023��12��21��
**************/

#ifndef _START_SCENE_H
#define _START_SCENE_H

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include"MAINScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class STARTScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ������

	CREATE_FUNC(STARTScene);

	static MenuItemImage* creatMenuItem(std::string name, const ccMenuCallback& callback);//����ͨ�ò˵���

private:
	bool musicON;//��¼���ֲ���״̬

	void menuStartCallback(cocos2d::Ref* pSender);//��ʼ��ť�Ļص�

	void menuCloseCallback(cocos2d::Ref* pSender);//�˳���ť�Ļص�
};

#endif //_START_SCENE_H