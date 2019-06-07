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

	//������
	void hurtMe(int iHurtValue);
	//�Ƿ�����
	bool isDead();
protected:
	//ʵ������ʱ����
	virtual void onDead();
	//�󶨾���ʱ����
	virtual void onBindSprite();
	//���˺�ʱ����
	virtual void onHurt();
protected:
    Sprite* m_sprite;
	Controller1* m_controller;
	

	
	CC_SYNTHESIZE(int, m_ID, ID);              //ʵ��ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);//ģ��ID
	CC_SYNTHESIZE(std::string, m_sName, sName);//����
	CC_SYNTHESIZE(int, m_iHP, iHP);            //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);  //����
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);      //����
	CC_SYNTHESIZE(int, m_iLevel, iLevel);      //�ȼ�
	bool m_isDead;                             //����Ƿ�����
	
};

#endif