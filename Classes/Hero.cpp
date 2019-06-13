#include"GameHead.h"
using namespace cocos2d;

bool Hero::init() {

	m_iHP = Ashe_iHP;
	m_iDefense = Ashe_iDenfense;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;

	return true;
}

int Hero::getID() {
	return Ashe_ID;
}

void Hero::WriteForCRC(OutputMemoryBitStream& inStream)
{
    inStream.Write(mPlayerId);
    inStream.Write(mNetworkId);
}

void Hero::run() {
	Animation *moveAct = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		__String *frameName = __String::createWithFormat("greenHero%d.png", i);
		log("frameName=%s", frameName->getCString());
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(frameName->getCString());
		moveAct->addSpriteFrame(spriteFrame);
	}

	moveAct->setDelayPerUnit(0.15f);
	moveAct->setRestoreOriginalFrame(true);
	Animate*action = Animate::create(moveAct);
	m_sprite->runAction(action);
	
}

void Hero::onDead(int i, vector<Entity*> ETT_ptr) {
	extern vector<Entity*> mETT_ptr;
	mETT_ptr.erase(mETT_ptr.begin() + i);
	this->removeFromParent();
}