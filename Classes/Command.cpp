/* Command  �����д
  * ������Ҫʵ�ֵ��麯����
  *                          Read(), ProcessCommand(), Write()
  * �������У�   StaticCreate(), shared_ptr
*/
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.08

#include "GameHead.h"

shared_ptr< Command > Command::StaticReadAndCreate( InputMemoryBitStream& inInputStream )
{
	CommandPtr retVal;
	
	int type = CM_INVALID;
	inInputStream.Read( type );                 //���ֽ�����ȡ ��������
	uint32_t networkId = 0;
	inInputStream.Read( networkId );        //���ֽ�����ȡ �����Ӧ�ľ���id
	uint32_t playerId = 0;
	inInputStream.Read( playerId );             //���ֽ�����ȡ ������������id

	switch ( type )
	{

	case CM_ATTACK:
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;
     
	case CM_MOVE:
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read( inInputStream );
		break;

    case CM_CHOOSE:
        retVal = std::make_shared< ChooseHeroCommand >();
        retVal->mNetworkId = networkId;
        retVal->mPlayerId = playerId;
        retVal->Read(inInputStream);
        break;
        
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
	EntityPtr me = NetworkManager::sInstance->GetGameObject( inMyNetId );//����������ʵ���ָ��
	EntityPtr target = NetworkManager::sInstance->GetGameObject( inTargetNetId );//��������ʵ���ָ��
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();//������

    //�Ƿ���Թ�����
	if ( me && me->GetClassId() == Hero::kClassId &&
		me->GetPlayerId() ==  playerId &&
		target && target->GetClassId() == Hero::kClassId &&
		target->GetPlayerId() != me->GetPlayerId() )
	{ 
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = inMyNetId;
		retVal->mPlayerId = playerId;
		retVal->mTargetNetId = inTargetNetId;
	}
    else
    {
        LOG_SU("attack command create error");
    }
	return retVal;
}


void AttackCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTargetNetId );
}

void AttackCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTargetNetId );
}

void AttackCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//����ִ�й����ĺ���������
        // Call function to process the attack command
	}
}


MoveCommandPtr MoveCommand::StaticCreate( uint32_t inNetworkId, const cocos2d::Vec2& inTarget )
{  
	MoveCommandPtr retVal;
	EntityPtr go = NetworkManager::sInstance->GetGameObject( inNetworkId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

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

void MoveCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//����ʵ�����ߵĺ���������
        // Call function to process the move command
	}
}

void MoveCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTarget );
}

ChooseHeroCommandPtr ChooseHeroCommand::StaticCreate(EntityPtr inHero)
{
    ChooseHeroCommandPtr retVal;
    uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    if (inHero->GetClassId() == Hero::kClassId &&
        inHero->GetPlayerId() == playerId)
    {
        retVal = std::make_shared< ChooseHeroCommand >();
        retVal->mPlayerId = playerId;
        retVal->heroClassId = Hero::kClassId;
    }
    return retVal;
}

void ChooseHeroCommand::Write(OutputMemoryBitStream& inOutputStream)
{
    Command::Write(inOutputStream);
    inOutputStream.Write(heroClassId);
}


void ChooseHeroCommand::ProcessCommand()
{
    if (heroClassId == Hero::kClassId)
    {
        NetworkManager::sInstance->RegisterGameObject(EntityRegistry::sInstance->CreateEntity(heroClassId));
    }
}

void ChooseHeroCommand::Read(InputMemoryBitStream& inInputStream)
{
    inInputStream.Read(heroClassId);
}
