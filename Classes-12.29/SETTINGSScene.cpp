/**************
* ����:�����֮ս�˵�����
* ����:�����
* ʱ��:2023��12��24��
**************/

#include "SETTINGSScene.h"

USING_NS_CC;

/*************
* ��������:createScene()
* ��������:��
* ��������:����SETTINGSScene�Ĵ���
* ����ֵ  :������ָ��
*************/
cocos2d::Scene* SETTINGSScene::createScene()
{
    return SETTINGSScene::create();
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
* ��������:��ʼ����SETTINGSScene�ĳ�ʼ��
* ����ֵ  :true:�����ɹ�����;
*          fasle:��������ʧ��
*************/
bool SETTINGSScene::init()
{
	/* ���ഴ���ɹ���ǰ�� */
	if (!Scene::init())
		return false;

	/* ��ȡ��Ļ������Ϣ */
	auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ���������С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	 //��ȡ��������ԭ��(���½�)

	/* �����ñ������볡�� */
	Vec2 pos_BG = origin + visibleSize / 2;//��ȡλ��
	_background = createBackground(pos_BG);//��������
	if (_background == nullptr) {
		problemLoading("");
	}
	else {
		this->addChild(_background);//���볡��
	}

	return true;
}

/*****************
* ��������:�������ñ�������
* ��������:Vec2 pos:����λ��
* ����ֵ  :ָ�򱳾���ָ��
*****************/
Sprite* SETTINGSScene::createBackground(Vec2 pos)
{
	auto sprite = Sprite::create(pic_BG_path);//������������

	if (sprite == nullptr) {
		problemLoading("");
	}
	else {
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//����ê��
		sprite->setPosition(pos);					//����λ��

		/* 1.�������ֻ����� */
		Vec2 pos_MS = sprite->getPosition() + Vec2(0, 50);				//���ֻ�����λ��
		_musicSlider = createMusicSlider(pos_MS, 
			CC_CALLBACK_1(SETTINGSScene::musicSliderCallBack, this));	//�������ֻ�����
		sprite->addChild(_musicSlider);									//�ڱ����м��뻬����
		Vec2 pos_Label_MS = pos_MS + Vec2(-120 - _musicSlider->getContentSize().width / 2, 0);//��ǩλ��
		std::string name_M = ConfigController::getInstance()->getCNByID(WORDS_MUSIC_VOLUME);	//��ȡ����
		auto label_MS = createMyLabel(name_M, pos_Label_MS);//����������С��ǩ
		sprite->addChild(label_MS);							//�ڱ����м����ǩ

		/* 2.����Ƶ�ʸ�ѡ�� */
		Vec2 pos_Label_R[NUM_RCB];			//��ǩ����
		Vec2 pos_RCB[NUM_RCB];				//λ������
		std::string name_RCB[NUM_RCB];		//��������
		name_RCB[0] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_LOW);
		name_RCB[1] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_MID);
		name_RCB[2] = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_HIG);
		for (int i = 0; i < NUM_RCB; i++) {
			pos_Label_R[i] =	pos_MS-_musicSlider->getContentSize()/2 
							+ Vec2(i * 100, -50);								//��ñ�ǩλ��
			auto label = createMyLabel(name_RCB[i],pos_Label_R[i]);				//������ǩ
			sprite->addChild(label);											//�����м����ǩ
			pos_RCB[i] = label->getPosition() + Vec2(40, 0);					//��ø�ѡ��λ��
			_rateCheckBox[i] = createRateCheckbox(pos_RCB[i],
					CC_CALLBACK_1(SETTINGSScene::rateCheckboxCallBack, this));	//������ѡ��
			_rateCheckBox[i]->setTag(i);										//���ñ�ǩ
			sprite->addChild(_rateCheckBox[i]);									//�����м��븴ѡ��
		}
		Vec2 pos_Label_RCB = pos_Label_R[0] + Vec2(-120, 0);	//��ǩλ��
		std::string name_R = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_QULITY);//��ȡ����
		auto label_RCB = createMyLabel(name_R, pos_Label_RCB);	//����������С��ǩ
		sprite->addChild(label_RCB);							//�ڱ����м����ǩ
	
		/* 3.�����˳���ť */
		Vec2 pos_close = pos + Vec2(260, 125);									//�رհ�ťλ��
		_close = createCloseBtn(pos_close,
			CC_CALLBACK_1(SETTINGSScene::closeCallBack, this));					//�����رհ�ť
		sprite->addChild(_close);												//���볡��
	}

	return sprite;
}

/*****************
* ��������:�������ֻ�����
* ��������:Vec2 pos:����λ��;
*		   const Slider::ccSliderCallback& callback
* ����ֵ  :ָ�򻬶�����ָ��
*****************/
Slider* SETTINGSScene::createMusicSlider(Vec2 pos, const Slider::ccSliderCallback& callback)
{
	/* ����һ�������� */
	auto slider = Slider::create();
	slider->loadBarTexture(pic_MS_BK_path);
	slider->loadSlidBallTextures(pic_MS_NODE_path);
	slider->loadProgressBarTexture(pic_MS_PB_path);

	if (slider == nullptr) {
		problemLoading("");
	}
	else {
		slider->setPercent(50);//���ó�ʼ��С

		slider->setAnchorPoint(Vec2::ANCHOR_MIDDLE);	//����ê��
		slider->setPosition(pos);						//����λ��
		slider->addEventListener(callback);				//��Ӽ����¼�
	}

	return slider;
}

/*****************
* ��������:����ͨ�õ�֡�ʸ�ѡ��
* ��������:Vec2 posn:λ��
*          int tag:��Ӧ��ǩ
* ����ֵ  :ָ��ѡ���ָ��
*****************/
CheckBox* SETTINGSScene::createRateCheckbox(Vec2 pos, const CheckBox::ccCheckBoxCallback& callback)
{
	auto checkbox = CheckBox::create(pic_RCB_NOR_path,
		pic_RCB_RRE_path,
		pic_RCBNODE_path,
		pic_RCB_DIS_path,
		pic_RCBNODE_DIS_path);//����ͨ�ø�ѡ��

	if (checkbox == nullptr) {
		problemLoading("");
	}
	else {
		checkbox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);			//����ê��
		checkbox->setPosition(pos);									//����λ��
		checkbox->addEventListener(callback);						//��Ӽ����¼�
	}

	return checkbox;
}

/*****************
* ��������:����ͨ�õı�ǩ
* ��������:std::string& text:�ı�����
* ����ֵ  :ָ���ǩ��ָ��
*****************/
Label* SETTINGSScene::createMyLabel(std::string& text,Vec2 pos)
{
	auto label = Label::createWithTTF(text, "fonts/Genshin.ttf", 24);	//������ǩ
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);					//����ê��
	label->setPosition(pos);											//����λ��

	return label;
}

/*****************
* ��������:�����˳���ť
* ��������:Vec2 pos:λ��
* ����ֵ  :ָ��ť��ָ��
*****************/
Button* SETTINGSScene::createCloseBtn(Vec2 pos, const Button::ccWidgetClickCallback& callback)
{
	auto button = Button::create(pic_CLOSE_NOR_path, pic_CLOSE_SEL_path);	//������ť

	if (button == nullptr) {
		problemLoading("");
	}
	else {
		button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);						//����ê��
		button->setPosition(pos);											//����λ��
		button->addClickEventListener(callback);							//��Ӽ����¼�
	}

	return button;
}

/*****************
* ��������:���ֻ������ص�����
* ��������:Ref* pSender
* ����ֵ  :��
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
* ��������:Ƶ�ʸ�ѡ��ص�����
* ��������:Ref* pSender
* ����ֵ  :��
*****************/
void SETTINGSScene::rateCheckboxCallBack(Ref* pSender)
{
	if (pSender == nullptr) {
		return;
	}
	/* ��ȡѡ�и�ѡ������ */
	int tag = dynamic_cast<CheckBox*>(pSender)->getTag();
	/* �Ƚ����и�ѡ����Ϊδѡ */
	for (int i = 0; i < NUM_RCB; i++) {
		_rateCheckBox[i]->setSelected(false);
	}
	/* ��ѡ�и�ѡ����Ϊ��ѡ */
	_rateCheckBox[tag]->setSelected(true);
	///* �л���Ӧ��֡�� */
	//auto director = Director::getInstance();
	//director->setAnimationInterval(1.0f / 40 + tag * 10);

	return;

}

/*****************
* ��������:�رհ�ť�ص�����
* ��������:Ref* pSender
* ����ֵ  :��
*****************/
void SETTINGSScene::closeCallBack(Ref* pSender)
{
	auto director = Director::getInstance();
	director->popScene();

	return;
}
