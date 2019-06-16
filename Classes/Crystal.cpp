#include"GameHead.h"
using namespace cocos2d;

bool Crystal::init() {


	m_iHP = Crystal_iHP;
	m_isDead = false;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;

	return true;
}
int Crystal::getID() {
	return Crystal_ID;
}

void Crystal::onDead(int i) {

	extern double goldenCoin;
	extern double power;
	goldenCoin += 60;
	power += 60;
	CCLOG("%f", goldenCoin);
	extern vector<Entity*> eETT_ptr;
	eETT_ptr.erase(eETT_ptr.begin() + i);
	this->removeFromParent();
	auto overSceneCreate = overScene::createScene();
    Director::getInstance()->replaceScene(overSceneCreate);

	extern Crystal* e_crystal;
	e_crystal = NULL;
}