#include"GameHead.h"
using namespace cocos2d;

bool e_isAtkCoolDown;

bool LaneTower::init() {

	
	m_iHP = Tower_iHP;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;
	e_isAtkCoolDown = false;
	
	return true;
}
int LaneTower::getID(){
	return Tower_ID;
}

void LaneTower::onDead(int i, vector<Entity*> ETT_ptr) {

	extern int goldenCoin;
	extern int power;
	goldenCoin += 60;
	power += 60;
	extern vector<Entity*> eETT_ptr;
	eETT_ptr.erase(eETT_ptr.begin() + i);
	this->removeFromParent();
}

void LaneTower::atkCoolDownEnd(float dt) {
	e_isAtkCoolDown = false;
}

