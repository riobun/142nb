// CommandList:  命令队列
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05
//  合并InputManager与CommandList，便于调用

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

	void			ProcessCommands( uint32_t inExpectedPlayerId );//当命令id是期望的id时，处理命令

	void Write( OutputMemoryBitStream& inOutputStream );
	void Read( InputMemoryBitStream& inInputStream );

private:
    
    //	void			GenerateRightClickCommand( const Vector3& inWorldPos );
	deque< CommandPtr >	mCommands;
    //	uint32_t		mSelectedNetId;
};

