#include "ConfigController.h"

/****************************************************
 * ���ܣ������ļ�������Ĭ�Ϻ���
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
ConfigController* ConfigController::instance = nullptr;
ConfigController* ConfigController::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ConfigController();
	}
	return instance;
}
void ConfigController::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
ConfigController::~ConfigController()
{
	prt_cnWords.clear();
	prt_picPath.clear();
	ConfigController::destroyInstance();
}

/****************************************************
 * ���ܣ�ͨ����Ż�ȡָ������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
std::string ConfigController::getCNByID(int id)
{
	// �������Ϊ�գ���ȡ�����ļ�����Ϊ������Ҫ��ȡ
	if (prt_cnWords.empty())
	{
		// ��ȡ������plist�����ļ�����ֹ��������
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/CNWords.plist");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();		// תΪ int
			Value val = mapPair.second;

			prt_cnWords.insert(std::pair<int, Value>(key, val));
		}
	}

	if (prt_cnWords.empty())
	{
		return "";
	}

	return prt_cnWords.at(id).asString();		// תΪ string
}

/****************************************************
 * ���ܣ�ͨ����Ż�ȡָ������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
std::string ConfigController::getPathByID(int id)
{
	// �������Ϊ�գ���ȡ�����ļ�����Ϊ������Ҫ��ȡ
	if (prt_picPath.empty())
	{
		// ��ȡͼƬ·��plist�����ļ�
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/PicPath.plist");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();		// תΪ int
			Value val = mapPair.second;

			prt_picPath.insert(std::pair<int, Value>(key, val));
		}
	}

	if (prt_picPath.empty())
	{
		return "";
	}

	return prt_picPath.at(id).asString();		// תΪ string
}