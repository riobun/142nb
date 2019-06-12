#include"GameHead.h"
using namespace cocos2d;

bool Hero::init() {
	return true;
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