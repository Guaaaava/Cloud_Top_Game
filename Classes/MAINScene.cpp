/**************
* ����:�����֮ս������
* ����:�����
* ʱ��:2023��12��23��
**************/

#include "MAINScene.h"
#include "CTGScene.h"

USING_NS_CC;

#define SET 1

int MAINScene::gameMode = -1;

/*************
* ��������:createScene()
* �������� : ��
* �������� : ����MAINScne�Ĵ���
* ����ֵ : ��
* ************/
Scene * MAINScene::createScene()
{
	return MAINScene::create();
}

/*************
* ��������:problemLoading()
* ��������:const char*fileName:�ļ���
* ��������:�޷����ļ�ʱ����
* ����ֵ  :��
*************/
static void problemLoading(const char* fileName)
{
	printf("Error while loading: %s\n", fileName);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in startScene.cpp\n");
}

/*************
* ��������:init()
* ��������:��
* ��������:��ʼ����MAINScne�ĳ�ʼ��
* ����ֵ  :true:�����ɹ�����;
*          fasle:��������ʧ��
*************/
bool MAINScene::init()
{
	/* ���ഴ���ɹ���ǰ�� */
	if (!Scene::init())
		return false;

	/* ��ȡ��Ļ������Ϣ */
	auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ���������С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //��ȡ��������ԭ��(���½�)

	/* Ԥ�������� */
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("mainScene/Lonely Warrior.mp3");

	/* 1.�������� */
	auto background = Sprite::create("mainScene/mainBackground.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin);
	this->addChild(background);

	/* 2.���ð�ť */
	Vec2 settingsBtn_pos(origin + visibleSize - Vec2(30, 30));
	int settingsBtn_zOrder = 1;
	/**********
	* ����:��ť
	* ����:���ð�ť
	* λ��:settingsBtn_pos
	* ˳��:settingsBtn_zOrder
	**********/
	auto settingsBtn = Button::create("mainScene/settingsNormal.png", "mainScene/settingsSelected.png", "mainScene/settingsDisabled.png");
	settingsBtn->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);  //����ê��
	settingsBtn->setPosition(settingsBtn_pos);			  //����λ��
	background->addChild(settingsBtn, settingsBtn_zOrder);//���볡��
	settingsBtn->addClickEventListener([](cocos2d::Ref* pSender)
		{
			/* ��ȡ��һ������ */
			auto nextScene = SETTINGSScene::create();
			/* �л�����һ������ */
			Director::getInstance()->pushScene(nextScene);
		}
	);

	/* 3.��Ϸ�˵� */
	Vector<MenuItem*>MenuItems;

	/* 3.1ѵ��ģʽ�˵��� */
	const Vec2 trainingModeItem_pos(origin+Vec2(background->getContentSize().width/4, background->getContentSize().height / 2));
	/**********
	* ����:�˵���
	* ����:ѵ��ģʽ
	* λ��:trainingModeItem_pos
	**********/
	/* ����ͼƬ�˵��� */
	auto trainingModeItem = MenuItemImage::create("mainScene/trainingModeNormal.png", "mainScene/trainingModeSelected.png", CC_CALLBACK_1(MAINScene::menuTrainingModeCallback, this));
	trainingModeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);	//ê������
	trainingModeItem->setPosition(trainingModeItem_pos);	//λ������
	trainingModeItem->setCallback(CC_CALLBACK_1(MAINScene::menuTrainingModeCallback, this));//�����¼�
	MenuItems.pushBack(trainingModeItem);					//����˵�

	/* 3.2����ģʽ�˵��� */
	const Vec2 onlineModeItem_pos(origin + Vec2(3 * background->getContentSize().width / 4, background->getContentSize().height / 2));//λ��
	/**********
	* ����:�˵���
	* ����:����ģʽ
	* λ��:onlineModeItem_pos
	**********/
	/* ����ͼƬ�˵��� */
	auto onlineModeItem = MenuItemImage::create("mainScene/onlineModeNormal.png", "mainScene/onlineModeSelected.png", CC_CALLBACK_1(MAINScene::menuOnlineModeCallback, this));
	onlineModeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//ê������
	onlineModeItem->setPosition(onlineModeItem_pos);	//λ������
	onlineModeItem->setCallback(CC_CALLBACK_1(MAINScene::menuOnlineModeCallback, this));//�����¼�
	MenuItems.pushBack(onlineModeItem);					//����˵�

	auto menu = Menu::createWithArray(MenuItems);//�����˵�
	menu->setPosition(Vec2::ZERO);				 //���ò˵�λ��
	background->addChild(menu);;				 //���˵����뱳��

	/* 4.�������� */
	audio->playBackgroundMusic("mainScene/Lonely Warrior.mp3", true);
	if (audio == nullptr) {
		problemLoading("mainScene/Lonely Warrior.mp3");
	}

	return true;
}

/*************
* ��������:cocos2d::Ref* pSender
* ��������:ѵ��ģʽ�ص�����
* ����ֵ  :��
*************/
void MAINScene::menuTrainingModeCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();//��ͣ��ǰ����

	auto director = Director::getInstance();

	/* �ı䴰�ڴ�С */
	Size newSize(CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT);
	director->getOpenGLView()->setDesignResolutionSize(newSize.width, newSize.height, ResolutionPolicy::EXACT_FIT);
	director->getOpenGLView()->setFrameSize(newSize.width, newSize.height);

	gameMode = 1;

	/* ��һ������ջ */
	auto nextScene = CTGScene::create();
	director->pushScene(nextScene);

}

/*************
* ��������:cocos2d::Ref* pSender
* ��������:����ģʽ�ص�����
* ����ֵ  :��
*************/
void MAINScene::menuOnlineModeCallback(cocos2d::Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();//��ͣ��ǰ����

	auto director = Director::getInstance();

	/* �ı䴰�ڴ�С */
	Size newSize(CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT);
	director->getOpenGLView()->setDesignResolutionSize(newSize.width, newSize.height, ResolutionPolicy::EXACT_FIT);
	director->getOpenGLView()->setFrameSize(newSize.width, newSize.height);

	gameMode = 2;

	/* ��һ������ջ */
	auto nextScene = CTGScene::create();
	director->pushScene(nextScene);
}
