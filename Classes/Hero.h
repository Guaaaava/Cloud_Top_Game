#pragma once

/**************
* ����:Ӣ����(������)
* ����:�����
* ʱ��:2023��12��29��
**************/

#include "cocos2d.h"
USING_NS_CC;


class Hero :public cocos2d::Sprite
{
public:
	CREATE_FUNC(Hero);//������̬create����

	virtual bool init();//��ʼ������
};

class Annie :public Hero
{
public:
	CREATE_FUNC(Annie);//������̬create����

	virtual bool init();//��ʼ������
};