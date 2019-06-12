/* Command  命令读写
  * 子类示例：   AttackCommand, MoveCommand
  * 子类需要实现的虚函数：
  *                          Read(), ProcessCommand(), Write()
  * 子类须有：   StaticCreate(), shared_ptr
*/
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.04

#include "NetworkHead.h"

shared_ptr< Command > Command::StaticReadAndCreate( InputMemoryBitStream& inInputStream )
{
	CommandPtr retVal;
	
	int type = CM_INVALID;
	inInputStream.Read( type );                 //从字节流读取 命令类型
	uint32_t networkId = 0;
	inInputStream.Read( networkId );        //从字节流读取 命令对应的精灵id
	uint32_t playerId = 0;
	inInputStream.Read( playerId );             //从字节流读取 发送命令的玩家id

	switch ( type ) //根据命令类型，创建子类实例，调用子类Read()
	{
          /*
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
<<<<<<< Updated upstream
        */
=======
        
    case CM_CHOOSE:
        retVal = std::make_shared< ChooseHeroCommand >();
        retVal->mNetworkId = networkId;
        retVal->mPlayerId = playerId;
        retVal->Read(inInputStream);
        break;

>>>>>>> Stashed changes
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

/* 创建Attack命令，返回其指针
AttackCommandPtr AttackCommand::StaticCreate( uint32_t inMyNetId, uint32_t inTargetNetId )
{
	AttackCommandPtr retVal;
	GameObjectPtr me = NetworkManager::sInstance->GetGameObject( inMyNetId );
	GameObjectPtr target = NetworkManager::sInstance->GetGameObject( inTargetNetId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //是否可以攻击？条件判断
	//can only issue commands to this unit if I own it, and it's a cat,
	//and if the target is a cat that's on a different team
	if ( me && me->GetClassId() == RoboCat::kClassId &&
		me->GetPlayerId() ==  playerId &&
		target && target->GetClassId() == RoboCat::kClassId &&
		target->GetPlayerId() != me->GetPlayerId() )
	{ //可以攻击，创建命令并写进流
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = inMyNetId;
		retVal->mPlayerId = playerId;
		retVal->mTargetNetId = inTargetNetId;
	}
	return retVal;
}
*/

/*把命令写进流
void AttackCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTargetNetId );
}

//读取流中的攻击命令，对应Write()
void AttackCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTargetNetId );
}*/

/* 处理流中的攻击命令
void AttackCommand::ProcessCommand()
{
	GameObjectPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    // 
	if ( obj && obj->GetClassId() == RoboCat::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		RoboCat* rc = obj->GetAsCat();
		rc->EnterAttackState( mTargetNetId );
	}
}
*/

/*创建Move命令，返回该命令的指针
MoveCommandPtr MoveCommand::StaticCreate( uint32_t inNetworkId, const Vector3& inTarget )
{   //参数：发出命令的网络id和move的目标位置
	MoveCommandPtr retVal;
	GameObjectPtr go = NetworkManager::sInstance->GetGameObject( inNetworkId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //验证：该网络id是可以行走的；并且该玩家id可以控制它
	//can only issue commands to this unit if I own it, and it's a cat
	if ( go && go->GetClassId() == RoboCat::kClassId && 
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
	inOutputStream.Write( mTarget );//写入行走目标
}

//执行Move命令
void MoveCommand::ProcessCommand()
{
	GameObjectPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    //再次判断（是否重复？）
	if ( obj && obj->GetClassId() == RoboCat::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		RoboCat* rc = obj->GetAsCat();
		rc->EnterMovingState( mTarget );//行走的实现函数
	}
}

//对应Write()
void MoveCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTarget );
}
<<<<<<< Updated upstream
*/
=======


ChooseHeroCommandPtr ChooseHeroCommand::StaticCreate(EntityPtr inHero)
{
    ChooseHeroCommandPtr retVal;
    uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //验证：该实体是英雄，是我的
    if (inHero->GetClassId() == Hero::kClassId &&
        inHero->GetPlayerId() == playerId)
    {
        retVal = std::make_shared< ChooseHeroCommand >();
        retVal->mPlayerId = playerId;
        retVal->heroClassId = Hero::kClassId;//添加英雄时更改
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
        NetworkManager::sInstance->RegisterAndReturn(EntityRegistry::sInstance->CreateEntity(heroClassId));
    }
}

void ChooseHeroCommand::Read(InputMemoryBitStream& inInputStream)
{
    inInputStream.Read(heroClassId);
}
>>>>>>> Stashed changes
