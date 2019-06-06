// CommandList:  �������
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05
//  �ϲ�InputManager��CommandList�����ڵ���

class CommandList
{
public:
    static void StaticInit();
    static unique_ptr< CommandList >	sInstance;
    CommandList()
    {}

	void			AddCommand( CommandPtr inCommand );

	void			Clear()							{ mCommands.clear(); }//ClearCommandList
	int			GetCount()		const	{ return static_cast<int>(mCommands.size()); }

    //void			Update();
    //uint32_t		GetSelectedNetId() { return mSelectedNetId; }

	void			ProcessCommands( uint32_t inExpectedPlayerId );//������id��������idʱ����������

	void Write( OutputMemoryBitStream& inOutputStream );
	void Read( InputMemoryBitStream& inInputStream );

private:
    
    //	void			GenerateRightClickCommand( const Vector3& inWorldPos );
	deque< CommandPtr >	mCommands;
    //	uint32_t		mSelectedNetId;
};

