#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

// �����ֱ���
#define WORDS_GAME_NAME 1001	// �������֮ս������
#define WORDS_GAME_START 1002	//����ʼ��Ϸ������
#define WORDS_GAME_CLOSE 1003	//���˳���Ϸ������
#define WORDS_TRAINING_MODE 1004//��ѵ��ģʽ������
#define WORDS_ONLINE_MODE 1005	//������ģʽ������
#define WORDS_MUSIC_VOLUME 1006 //��������С������
#define WORDS_IMAGE_QULITY 1007 //�����ʡ�����
#define WORDS_IMAGE_LOW 1008	//���͡�����
#define WORDS_IMAGE_MID 1009	//���С�����
#define WORDS_IMAGE_HIG 1010	//���ߡ�����
#define WORDS_LEVELUP	2001	// ������������
#define WORDS_REFRESH	2002	// "ˢ�¡�����
#define WORDS_LEVEL_1	2003	// ����������
#define WORDS_LEVEL_2	2004	// "���飺"����
#define WORDS_MONEY		2005	// "��ң�"����
#define WORDS_SELL		2006	// �����ۡ�����

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
