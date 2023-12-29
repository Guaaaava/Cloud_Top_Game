/**************
* ����:�����֮ս��ʼ����
* ����:�����
* ʱ��:2023��12��21��
**************/

#include "startScene.h"

USING_NS_CC;

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
		JDSTARLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);	//ê������

		JDSTARLabel->setPosition(JDSTAR_pos);				//λ������

		layer->addChild(JDSTARLabel, JDSTAR_zOrder);		//�������
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
	const Vec2 startGameItem_pos(GCCLabel->getPosition() + Vec2(0, -60 - GCCLabel->getContentSize().height));//λ��
	/**********
	* ����:�˵���
	* ����:ѵ��ģʽ
	* λ��:trainingModeItem_pos
	**********/
	/* ����ͼƬ�˵��� */
	std::string gemeStart = ConfigController::getInstance()->getCNByID(WORDS_GAME_START);
	auto startGame = creatMenuItem(gemeStart, CC_CALLBACK_1(STARTScene::menuStartCallback, this));
	startGame->setPosition(startGameItem_pos);//λ������
	MenuItems.pushBack(startGame);	  //����˵�

	/* 4.2�˳���Ϸ�˵��� */
	const Vec2 closeGame_pos(startGame->getPosition() + Vec2(0,-20-startGame->getContentSize().height));//λ��
	/**********
	* ����:�˵���
	* ����:����ģʽ
	* λ��:onlineModeItem_pos
	**********/
	/* ����ͼƬ�˵��� */
	std::string gameClose = ConfigController::getInstance()->getCNByID(WORDS_GAME_CLOSE);
	auto closeGame = creatMenuItem(gameClose, CC_CALLBACK_1(STARTScene::menuCloseCallback, this));
	closeGame->setPosition(closeGame_pos);		//λ������
	MenuItems.pushBack(closeGame);				//����˵�
	
	auto menu = Menu::createWithArray(MenuItems);//�����˵�
	menu->setPosition(Vec2::ZERO);				 //���ò˵�λ��
	layer->addChild(menu);						 //���˵����볡��

	/* 5.������Ч */

	/**********
	* ����:����
	* ����:startMusic
	**********/
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("startScene/Lonely Warrior.mp3", true);
	if (audio == nullptr) {
		problemLoading("startScene/Lonely Warrior.mp3");
	}


	/* 6.������ť */
	const Vec2 silenceBtn_pos(origin + visibleSize - Vec2(20, 20));//λ��
	/**********
	* ����:���ز˵���
	* ����:������ť
	**********/
	this->musicON = true;//Ĭ�ϲ�������
	auto bgm = SimpleAudioEngine::getInstance();
	bgm->playBackgroundMusic("startScene/startMusic.mp3", true);
	auto silenceBtn = Button::create("startScene/silenceBtnON.png");
	silenceBtn->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);//����ê��
	silenceBtn->setPosition(silenceBtn_pos);		   //����λ��
	layer->addChild(silenceBtn);					   //�����
	/* �ص����� */
	silenceBtn->addClickEventListener([this](cocos2d::Ref* pSender) {
		Button* Btn = dynamic_cast<Button*>(pSender);
		if (musicON == true) {
			/* �л�״̬ */
			musicON = false;
			/* �л�ͼ�� */
			Btn->loadTextures("startScene/silenceBtnOFF.png", "startScene/silenceBtnOFF.png", "startScene/silenceBtnOFF.png");
			/* ��ͣ���� */
			auto audio = SimpleAudioEngine::getInstance();
			audio->pauseBackgroundMusic();

		}//���ڲ���
		else {
			/* �л�״̬ */
			musicON = true;
			/* �л�ͼ�� */
			Btn->loadTextures("startScene/silenceBtnON.png", "startScene/silenceBtnON.png", "startScene/silenceBtnON.png");
			/* �ָ����� */
			auto audio = SimpleAudioEngine::getInstance();
			audio->resumeBackgroundMusic();
		}//�Ѿ���ͣ
		});

	return true;
}

/*************
* ��������:creatMenuItem()
* ��������:std::string name:�˵�������
*          const ccMenuCallback& callback:�˵���ص�����
* ��������:����һ��ͨ�ò˵���
* ����ֵ  :ָ��˵����ָ��
*************/
MenuItemImage* STARTScene::creatMenuItem(std::string name, const ccMenuCallback& callback)
{
	/* ����һ��ͨ��ͼƬ�˵��� */
	auto item = MenuItemImage::create("startScene/BtnNormal.png", "startScene/BtnSelected.png", callback);
	if (item == nullptr) {
		problemLoading("startScene / BtnNormal.png");
	}
	else {
		/* �����ǩ���� */
		auto label = Label::createWithTTF(name, "fonts/TJL.ttf", 32);//������ǩ
		if (label == nullptr) {
			problemLoading("fonts/TJL.ttf");
		}
		else {
			label->setPosition(item->getContentSize() / 2);//����λ��Ϊ�˵�������
			item->addChild(label);//�����ǩ
		}
	}

	return item;
}

/*************
* ��������:menuTrainingModeCallback()
* ��������:cocos2d::Ref* pSender
* ��������:ѵ��ģʽ��ť�Ļص�����������ѵ��ģʽ����
* ����ֵ  :��
*************/
void STARTScene::menuStartCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
	/* ��ȡ��һ������ */
	auto nextScene = MAINScene::create();
	/* �л�����һ������ */
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, nextScene, Color3B::WHITE));
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
