// CommandList:  命令队列
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05
//  合并InputManager与CommandList，便于调用

#ifndef _COMMAND_LIST_H
#define _COMMAND_LIST_H

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

	void			ProcessCommands( uint32_t inExpectedPlayerId );//当命令id是期望的id时，处理命令
    void			ProcessCommands();//处理所有命令

	void Write( OutputMemoryBitStream& inOutputStream );
	void Read( InputMemoryBitStream& inInputStream );

private:
	deque< CommandPtr >	mCommands;
};

#endif // _COMMAND_LIST_H