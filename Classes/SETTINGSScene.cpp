#include "SETTINGSScene.h"

USING_NS_CC;

cocos2d::Scene* SETTINGSScene::createScene()
{
    return SETTINGSScene::create();
}

static void problemLoading(const char* fileName)
{
    printf("Error while loading: %s\n", fileName);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in startScene.cpp\n");
}

bool SETTINGSScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _background = createBackground(origin + visibleSize / 2);
    if (_background == nullptr) {
        problemLoading("");
    }
    else {
        this->addChild(_background);
    }

    return true;
}

Sprite* SETTINGSScene::createBackground(Vec2 pos)
{
    auto sprite = Sprite::create(pic_BG_path);
    if (sprite == nullptr) {
        problemLoading("");
    }
    else {
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        sprite->setPosition(pos);

        Vec2 pos_MS = sprite->getPosition() + Vec2(0, 50);
        _musicSlider = createMusicSlider(pos_MS, CC_CALLBACK_1(SETTINGSScene::musicSliderCallBack, this));
        sprite->addChild(_musicSlider);

        std::string name_M = ConfigController::getInstance()->getCNByID(WORDS_MUSIC_VOLUME);
        auto label_MS = createLabel(name_M, pos_MS + Vec2(-120 - _musicSlider->getContentSize().width / 2, 0));
        sprite->addChild(label_MS);

        const std::string name_RCB[NUM_RCB] = {
            ConfigController::getInstance()->getCNByID(WORDS_IMAGE_LOW),
            ConfigController::getInstance()->getCNByID(WORDS_IMAGE_MID),
            ConfigController::getInstance()->getCNByID(WORDS_IMAGE_HIG)
        };

        for (int i = 0; i < NUM_RCB; i++) {
            Vec2 pos_Label_R = pos_MS - _musicSlider->getContentSize() / 2 + Vec2(i * 100, -50);
            auto label = createLabel(name_RCB[i], pos_Label_R);
            sprite->addChild(label);

            Vec2 pos_RCB = label->getPosition() + Vec2(40, 0);
            _rateCheckBox[i] = createRateCheckbox(pos_RCB, CC_CALLBACK_1(SETTINGSScene::rateCheckboxCallBack, this));
            _rateCheckBox[i]->setTag(i);
            sprite->addChild(_rateCheckBox[i]);
        }

        std::string name_R = ConfigController::getInstance()->getCNByID(WORDS_IMAGE_QULITY);
        auto label_RCB = createLabel(name_R, pos_Label_R + Vec2(-120, 0));
        sprite->addChild(label_RCB);

        _close = createButton(pic_CLOSE_NOR_path, pic_CLOSE_SEL_path, pos + Vec2(260, 125), CC_CALLBACK_1(SETTINGSScene::closeCallBack, this));
        sprite->addChild(_close);
    }

    return sprite;
}

Slider* SETTINGSScene::createMusicSlider(Vec2 pos, const Slider::ccSliderCallback& callback)
{
    auto slider = Slider::create(pic_MS_BK_path, pic_MS_NODE_path, pic_MS_PB_path);
    if (slider ==nullptr) {
        problemLoading("");
    }
    else {
        slider->setPercent(50);
        slider->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        slider->setPosition(pos);
        slider->addEventListener(callback);
    }
    slider->addEventListener(CC_CALLBACK_1(SETTINGSScene::musicSliderCallBack, this));
    return slider;
}

CheckBox* SETTINGSScene::createRateCheckbox(Vec2 pos, const CheckBox::ccCheckBoxCallback& callback)
{
    auto checkbox = CheckBox::create(pic_RCB_NOR_path, pic_RCB_RRE_path, pic_RCBNODE_path, pic_RCB_DIS_path, pic_RCBNODE_DIS_path);
    if (checkbox == nullptr) {
        problemLoading("");
    }
    else {
        checkbox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        checkbox->setPosition(pos);
        checkbox->addEventListener(callback);
    }
    return checkbox;
}

Label* SETTINGSScene::createLabel(const std::string& text, Vec2 pos)
{
    auto label = Label::createWithTTF(text, "fonts/Genshin.ttf", 24);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    label->setPosition(pos);
    return label;
}

Button* SETTINGSScene::createButton(const std::string& normalImage, 
    const std::string& selectedImage, Vec2 pos, const Button::ccWidgetClickCallback& callback)
{
    auto button = Button::create(normalImage, selectedImage);
    if (button == nullptr) {
        problemLoading("");
    }
    else {
        button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
        button->setPosition(pos);
        button->addClickEventListener(callback);
    }
    return button;
}

void SETTINGSScene::musicSliderCallBack(Ref* pSender)
{
    Slider* slider = dynamic_cast<Slider*>(pSender);
    if (slider != nullptr) {
        int per = slider->getPercent();
        auto audioEngine = SimpleAudioEngine::getInstance();
        audioEngine->setBackgroundMusicVolume(0);
    }
}

void SETTINGSScene::rateCheckboxCallBack(Ref* pSender)
{
    if (pSender == nullptr) {
        return;
    }

    int tag = dynamic_cast<CheckBox*>(pSender)->getTag();

    for (int i = 0; i < NUM_RCB; i++) {
        _rateCheckBox[i]->setSelected(i == tag);
    }
}

void SETTINGSScene::closeCallBack(Ref* pSender)
{
    auto director = Director::getInstance();
    director->popScene();
}