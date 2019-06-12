#include"GameHead.h"
using namespace cocos2d;

bool Crystal::init() {


	m_iHP = Crystal_iHP;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;

	return true;
}
int Crystal::getID() {
	return Crystal_ID;
}