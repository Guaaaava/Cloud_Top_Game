#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

// �����ֱ���
#define WORDS_GAME_NAME 1001	// �������֮ս������
#define WORDS_START     1002	// ����ʼ������
#define WORDS_SHOP      1003	// ���̵ꡱ����
#define WORDS_EXIT      1004	// ���˳�������
#define WORDS_LEVELUP	1005	// ������������
#define WORDS_REFRESH	1006	// "ˢ�¡�����
#define WORDS_LEVEL_1	1007	// ����������
#define WORDS_LEVEL_2	1008	// "���飺"����
#define WORDS_MONEY		1009	// "��ң�"����
#define WORDS_SELL		1010	// �����ۡ�����

// ͼƬ·�����룬�±��1��ʼ
const int MAX_NUM_KEY = 10;
const int PATH_NORMAL[MAX_NUM_KEY + 5] = { 0x3f3f3f3f, 1,2,3,4,5,6,7,8,9,10 };
const int PATH_SELECTED[MAX_NUM_KEY + 5] = { -0x3f3f3f3f, -1,-2,-3,-4,-5,-6,-7,-8,-9,-10 };
const int PATH_DISABLED[MAX_NUM_KEY + 5] = { 0x3f3f3f3f, -111, -222, -333, -444, -555, -666, -777, -888, -999, -101010 };

/****************************************************
 * ���ܣ������ļ���������ʵ�ֶ�ȡ�ͻ��������ļ�����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��7��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class ConfigController
{
public:
	static ConfigController* getInstance();
	static void destroyInstance();
	~ConfigController();

	// ͨ����Ż�ȡָ������
	std::string getCNByID(int id);

	// ͨ����Ż�ȡ�ƿ�ͼƬ·��
	std::string getPathByID(int id);

private:
	static ConfigController* instance;

	// ��¼���ֱ��������ݣ�
	std::map<int, Value> prt_cnWords;

	// ��¼�ƿ�ͼƬ·��
	std::map<int, Value> prt_picPath;
};

