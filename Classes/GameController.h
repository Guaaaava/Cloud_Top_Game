#pragma once

/****************************************************
 * ���ܣ���Ϸ�߼�������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��14��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
class GameController
{
public:
	static GameController* getInstance();
	static void destroyInstance();
	~GameController();

	// ��ս����


	// ʤ���ж�
	

private:
	static GameController* instance;
};