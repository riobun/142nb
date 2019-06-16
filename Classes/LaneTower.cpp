
#include "GameHead.h"
using namespace cocos2d;

	bool LaneTower::init() {

	
	m_iHP = Tower_iHP;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;
	
	return true;
}
int LaneTower::getID(){
	return Tower_ID;
}

void LaneTower::onDead(int i) {

	extern double goldenCoin;
	extern double power;
	goldenCoin += 60;
	power += 60;
	CCLOG("%f", goldenCoin);

	extern vector<Entity*> eETT_ptr;
	eETT_ptr.erase(eETT_ptr.begin() + i);
	this->removeFromParent();
	extern LaneTower* e_laneTower;
	e_laneTower = nullptr;
}

void LaneTower::atkCoolDownEnd(float dt) {
	extern bool e_isAtkCoolDown;
	e_isAtkCoolDown = false;
}

