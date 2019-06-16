#include"GameHead.h"
using namespace cocos2d;
extern double PRI_SPEED;

bool Soilder::init() {

	m_iHP = Soilder_iHP;
	m_iDefense = Soilder_iDenfense;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mPlayerId = 0;

	return true;
}

int Soilder::getID() {
	return Soilder_ID;
}

void Soilder::WriteForCRC(OutputMemoryBitStream& inStream)
{
	inStream.Write(mPlayerId);
}

void Soilder::onDead(int i) {

	/*extern int goldenCoin;
	extern int power;
	goldenCoin += 5;
	power += 5;*/
	extern vector<Entity*> eETT_ptr;
	eETT_ptr.erase(eETT_ptr.begin() + i);
	this->removeFromParent();
}
/*void Soilder::run() {
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("greenHero.plist", "greenHero.png");
	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameList;

	for (int i = 1; i < 7; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("greenHero%d.png", i));
		frameList.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);
	Animate*animate = Animate::create(animation);

	m_sprite->runAction(animate);
	
}*/