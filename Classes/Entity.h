#ifndef _Entity_H_
#define _Entity_H_

#include"GameHead.h"

using namespace cocos2d;

class Hero;
class Controller1;
//class ControllerListener;

class Entity :public ControllerListener{
public:
	Entity();
	~Entity();

    void bindSprite(Sprite* sprite);

	void setController(Controller1* controller);

	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();
	
	Sprite* getSprite();

	//被攻击
	void hurtMe(int iHurtValue);
	//是否死亡
	bool isDead();
protected:
	//实体死亡时调用
	virtual void onDead();
	//绑定精灵时调用
	virtual void onBindSprite();
	//受伤害时调用
	virtual void onHurt();
protected:
    Sprite* m_sprite;
	Controller1* m_controller;
	

	
	CC_SYNTHESIZE(int, m_ID, ID);              //实体ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);//模型ID
	CC_SYNTHESIZE(std::string, m_sName, sName);//名字
	CC_SYNTHESIZE(int, m_iHP, iHP);            //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);  //防御
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);      //移速
	CC_SYNTHESIZE(int, m_iLevel, iLevel);      //等级
	bool m_isDead;                             //标记是否死亡
	
};

#endif