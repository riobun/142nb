// TurnData：轮数据，用于同步
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫，2019.06.04

#include "NetworkHead.h"

void TurnData::Write( OutputMemoryBitStream& inOutputStream )
{
	inOutputStream.Write( mPlayerId );
	inOutputStream.Write( mRandomValue );
	inOutputStream.Write( mCRC );
	mCommandList.Write( inOutputStream );
}

void TurnData::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mPlayerId );
	inInputStream.Read( mRandomValue );
	inInputStream.Read( mCRC );
	mCommandList.Read( inInputStream );
}
