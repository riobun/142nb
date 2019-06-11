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