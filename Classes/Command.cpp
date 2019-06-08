/* Command  命令读写
  * 子类示例：   AttackCommand, MoveCommand
  * 子类需要实现的虚函数：
  *                          Read(), ProcessCommand(), Write()
  * 子类须有：   StaticCreate(), shared_ptr
*/
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.08

#include "GameHead.h"

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
	EntityPtr me = NetworkManager::sInstance->GetGameObject( inMyNetId );//发出攻击的实体的指针
	EntityPtr target = NetworkManager::sInstance->GetGameObject( inTargetNetId );//被攻击的实体的指针
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();//操作者

    //是否可以攻击？条件判断
	//发出攻击的实体存在，发出攻击的实体是英雄，该英雄是我的
    //被攻击的实体存在，被攻击的是英雄，被攻击的不是我
	if ( me && me->GetClassId() == Hero::kClassId &&
		me->GetPlayerId() ==  playerId &&
		target && target->GetClassId() == Hero::kClassId &&
		target->GetPlayerId() != me->GetPlayerId() )
	{ //可以攻击，创建命令并写进流
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = inMyNetId;
		retVal->mPlayerId = playerId;
		retVal->mTargetNetId = inTargetNetId;
	}
    else
    {
        LOG_SU("attack command create error");/////////debug
    }
	return retVal;
}



void AttackCommand::Write( OutputMemoryBitStream& inOutputStream )
{
	Command::Write( inOutputStream );
	inOutputStream.Write( mTargetNetId );
}

//读取流中的攻击命令，对应Write()
void AttackCommand::Read( InputMemoryBitStream& inInputStream )//没有被调用
{
	inInputStream.Read( mTargetNetId );
}

// 处理流中的攻击命令
void AttackCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    // 该网络id对应的实体存在，实体是英雄类，实体拥有者是我
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//RoboCat* rc = obj->GetAsCat();
		//rc->EnterAttackState( mTargetNetId );
	}
}


//创建Move命令，返回该命令的指针
MoveCommandPtr MoveCommand::StaticCreate( uint32_t inNetworkId, const cocos2d::Vec2& inTarget )
{   //参数：网络id对应的实体的网络id和move的目标位置
	MoveCommandPtr retVal;
	EntityPtr go = NetworkManager::sInstance->GetGameObject( inNetworkId );
	uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();

    //验证：该实体存在，是英雄，是我的
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
	inOutputStream.Write( mTarget );//写入行走目标
}

//执行Move命令
void MoveCommand::ProcessCommand()
{
	EntityPtr obj = NetworkManager::sInstance->GetGameObject( mNetworkId );
    //实体存在，是英雄，发出命令的是拥有者
	if ( obj && obj->GetClassId() == Hero::kClassId &&
		obj->GetPlayerId() == mPlayerId )
	{
		//Hero* rc = obj->GetAsCat();
		//rc->EnterMovingState( mTarget );//行走的实现函数
	}
}

//对应Write()
void MoveCommand::Read( InputMemoryBitStream& inInputStream )
{
	inInputStream.Read( mTarget );
}