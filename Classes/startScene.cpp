/**************
* ����:�����֮ս��ʼ����
* ����:�����
* ʱ��:2023��12��21��
**************/

#include "startScene.h"

USING_NS_CC;

#define WORDS_GAME_NAME 1001	// �������֮ս������
#define WORDS_GAME_START 1002	//����ʼ��Ϸ������
#define WORDS_GAME_CLOSE 1003   //���˳���Ϸ������

/*************
* ��������:createScene()
* ��������:��
* ��������:����STARTScne�Ĵ���
* ����ֵ  :��
*************/
Scene* STARTScene::createScene()
{
	return STARTScene::create();
}

/*************
* ��������:problemLoading()
* ��������:const char*fileName:�ļ���
* ��������:�޷����ļ�ʱ����
* ����ֵ  :��
*************/
static void problemLoading(const char*fileName)
{
	printf("Error while loading: %s\n", fileName);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in startScene.cpp\n");
}

/*************
* ��������:init()
* ��������:��
* ��������:��ʼ����STARTScne�ĳ�ʼ��
* ����ֵ  :true:�����ɹ�����;
*          fasle:��������ʧ��  
*************/
bool STARTScene::init()
{
	/* ���ഴ���ɹ���ǰ�� */
	if (!Scene::init())
		return false;

	/* ��ȡ��Ļ������Ϣ */
	auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ���������С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //��ȡ��������ԭ��(���½�)

	/* 1.��ɫ������ */
	auto layer = LayerColor::create(Color4B::BLACK);//���ñ�������ɫ
	layer->setPosition(origin);					    //���ñ�����λ��
	layer->setContentSize(visibleSize);			    //���ñ������С
	this->addChild(layer);						    //����������볡��

	/* 2.JDStar��ǩ */
	const float JDSTAR_size = 45;	   //��С
	const Vec2 JDSTAR_pos(origin.x,
		origin.y + visibleSize.height);//λ��
	const int JDSTAR_zOrder = 1;	   //��ʾ˳��
	/**********
	* ����:��ǩ
	* ����:JDStar
	* ����:Genshin.ttf
	* ��С:JDSTAR_size
	* λ��:JDSTAR_pos
	**********/
	auto JDSTARLabel = Label::createWithTTF("JDStar", "fonts/Genshin.ttf", JDSTAR_size);

	if (JDSTARLabel == nullptr) {
		problemLoading("fonts / Genshin.ttf");
	}
	else {
		JDSTARLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);//ê������

		JDSTARLabel->setPosition(JDSTAR_pos);//λ������

		layer->addChild(JDSTARLabel, JDSTAR_zOrder);//�������
	}

	/* 3.�����֮ս��ǩ */
	const float GCC_size = 64;		   //��С
	const Vec2 GCC_pos(origin.x + visibleSize.width / 2,
					   origin.y + visibleSize.height / 2 + 100);//λ��
	const int GCC_zOrder = 2;		   //��ʾ˳��
	/**********
	* ����:��ǩ
	* ����:�����֮ս
	* ����:TJL.ttf
	* ��С:GCC_size
	* λ��:GCC_pos
	**********/
	std::string gameName = ConfigController::getInstance()->getCNByID(WORDS_GAME_NAME);
	auto GCCLabel = Label::createWithTTF(gameName, "fonts/TJL.ttf", GCC_size);
	if (GCCLabel == nullptr) {
		problemLoading("fonts/TJL.ttf");
	}
	else {
		GCCLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//ê������

		GCCLabel->setPosition(GCC_pos);//λ������

		GCCLabel->setColor(Color3B::YELLOW);//��ɫ����

		layer->addChild(GCCLabel, GCC_zOrder);//���볡����
	}

	/* 4.��Ϸ�˵� */
	Vector<MenuItem*>MenuItems;

	/* 4.1��ʼ��Ϸ�˵��� */
	const Vec2 startItem_pos(GCCLabel->getPosition() + Vec2(0, -60 - GCCLabel->getContentSize().height));//λ��
	/**********
	* ����:�˵���
	* ����:��ʼ��Ϸ
	* λ��:startItem_pos
	**********/
	/* ����ͼƬ�˵��� */
	std::string gameStart = ConfigController::getInstance()->getCNByID(WORDS_GAME_START);
	auto startItem = creatMenuItem(gameStart, CC_CALLBACK_1(STARTScene::menuStartCallback, this));
	startItem->setPosition(startItem_pos);				  //λ������
	MenuItems.pushBack(startItem);

	/* 4.2�˳���Ϸ�˵��� */
	const Vec2 closeItem_pos(startItem->getPosition() + Vec2(0, -20 - startItem->getContentSize().height));//λ��
	/**********
	* ����:�˵���
	* ����:�˳���Ϸ
	* λ��:closeItem_pos
	**********/
	std::string gameClose = ConfigController::getInstance()->getCNByID(WORDS_GAME_CLOSE);
	auto closeItem = creatMenuItem(gameClose, CC_CALLBACK_1(STARTScene::menuCloseCallback, this));
	closeItem->setPosition(closeItem_pos);				  //λ������
	MenuItems.pushBack(closeItem);

	auto menu = Menu::createWithArray(MenuItems);//�����˵�
	menu->setPosition(Vec2::ZERO);				 //���ò˵�λ��
	layer->addChild(menu);						 //���˵����볡��
	
	return true;
}

MenuItemImage* STARTScene::creatMenuItem(std::string name, const ccMenuCallback& callback)
{
	/* ����һ��ͨ��ͼƬ�˵��� */
	auto item = MenuItemImage::create("BtnNormal.png", "BtnSelected.png", callback);
	if (item == nullptr) {
	
	}
	else {
		/* �����ǩ���� */
		auto label = Label::createWithTTF(name, "fonts/TJL.ttf", 32);//������ǩ
		label->setPosition(item->getContentSize() / 2);//����λ��Ϊ�˵�������
		item->addChild(label);//�����ǩ
	}

	return item;
}

/*************
* ��������:menuStartCallback()
* ��������:cocos2d::Ref* pSender
* ��������:��ʼ��Ϸ��ť�Ļص�������������һ������
* ����ֵ  :��
*************/
void STARTScene::menuStartCallback(cocos2d::Ref* pSender)
{
	auto nextScene = CTGScene::create();

	Director::getInstance()->pushScene(TransitionFade::create(0.5, nextScene, Color3B(0, 255, 255)));

	return;
}

/*************
* ��������:menuCloseCallback()
* ��������:cocos2d::Ref* pSender
* ��������:�˳���Ϸ��ť�Ļص�������������Ϸ
* ����ֵ  :��
*************/
void STARTScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	/* ������Ϸ */
	Director::getInstance()->end();

	return;
}
