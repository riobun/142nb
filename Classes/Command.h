/* Command  �����д
  ******��������*******
  * ����ʾ����   AttackCommand, MoveCommand
  * public�̳�Command��
  * ������Ҫʵ�ֵ��麯����
  *                          Read(), ProcessCommand(), Write()
  * �������У�   StaticCreate(), shared_ptr
  * ����Command�����������ECommandType

  ******��������*******
  *cmd = AttackCommand::StaticCreate(...);
  *if (cmd)
  *CommandList::sInstance->AddCommand(cmd);
  */
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.08

#ifndef _COMMAND_H_
#define _COMMAND_H_
class Command
{
public:
	enum ECommandType   //�������������ͣ���Ҫ���
	{
		CM_INVALID,
		CM_ATTACK,
		CM_MOVE,
        CM_CHOOSE
	};

	Command() :
	mCommandType( CM_INVALID ),
	mNetworkId( 0 ),
	mPlayerId( 0 )
	{}

	//given a buffer, will construct the appropriate command subclass
    //���ֽ�����ȡ�������͵�ö�٣��ݴ˴��������ʵ��������������Read()
	static shared_ptr< Command > StaticReadAndCreate( InputMemoryBitStream& inInputStream );

	void SetNetworkId( uint32_t inId ) { mNetworkId = inId; }
	int GetNetworkId() const { return mNetworkId; }

	void SetPlayerId( uint32_t inId ) { mPlayerId = inId; }
	int GetPlayerId() const { return mPlayerId; }

    //д����ֽ���
	virtual void Write( OutputMemoryBitStream& inOutputStream );
    //ִ������
	virtual void ProcessCommand() = 0;
protected:
    //���ֽ���������
	virtual void Read( InputMemoryBitStream& inInputStream ) = 0;

	ECommandType mCommandType;  //��������
	uint32_t mNetworkId;                        //�����Ӧ�ľ���id
	uint32_t mPlayerId;                             //������������id
};

typedef shared_ptr< Command >	CommandPtr;


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

	virtual void ProcessCommand() override; //������Ϸ�߼�������ִ������

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t mTargetNetId;
};

typedef shared_ptr< AttackCommand > AttackCommandPtr;


class MoveCommand : public Command
{
public:
	MoveCommand()
	{
		mCommandType = CM_MOVE;
	}

	static shared_ptr< MoveCommand > StaticCreate( uint32_t inNetworkId, const cocos2d::Vec2& inTarget );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

    //�ƶ�Ŀ��
	cocos2d::Vec2 mTarget;
};

typedef shared_ptr< MoveCommand > MoveCommandPtr;

class ChooseHeroCommand : public Command
{
public:
    ChooseHeroCommand()
    {
        mCommandType = CM_CHOOSE;
    }

    static shared_ptr< ChooseHeroCommand > StaticCreate(EntityPtr inHero);

    virtual void Write(OutputMemoryBitStream& inOutputStream) override;

    virtual void ProcessCommand() override;

protected:
    virtual void Read(InputMemoryBitStream& inInputStream) override;

    //???????????????
    EntityPtr mHero;
    int heroClassId;
};

typedef shared_ptr< ChooseHeroCommand > ChooseHeroCommandPtr;

#endif //_COMMAND_H_