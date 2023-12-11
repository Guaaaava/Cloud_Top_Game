#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// �൱�� using namespace cocos2d;

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

private:
	static ConfigController* instance;

	// ��¼���ֱ��������ݣ�
	std::map<int, Value> prt_cnWords;
};

