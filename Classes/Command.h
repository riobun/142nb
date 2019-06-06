/* Command  命令读写
  ******创建子类*******
  * 子类示例：   AttackCommand, MoveCommand
  * public继承Command类
  * 子类需要实现的虚函数：
  *                          Read(), ProcessCommand(), Write()
  * 子类须有：   StaticCreate(), shared_ptr
  * 须在Command添加命令类型ECommandType

  ******创建命令*******
  *cmd = AttackCommand::StaticCreate(...);
  *if (cmd)
  *CommandList::sInstance->AddCommand(cmd);
  */
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.04


class Command
{
public:
	enum ECommandType   //创建新命令类型，需要添加
	{
		CM_INVALID,
		CM_ATTACK,
		CM_MOVE
	};

	Command() :
	mCommandType( CM_INVALID ),
	mNetworkId( 0 ),
	mPlayerId( 0 )
	{}

	//given a buffer, will construct the appropriate command subclass
    //从字节流读取命令类型的枚举，据此创建子类的实例，并调用子类Read()
	static shared_ptr< Command > StaticReadAndCreate( InputMemoryBitStream& inInputStream );

	void SetNetworkId( uint32_t inId ) { mNetworkId = inId; }
	int GetNetworkId() const { return mNetworkId; }

	void SetPlayerId( uint32_t inId ) { mPlayerId = inId; }
	int GetPlayerId() const { return mPlayerId; }

    //写命令到字节流
	virtual void Write( OutputMemoryBitStream& inOutputStream );
    //执行命令
	virtual void ProcessCommand() = 0;
protected:
    //从字节流读命令
	virtual void Read( InputMemoryBitStream& inInputStream ) = 0;

	ECommandType mCommandType;  //命令类型
	uint32_t mNetworkId;                        //命令对应的精灵id
	uint32_t mPlayerId;                             //发出命令的玩家id
};

typedef shared_ptr< Command >	CommandPtr;

/* 例一：AttackCommand 
class AttackCommand : public Command
{
public:
	AttackCommand():
	mTargetNetId(0)
	{
		mCommandType = CM_ATTACK;
	}

	static shared_ptr< AttackCommand > StaticCreate( uint32_t inMyNetId, uint32_t inTargetNetId );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override; //调用游戏逻辑函数，执行命令

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t mTargetNetId;
};

typedef shared_ptr< AttackCommand > AttackCommandPtr;
*/

/*例二：MoveCommand
class MoveCommand : public Command
{
public:
	MoveCommand()
	{
		mCommandType = CM_MOVE;
	}

    // 该函数参数中 Vector3 是自定义类型
    // 如果命令中有自定义类型（且需要通过网络传输），须重定义
	static shared_ptr< MoveCommand > StaticCreate( uint32_t inNetworkId, const Vector3& inTarget );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

    //移动目标
	//Vector3 mTarget;
};

typedef shared_ptr< MoveCommand > MoveCommandPtr;
*/
