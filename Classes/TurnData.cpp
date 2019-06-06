// TurnData�������ݣ�����ͬ��
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ��2019.06.04

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
