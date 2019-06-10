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