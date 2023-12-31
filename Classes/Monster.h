#pragma once
#include<list>
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Monster :public Sprite
{
public:
	//英雄选择动作核心逻辑
	void monsterAction();
	//升lv级
	void upLevel(int lv) { _lv += lv; _hp *= _lv; _ap *= _lv; };
	//每回合减少的血量
	void getHurted() {
		for (std::list<Monster*>::iterator iter = _l.begin(); iter != _l.end(); iter++)
		{
			if ((*iter)->_hp > 0)
			{
				if ((*iter)->_mp >= (*iter)->_max_mp)
					_enemy_ap += (*iter)->_skill_ap;
				else
					_enemy_ap += (*iter)->_ap;
			}
		}
		_hp -= _enemy_ap;
	};
	//获取敌人信息
	void getEnemyInfor(std::list<Monster*>l) { _l = l; };
	//创建plist帧动画
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	//初始化人物属性，以及坐标start_pos（默认坐标为屏幕中央）
	virtual bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2)) = 0;
	//前往敌人坐标并执行接下来的一系列动作
	virtual void monsterRunToEnemyPos(Vec2& end_pos) = 0;
	//实现英雄攻击动画
	virtual void monsterAttack() = 0;
	//实现英雄死亡动画
	virtual void monsterDead() = 0;

protected:
	double _enemy_ap = 0;
	bool _reverse = false;//移动时是否翻转
	Vec2 _postion;//当前位置
	double _hp;
	double _ap;
	double _mp;
	int _lv;
	double _max_mp;
	double _skill_ap;
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	std::list<Monster*>_l;
};

class BlackWerewolf :public Monster
{
public:
	CREATE_FUNC(BlackWerewolf);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};

class SkeletonWarrior :public Monster
{
public:
	CREATE_FUNC(SkeletonWarrior);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};
class BlueSlime :public Monster
{
public:
	CREATE_FUNC(BlueSlime);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};
