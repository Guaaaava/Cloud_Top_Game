//#include "Heroes.h"
///**************
//* ����:������ʵ��
//* ����:�����
//* ʱ��:2023��12��28��
//**************/
//
///*************
//* ��������:	�ļ�·��
//* ��������:	����һ����Ӣ��
//* ����ֵ  :ָ��Ӣ�۵�ָ��
//*************/
//Sprite* Hero::create(std::string& filePath)
//{
//	return Sprite::create(filePath);
//}
//
///*************
//* ��������:	��
//* ��������:	Ӣ�۵ĳ�ʼ��
//* ����ֵ  :	true:��ʼ���ɹ�;
//*			false:��ʼ��ʧ��
//*************/
//bool Hero::init()
//{
//	if (!Sprite::init()) {
//		return false;
//	}
//
//	return true;
//}
//
///*************
//* ��������:	��
//* ��������:	�ж�Ӣ���Ƿ�����
//* ����ֵ  :	true:Ӣ���Ѿ�����;
//*			false:Ӣ�ۻ�δ����
//*************/
//inline bool Hero::isDead() const
//{
//	/* Ѫ��С��0˵������ */
//	if (this->_HP <= 0) {
//		return true;
//	}
//
//	return false;
//}
//
///*************
//* ��������:	int time:�ƶ�ʱ��:
//			Vec2 dir:�ƶ�������
//* ��������:	ʵ��һ��Ӣ�۵��ƶ�(���λ��)
//* ����ֵ  :	����ָ��
//*************/
//MoveBy* Hero::moveBy(int time, Vec2 dir)
//{
//	/* Ӣ�۴�����δ�������ƶ�ǰ�� */
//	if ((this != nullptr) && (!this->isDead())) {
//		auto move = MoveBy::create(time, dir);
//		return move;
//	}
//
//	return nullptr;
//}
//
///*************
//* ��������:	int time:�ƶ�ʱ��:
//			Vec2 pos:�յ�λ��
//* ��������:	ʵ��һ��Ӣ�۵��ƶ�(����λ��)
//* ����ֵ  :	����ָ��
//*************/
//MoveTo* Hero::moveTo(int time, Vec2 pos)
//{
//	/* Ӣ�۴�����δ�������ƶ�ǰ�� */
//	if ((this != nullptr) && (!this->isDead())) {
//		auto move = MoveTo::create(time, pos);
//		return move;
//	}
//
//	return nullptr;
//}
//
///*************
//* ��������:	Heroes*enemy:�����ĵз�Ӣ��
//* ��������:	ʵ��Ӣ�۵Ĺ���
//* ����ֵ  :	��
//*************/
//void Hero::attack(Hero* enemy) const
//{
//	/* �з�Ӣ�۴�����δ�������ƶ�ǰ�� */
//	if ((enemy != nullptr) && (!enemy->isDead())) {
//		enemy->beAttack(this->_ATK);
//	}
//
//	return;
//}
//
///*************
//* ��������:	int atk:�ܹ�����ֵ
//* ��������:	ʵ��һ��Ӣ�۵��ܹ���
//* ����ֵ  :	��
//*************/
//void Hero::beAttack(int atk)
//{
//	/* Ӣ�۴�����δ�������ܹ���ǰ�� */
//	if ((this != nullptr) && (!this->isDead())) {
//		this->_HP -= atk - _DEF;
//	}
//
//	return;
//}
//
///*************
//* ��������:	��
//* ��������:	���캯��
//* ����ֵ  :	��
//*************/
//Annie::Annie()
//{
//
//}
