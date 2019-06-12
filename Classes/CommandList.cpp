// CommandList:  命令队列
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#include "NetworkHead.h"

unique_ptr< CommandList >	CommandList::sInstance;

void CommandList::StaticInit()
{
    sInstance.reset(new CommandList());
}

void CommandList::AddCommand( CommandPtr inCommand )
{
	mCommands.push_back( inCommand );
}

void CommandList::ProcessCommands( uint32_t inExpectedPlayerId )
{
	for( CommandPtr p : mCommands )
	{
		if ( p->GetPlayerId() == inExpectedPlayerId )
		{
			p->ProcessCommand();
		}
	}
}

void CommandList::ProcessCommands()
{
    for (CommandPtr p : mCommands)
        p->ProcessCommand();
}

void CommandList::Write( OutputMemoryBitStream& inOutputStream )
{
	inOutputStream.Write( GetCount() );
	for( CommandPtr p : mCommands )
	{
		p->Write( inOutputStream );
	}
}

void CommandList::Read( InputMemoryBitStream& inInputStream )
{
	int count;
	inInputStream.Read( count );
	for( int i = 0; i < count; ++i )
	{
		mCommands.push_back( Command::StaticReadAndCreate( inInputStream ) );
	}
}
