#include "CTGScene.h"
#include "Shop.h"
#include "GameController.h"

#include <iostream>

/****************************************************
 * ���ܣ���ʼ���̵꣬��ʼ���ɹ�����true����֮����false
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool Shop::init()
{
    bool ret = true;

    money = 0, expr = 0, level = 0; // ��ʼ��
    for (int i = 0; i < NUM_CHESS_SHOP + 5; i++)
        chessButton[i] = nullptr;
    
    createLevelUpButton();          // ������ť
    createRefreshShopButton();      // ˢ���̵갴ť

    createLevelLabel();             // ����ֵ��ǩ
    createMoneyLabel();             // ��ұ�ǩ

    initAllChess();                 // ��ʼ���ƿ�

    createInitChessButton();        // ��ʼ�Ŀ��ư�ť
    getChessPrice();                // ��ȡ��ǰ���Ƽ۸�

    // ���°�ť����״̬
    updateButtonState();

    return ret;
}

/****************************************************
 * ���ܣ���ʼ���ƿ⣨Hero������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::initAllChess()
{
    for (int i = 1; i <= NUM_CHESS; i++)
    {
        if (i <= 5)
            allChess[i] = 1;
        else if (i > 5 && i <= 8)
            allChess[i] = 2;
        else
            allChess[i] = 3;
    }
}

/****************************************************
 * ���ܣ���ȡ��ǰ���Ƽ۸񣨴�Hero��get��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::getChessPrice()
{
    for (int i = 1; i <= NUM_CHESS_SHOP; i++)
    {
        chessPrice[i] = chess[i];
    }
}

/****************************************************
 * ���ܣ�����ͨ�õĿ��ư�ť
 * ������Ӣ��λ�ã�Ӣ�۱��
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createChessButton(int numOfChess, int index)
{
    if (numOfChess <= 0 || numOfChess > NUM_CHESS_SHOP)
    {
        CCLOG("λ�ò���1~%d�У��������ư�ťʧ��(Shop.cpp)\n", NUM_CHESS_SHOP);
        return;
    }

    if (index <= 0 || index > NUM_CHESS)
    {
        CCLOG("Ӣ�۱�Ų���1~%d�У��������ư�ťʧ��(Shop.cpp)\n", NUM_CHESS);
        return;
    }

    std::string normalPicPath = ConfigController::getInstance()->getPathByID(PATH_NORMAL[index]);
    std::string selectedPicPath = ConfigController::getInstance()->getPathByID(PATH_SELECTED[index]);
    std::string disabledPicPath = ConfigController::getInstance()->getPathByID(PATH_DISABLED[index]);

    chessButton[numOfChess] = Button::create(normalPicPath, selectedPicPath, disabledPicPath);  // ������ť

    // ʹ��lambda����ʽ��ȷ����ȷ����numOfChess��index
    chessButton[numOfChess]->addTouchEventListener([&, numOfChess, index](Ref* sender, Widget::TouchEventType type)  // �ص�����
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                // ���°�ť����¼�
                chessButton[numOfChess]->removeFromParentAndCleanup(true);
                chessButton[numOfChess] = nullptr;

                // ���ѽ�ң���Hero��get��
                money -= allChess[index];

                // ���°�ť����״̬
                updateButtonState();

                // ���½�ұ�ǩ
                labelMoney->setString(getMoneyLabelStr());

                // ������������Ӣ��

                break;
            default:
                break;
            }
        });
}

/****************************************************
 * ���ܣ���ʼ�Ŀ��ư�ť
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createInitChessButton()
{
    // �������������
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> u1(1, 100);  // ģ�����
    std::uniform_int_distribution<int> u2(1, 100);  // ��ʵ�±�
    randomEngine.seed(time(0));

    // ��ʼ���̵�
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // ���������
        int r1 = u1(randomEngine);
        int r2 = 1;

        // ���ݵȼ���������
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // �������
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // ǰ5����1��
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8��2��
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10��3��

        // ���������볡����
        chess[num] = allChess[r2];
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z ֵΪ 2

        // ��ʾ��ť
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// ����λ��
    }
}

/****************************************************
 * ���ܣ�������ť z ֵΪ 3
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createLevelUpButton()
{
    std::string normalPicPath = "NormalLevelUpButton.png";	// δ��ѡ��ʱ��ť��ʽ
    std::string selectedPicPath = "SelectedLevelUpButton.png";	// ��ѡ��ʱ��ť��ʽ
    std::string disabledPicPath = "DisabledLevelUpButton.png";  // ������ʱ��ť��ʽ
    buttonLevelUp = Button::create(normalPicPath, selectedPicPath, disabledPicPath);// ������ť
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);	// ��ȡ���ġ�������
    buttonLevelUp->setTitleText(words);						// ���ð�ť����
    buttonLevelUp->setTitleFontName("fonts/simkai.ttf");	// ��������
    buttonLevelUp->setTitleFontSize(24.0f);					// �����ֺ�
    buttonLevelUp->setTitleColor(Color3B::BLACK);			// ������ɫ
    buttonLevelUp->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f));	// ����λ��

    CTGScene::getLayer()->addChild(buttonLevelUp, 2);						// ��ť z ֵΪ 2

    // ʹ��lambda����ʽ�����÷�ʽ�����ⲿ����
    buttonLevelUp->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // �ص�����
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - MONEY_ADD_EXP >= 0)     // ���Ǯ����������
                {
                    money -= MONEY_ADD_EXP; // ���ѽ��
                    expr += EXP_ADD_ONCE;   // �Ӿ���
                    transformExpToLevel();  // ת��Ϊ�ȼ�

                    // ���°�ť����״̬
                    updateButtonState();

                    labelMoney->setString(getMoneyLabelStr());
                    labelLevel->setString(getLevelLabelStr());  // ���±�ǩ

                    // ���ݵȼ����ӿ��ϳ�Ӣ����
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * ���ܣ�ˢ���̵갴ť z ֵΪ 3
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createRefreshShopButton()
{
    std::string normalPicPath = "NormalRefreshShopButton.png";		// δ��ѡ��ʱ��ť��ʽ
    std::string selectedPicPath = "SelectedRefreshShopButton.png";	// ��ѡ��ʱ��ť��ʽ
    std::string disabledPicPath = "DisabledRefreshShopButton.png";  // ������ʱ��ť��ʽ
    buttonRefreshShop = Button::create(normalPicPath, selectedPicPath, disabledPicPath);    // ������ť
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_REFRESH);	// ��ȡ���ġ�ˢ�¡�
    buttonRefreshShop->setTitleText(words);						// ���ð�ť����
    buttonRefreshShop->setTitleFontName("fonts/simkai.ttf");	// ��������
    buttonRefreshShop->setTitleFontSize(24.0f);					// �����ֺ�
    buttonRefreshShop->setTitleColor(Color3B::BLACK);			// ������ɫ
    buttonRefreshShop->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.25f));	// ����λ��

    CTGScene::getLayer()->addChild(buttonRefreshShop, 2);						// ��ť z ֵΪ 2

    // ʹ��lambda����ʽ�����÷�ʽ�����ⲿ����
    buttonRefreshShop->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // �ص�����
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - REFRESH_ONCE >= 0)
                {
                    money -= REFRESH_ONCE;   // ���ѽ��
                    // ���ݵȼ�ˢ���̵�
                    refreshShop();

                    // ���¼۸�
                    getChessPrice();

                    // ���°�ť����״̬
                    updateButtonState();

                    labelMoney->setString(getMoneyLabelStr());     // ���±�ǩ
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * ���ܣ�����ֵ��ǩ
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createLevelLabel()
{
    std::string backgroundPicPath = "LevelLabelBackGround.png";
    spriteLevelLabel = Sprite::create(backgroundPicPath);
    spriteLevelLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.75f));
    CTGScene::getLayer()->addChild(spriteLevelLabel, 2);    // z ֵΪ 2

    // ��ǩ������ 
    //               2��
    //            ��ǰ��4/10
    std::string words = getLevelLabelStr();
    labelLevel = Label::createWithTTF(words, "fonts/simkai.ttf", 24.0f);
    labelLevel->setPosition(spriteLevelLabel->getPosition());
    labelLevel->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelLevel, 3);      // z ֵΪ 3
}

/****************************************************
 * ���ܣ���ұ�ǩ
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createMoneyLabel()
{
    std::string backgroundPicPath = "MoneyLabelBackGround.png";
    spriteMoneyLabel = Sprite::create(backgroundPicPath);
    spriteMoneyLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.25f));
    CTGScene::getLayer()->addChild(spriteMoneyLabel, 2);    // z ֵΪ 2

    // ��ǩ������ 
    //               ��ң�10
    std::string words = getMoneyLabelStr();
    labelMoney = Label::createWithTTF(words, "fonts/simkai.ttf", 32.0f);
    labelMoney->setPosition(spriteMoneyLabel->getPosition());
    labelMoney->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelMoney, 3);      // z ֵΪ 3
}

/****************************************************
 * ���ܣ���ȡ�����ҵ�numofChess�ſ�������λ��
 * �����������ҵڼ��ſ��ƣ�ע�ⲻҪ����NUM_CHESS_SHOP
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
Vec2 Shop::getChessPosition(const int numofChess)
{
    if (numofChess > NUM_CHESS_SHOP)
    {
        // ��־����ͨ���ض���鿴
        CCLOG("��%d�ſ��Ƴ����̵꿨������%d��λ�ø�������Shop.cpp��\n", numofChess, NUM_CHESS_SHOP);
        return Vec2(0, 0);
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 position = origin;

    const float chessMiddle_x = shopStart_x + (numofChess - 1) * chessWidth + chessWidth / 2.0f;
    position = origin + Vec2(chessMiddle_x, SHOP_HEIGHT / 2.0f);

    return position;
}

/****************************************************
 * ���ܣ��õ��ȼ���ǩ���º������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
std::string Shop::getLevelLabelStr()
{
    std::string words = "";

    // ��ǩ������ 
    //               2��
    //            ��ǰ��4/10
    std::string words_1 = "";
    std::string words_2 = "";
    std::string words_3 = "";

    words_1 += ('0' + level);

    if (expr >= 10) words_2 += ('0' + expr / 10);
    words_2 += ('0' + expr % 10);

    if (EXP_LEVEL[level + 1] >= 10) words_3 += ('0' + EXP_LEVEL[level + 1] / 10);
    words_3 += ('0' + EXP_LEVEL[level + 1] % 10);

    words = "    " + words_1 + words_level_1 + "\n" + words_level_2 + words_2 + "/" + words_3;

    return words;
}

/****************************************************
 * ���ܣ��õ���ұ�ǩ���º������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
std::string Shop::getMoneyLabelStr()
{
    std::string words = "";

    // ��ǩ������ 
    //               ��ң�10
    std::string words_1 = "";

    // ���������999
    if (money >= 100) words_1 += ('0' + money / 100);
    if (money >= 10) words_1 += ('0' + (money % 100) / 10);
    words_1 += ('0' + money % 10);

    words = words_money + words_1;

    return words;
}

/****************************************************
 * ���ܣ�������ת��Ϊ�ȼ�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::transformExpToLevel()
{
    for (int lev = MAX_LEVEL; lev >= level + 1; lev--)
    {
        if (expr >= EXP_LEVEL[lev])
        {
            level = lev;
            expr -= EXP_LEVEL[lev];
            break;
        }
    }
}

/****************************************************
 * ���ܣ����ݵȼ�ˢ���̵�
 * ע�⣺ֻ�����̵����п��Ƶ������ˢ�£�����ˢ�µ�ͬʱ��
 *      �Ӳ����Ƴ����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::refreshShop()
{
    if (chessButton == nullptr)
    {
        CCLOG("��ʼ��ʱ����ʹ��ˢ���̵꺯����(shop.cpp)");
        return;
    }

    // �������������
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> u1(1, 100);  // ģ�����
    std::uniform_int_distribution<int> u2(1, 100);  // ��ʵ�±�
    randomEngine.seed(time(0));

    // ˢ���̵�
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // ���������
        int r1 = u1(randomEngine);
        int r2 = 1;

        // ���ݵȼ���������
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // �������
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // ǰ5����1��
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8��2��
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10��3��

        // �Ƴ�ԭ��ť�����Ƴ��ٸ��£�����
        if (chessButton[num] != nullptr)
        {
            chessButton[num]->removeFromParentAndCleanup(true);
            chessButton[num] = nullptr;
        }

        // �����̵꿨�ƺͿ��ư�ť�����볡����
        chess[num] = allChess[r2];
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z ֵΪ 2

        // ���ݸ��º�����鴴����ť
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// ����λ��
    }
}

/****************************************************
 * ���ܣ����°�ť����״̬���������ڻص������У�����
 * ע�⣺ÿ�λ�Ǯ�Ժ�Ҫ���и���
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::updateButtonState()
{
    if (buttonLevelUp == nullptr || buttonRefreshShop == nullptr)
        return;

    // ������ť
    if (level == MAX_LEVEL || money - EXP_ADD_ONCE < 0) // ������ûǮ
        buttonLevelUp->setEnabled(false);   // ���ð�ť
    else
        buttonLevelUp->setEnabled(true);

    // ˢ���̵갴ť
    if (money - REFRESH_ONCE < 0)   // ûǮ
        buttonRefreshShop->setEnabled(false);   // ���ð�ť
    else
        buttonRefreshShop->setEnabled(true);

    // ���ư�ť
    for (int i = 1; i <= NUM_CHESS_SHOP; i++)   // �����ĸ�Ӣ������
    {
        if (money - chessPrice[i] < 0)  // ��i�ſ�������
        {
            if (chessButton[i] != nullptr)
                chessButton[i]->setEnabled(false);  // ���ý���
        }
        else
        {
            if (chessButton[i] != nullptr)
                chessButton[i]->setEnabled(true);
        }
    }
}