#include "ConfigController.h"

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
}

std::string ConfigController::getCNByID(int id)
{
	// �������Ϊ�գ���ȡ�����ļ�����Ϊ������Ҫ��ȡ
	if (prt_cnWords.empty())
	{
		// ��ȡ������plist�����ļ�����ֹ��������
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
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
