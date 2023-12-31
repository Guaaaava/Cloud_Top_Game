#pragma once
#include<list>
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	//英雄选择动作核心逻辑
	void heroAction();
	//升lv级
	void upLevel(int lv) { _lv += lv; _hp *= _lv; _ap *= _lv;  _max_hp = _hp; };
	//每回合减少的血量
	void getHurted() {
		for (std::list<Hero*>::iterator iter = _l.begin(); iter != _l.end(); iter++)
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
	void getEnemyInfor(std::list<Hero*>l) { _l = l; };
	//创建plist帧动画
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	//初始化人物属性，以及坐标start_pos（默认坐标为屏幕中央）
	virtual bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2)) = 0;
	//前往敌人坐标并执行接下来的一系列动作
	virtual void heroRunToEnemyPos(Vec2& end_pos) = 0;
	//实现英雄攻击动画
	virtual void heroAttack() = 0;
	//实现英雄死亡动画
	virtual void heroDead() = 0;
	//移动到某一点并攻击
	virtual void heroSkill() = 0;
	// 创建头顶血条
	void createHealthBar();
	// 更新头顶血条位置
	void updateHealthBarPosition();
	// 更新头顶血条显示
	//void updateHealthBarDisplay();
	void updateHealthBar(float dt);
	// 创建头顶蓝条
	void createMagicBar();
	// 更新头顶蓝条位置
	void updateMagicBarPosition();
	// 更新头顶蓝条显示
	void updateMagicBar(float dt);

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
	Animation* _skill;
	std::list<Hero*>_l;
	ProgressTimer* _healthBar;  // 头顶血条
	ProgressTimer* _magicBar;  // 头顶蓝条
	double _max_hp;
};

class Samurai :public Hero
{
public:
	CREATE_FUNC(Samurai);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class Berserker :public Hero
{
public:
	CREATE_FUNC(Berserker);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class Kunoichi :public Hero
{
public:
	CREATE_FUNC(Kunoichi);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();

};

class LightningMage :public Hero
{
public:
	CREATE_FUNC(LightningMage);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class FireVizard :public Hero
{
public:
	CREATE_FUNC(FireVizard);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class WandererMagican :public Hero
{
public:
	CREATE_FUNC(WandererMagican);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();


};
class NinjaMonk :public Hero
{
public:
	CREATE_FUNC(NinjaMonk);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class NinjaPeasant :public Hero
{
public:
	CREATE_FUNC(NinjaPeasant);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class SamuraiCommander :public Hero
{
public:
	CREATE_FUNC(SamuraiCommander);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};