#pragma once

/**************
* ����:�����֮ս������
* ����:�����
* ʱ��:2023��12��23��
**************/

#include"cocos2d.h"
USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include"ConfigController.h"

#include"SETTINGSScene.h"
#include"CTGScene.h"

class MAINScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ������

	CREATE_FUNC(MAINScene);

	static int getGameMode() { return gameMode; };

private:
	static int gameMode;

	void menuTrainingModeCallback(cocos2d::Ref* pSender);//ѵ��ģʽ��ť�Ļص�����

	void menuOnlineModeCallback(cocos2d::Ref* pSender);//����ģʽ��ť�Ļص�����

};
