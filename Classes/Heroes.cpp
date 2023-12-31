//#include "Heroes.h"
///**************
//* 功能:弈子类实现
//* 作者:尹泽河
//* 时间:2023年12月28日
//**************/
//
///*************
//* 函数参数:	文件路径
//* 函数功能:	创建一个新英雄
//* 返回值  :指向英雄的指针
//*************/
//Sprite* Hero::create(std::string& filePath)
//{
//	return Sprite::create(filePath);
//}
//
///*************
//* 函数参数:	无
//* 函数功能:	英雄的初始化
//* 返回值  :	true:初始化成功;
//*			false:初始化失败
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
//* 函数参数:	无
//* 函数功能:	判断英雄是否死亡
//* 返回值  :	true:英雄已经死亡;
//*			false:英雄还未死亡
//*************/
//inline bool Hero::isDead() const
//{
//	/* 血量小于0说明死亡 */
//	if (this->_HP <= 0) {
//		return true;
//	}
//
//	return false;
//}
//
///*************
//* 函数参数:	int time:移动时间:
//			Vec2 dir:移动的向量
//* 函数功能:	实现一个英雄的移动(相对位置)
//* 返回值  :	动作指针
//*************/
//MoveBy* Hero::moveBy(int time, Vec2 dir)
//{
//	/* 英雄存在且未死亡是移动前提 */
//	if ((this != nullptr) && (!this->isDead())) {
//		auto move = MoveBy::create(time, dir);
//		return move;
//	}
//
//	return nullptr;
//}
//
///*************
//* 函数参数:	int time:移动时间:
//			Vec2 pos:终点位置
//* 函数功能:	实现一个英雄的移动(绝对位置)
//* 返回值  :	动作指针
//*************/
//MoveTo* Hero::moveTo(int time, Vec2 pos)
//{
//	/* 英雄存在且未死亡是移动前提 */
//	if ((this != nullptr) && (!this->isDead())) {
//		auto move = MoveTo::create(time, pos);
//		return move;
//	}
//
//	return nullptr;
//}
//
///*************
//* 函数参数:	Heroes*enemy:攻击的敌方英雄
//* 函数功能:	实现英雄的攻击
//* 返回值  :	无
//*************/
//void Hero::attack(Hero* enemy) const
//{
//	/* 敌方英雄存在且未死亡是移动前提 */
//	if ((enemy != nullptr) && (!enemy->isDead())) {
//		enemy->beAttack(this->_ATK);
//	}
//
//	return;
//}
//
///*************
//* 函数参数:	int atk:受攻击的值
//* 函数功能:	实现一个英雄的受攻击
//* 返回值  :	无
//*************/
//void Hero::beAttack(int atk)
//{
//	/* 英雄存在且未死亡是受攻击前提 */
//	if ((this != nullptr) && (!this->isDead())) {
//		this->_HP -= atk - _DEF;
//	}
//
//	return;
//}
//
///*************
//* 函数参数:	无
//* 函数功能:	构造函数
//* 返回值  :	无
//*************/
//Annie::Annie()
//{
//
//}
