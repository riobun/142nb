/* Command  �����д
  * ����ʾ����   AttackCommand, MoveCommand
  * ������Ҫʵ�ֵ��麯����
  *                          Read(), ProcessCommand(), Write()
  * �������У�   StaticCreate(), shared_ptr
*/
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.04

#include "GameHead.h"
//#include "Entity.h"
//class Entity;
//class Hero;

shared_ptr< Command > Command::StaticReadAndCreate( InputMemoryBitStream& inInputStream )
{
	CommandPtr retVal;
	
	int type = CM_INVALID;
	inInputStream.Read( type );                 //���ֽ�����ȡ ��������
	uint32_t networkId = 0;
	inInputStream.Read( networkId );        //���ֽ�����ȡ �����Ӧ�ľ���id
	uint32_t playerId = 0;
	inInputStream.Read( playerId );             //���ֽ�����ȡ ������������id

	switch ( type ) //�����������ͣ���������ʵ������������Read()
	{

	case CM_ATTACK:
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;
     /*
	case CM_MOVE:
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;
        */
	default:
		LOG_SU( "Read in an unknown command type??" );
		break;
	}

	return retVal;
}

void Command::Write( OutputMemoryBitStream& inOutputStream )
{
	inOutputStream.Write( mCommandType );
	inOutputStream.Write( mNetworkId );
	inOutputStream.Write( mPlayerId );
}


AttackCommandPtr AttackCommand::StaticCreate( uint32_t inMyNetId, uint32_t inTargetNetId )
{
	AttackCommandPtr retVal;
	EntityPtr me = NetworkManager::sInstance->GetGameObject( inMyNetId );
	EntityPtr target = NetworkManager::sInstance->GetGameObject( inTargetNetId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //�Ƿ���Թ����������ж�
	//can only issue commands to this unit if I own it, and it's a cat,
	//and if the target is a cat that's on a different team
	if ( me && me->GetClassId() == Hero::kClassId &&
		me->GetPlayerId() ==  playerId &&
		target && target->GetClassId() == Hero::kClassId &&
		target->GetPlayerId() != me->GetPlayerId() )
	{ //���Թ������������д����
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = inMyNetId;
		retVal->mPlayerId = playerId;
		retVal->mTargetNetId = inTargetNetId;
	}
	return retVal;
}



void AttackCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTargetNetId );
}

//��ȡ���еĹ��������ӦWrite()
void AttackCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTargetNetId );
}

// �������еĹ�������
void AttackCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    // 
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//RoboCat* rc = obj->GetAsCat();
		//rc->EnterAttackState( mTargetNetId );
	}
}


//����Move������ظ������ָ��
MoveCommandPtr MoveCommand::StaticCreate( uint32_t inNetworkId, const cocos2d::Vec2& inTarget )
{   //�������������������id��move��Ŀ��λ��
	MoveCommandPtr retVal;
	EntityPtr go = NetworkManager::sInstance->GetGameObject( inNetworkId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //��֤��������id�ǿ������ߵģ����Ҹ����id���Կ�����
	//can only issue commands to this unit if I own it, and it's a cat
	if ( go && go->GetClassId() == Hero::kClassId && 
		go->GetPlayerId() == playerId )
	{
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = inNetworkId;
		retVal->mPlayerId = playerId;
		retVal->mTarget = inTarget;
	}
	return retVal;
}

void MoveCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTarget );//д������Ŀ��
}

//ִ��Move����
void MoveCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    //�ٴ��жϣ��Ƿ��ظ�����
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//Hero* rc = obj->GetAsCat();
		//rc->EnterMovingState( mTarget );//���ߵ�ʵ�ֺ���
	}
}

//��ӦWrite()
void MoveCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTarget );
}