//#pragma once
//
///**************
//* ����:������ͷ�ļ�
//* ����:�����
//* ʱ��:2023��12��28��
//**************/
//
//#include"cocos2d.h"
//USING_NS_CC;
//
//#define WAR 1	//սʿ
//#define AD 2	//����
//#define MT 3	//���
///* ���ӻ��� */
//class Hero :public Sprite
//{
//protected:
//	int _HP = -1;	//Ѫ��
//	int _MP = -1;	//����
//	int _ATK = -1;	//������
//	int _DEF = -1;	//������
//	int _RNG = -1;	//��������
//	int _SPD = -1;	//�ƶ��ٶ�
//	int _BD = -1;	//�����
//	Command pos;	//��¼�������ڵ���λ��
//public:
//	Command getPos();									//��ȡ�������ڵ���λ��
//	Command setPos(Command& pos);						//�����������ڵ���λ��
//    static Sprite* create(std::string& filePath);		//��������
//	virtual bool init();								//��ʼ������
//	inline bool isDead() const;							//�ж�Ӣ���Ƿ������ĺ���
//	MoveBy* moveBy(int time, Vec2 dir);					//�ƶ�����(����ƶ�)
//	MoveTo* moveTo(int time, Vec2 pos);					//�ƶ�����(�����ƶ�)
//	void attack(Hero* enemy) const;						//��������
//	void beAttack(int atk);								//����������
//
//	virtual void Ulti() = 0;							//���ܺ���(���麯��)
//	virtual void dead() = 0;							//��������(���麯��)
//};
//
//
//#define Annie_HP 100		//����Ѫ��ֵ�Ķ���
//#define Annie_MP 100		//��������ֵ�Ķ���
//#define Annie_ATK 10		//���ݹ���ֵ�Ķ���
//#define Annie_DEF 1			//���ݷ���ֵ�Ķ���
//#define Annie_RNG 3			//�������ֵ�Ķ���
//#define Annie_SPD 1			//��������ֵ�Ķ���
//#define Annie_BD SHOOTER	//�����Ķ���
///* Ӣ��1������ */
//class Annie :public Hero
//{
//public:
//	Annie();//���캯��
//
//
//};