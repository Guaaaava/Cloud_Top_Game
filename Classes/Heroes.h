//#pragma once
//
///**************
//* 功能:弈子类头文件
//* 作者:尹泽河
//* 时间:2023年12月28日
//**************/
//
//#include"cocos2d.h"
//USING_NS_CC;
//
//#define WAR 1	//战士
//#define AD 2	//射手
//#define MT 3	//肉盾
///* 奕子基类 */
//class Hero :public Sprite
//{
//protected:
//	int _HP = -1;	//血量
//	int _MP = -1;	//蓝量
//	int _ATK = -1;	//攻击力
//	int _DEF = -1;	//防御力
//	int _RNG = -1;	//攻击距离
//	int _SPD = -1;	//移动速度
//	int _BD = -1;	//所属羁绊
//	Command pos;	//记录奕子所在点阵位置
//public:
//	Command getPos();									//获取奕子所在点阵位置
//	Command setPos(Command& pos);						//设置奕子所在点阵位置
//    static Sprite* create(std::string& filePath);		//创建函数
//	virtual bool init();								//初始化函数
//	inline bool isDead() const;							//判断英雄是否死亡的函数
//	MoveBy* moveBy(int time, Vec2 dir);					//移动函数(相对移动)
//	MoveTo* moveTo(int time, Vec2 pos);					//移动函数(绝对移动)
//	void attack(Hero* enemy) const;						//攻击函数
//	void beAttack(int atk);								//被攻击函数
//
//	virtual void Ulti() = 0;							//技能函数(纯虚函数)
//	virtual void dead() = 0;							//死亡函数(纯虚函数)
//};
//
//
//#define Annie_HP 100		//安妮血量值的定义
//#define Annie_MP 100		//安妮蓝量值的定义
//#define Annie_ATK 10		//安妮攻击值的定义
//#define Annie_DEF 1			//安妮防御值的定义
//#define Annie_RNG 3			//安妮射程值的定义
//#define Annie_SPD 1			//安妮移速值的定义
//#define Annie_BD SHOOTER	//安妮羁绊的定义
///* 英雄1派生类 */
//class Annie :public Hero
//{
//public:
//	Annie();//构造函数
//
//
//};