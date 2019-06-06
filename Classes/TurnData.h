// TurnData：轮数据，用于同步
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫，2019.06.04

class TurnData
{
public:
	//default constructor exists so we can use it when reading from network
    TurnData() :
        mPlayerId(0),
        mRandomValue(0),
        mCRC(0)
    { }

	TurnData( int inPlayerId, uint32_t inRandomValue, uint32_t inCRC, CommandList& inCommandList ):
	mPlayerId(inPlayerId),
	mRandomValue(inRandomValue),
	mCRC(inCRC),
	mCommandList(inCommandList)
	{}

	void Write( OutputMemoryBitStream& inOutputStream );
	void Read( InputMemoryBitStream& inInputStream );

	int GetPlayerId() const { return mPlayerId; }
	uint32_t GetRandomValue() const { return mRandomValue; }
	uint32_t GetCRC() const { return mCRC; }

	CommandList& GetCommandList() { return mCommandList; }

private:
	int mPlayerId;
	uint32_t mRandomValue;
	uint32_t mCRC;
	CommandList mCommandList;
};
