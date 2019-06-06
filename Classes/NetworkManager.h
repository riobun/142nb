// NetworkManager:  网络收发处理主要接口
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

class NetworkManager
{
public:
    // Packet Types
	//sent when first trying to join请求加入
	static const uint32_t	kHelloCC = 'HELO';
	//sent when accepted by master peer欢迎加入
	static const uint32_t	kWelcomeCC = 'WLCM';
	//sent as a reply to HELO if it isn't the master peer不是主机
	static const uint32_t	kNotMasterPeerCC = 'NOMP';
	//sent as a reply to HELO if the game can't be joined (either full or already started)不能加入
	static const uint32_t	kNotJoinableCC = 'NOJN';
	//sent by new player to all non-master peers after being accepted
	static const uint32_t	kIntroCC = 'INTR';
	//contains data for a particular turn轮数据
	static const uint32_t	kTurnCC = 'TURN';
	//notifies peers that the game will be starting soon马上开始
	static const uint32_t	kStartCC = 'STRT';
	static const int		kMaxPacketsPerFrameCount = 10;//每秒10轮

	enum NetworkManagerState
	{
		NMS_Unitialized,    //未初始化
		NMS_Hello,              //请求加入过程中
		NMS_Lobby,             //休息
		//everything above this should be the pre-game/lobby/connection
		NMS_Starting,           //正在开始游戏（初始化）
		NMS_Playing,            //正在进行游戏
		NMS_Delay,              //其它伙伴延迟
	};

    // 唯一实例
	static unique_ptr< NetworkManager >	sInstance;
    //初始化为主机
	static bool	StaticInitAsMasterPeer( uint16_t inPort, const string& inName );
    //初始化为分机
	static bool StaticInitAsPeer( const SocketAddress& inMPAddress, const string& inName );

	NetworkManager();
	~NetworkManager();

	void	ProcessIncomingPackets();     //该轮主循环未发送网络包，接收
	void	SendOutgoingPackets();         //该轮主循环未发送网络包，发送
private:
	void	UpdateSayingHello( bool inForce = false );  //定时发送Hello包
	void	SendHelloPacket();                                           //发送Hello包
	void	UpdateStarting();                                              //游戏初始化更新
	void	UpdateSendTurnPacket();                             //给每个对象发送轮数据包
	void	TryAdvanceTurn();                                           //是否出现延迟以及处理
public:
    //处理接收包，分类:NMS_Hello,  Lobby, Playing, Delay
	void	ProcessPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );
private:
	void	ProcessPacketsHello( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//在Hello状态
	void	HandleNotMPPacket( InputMemoryBitStream& inInputStream );//他不是主机，重新发
	void	HandleWelcomePacket( InputMemoryBitStream& inInputStream );//得到欢迎包，处理id
	void	ProcessPacketsLobby( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//在休息状态
	void	HandleHelloPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//休息接到hello
	void	HandleIntroPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//休息接到intro
	void	HandleStartPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//休息接到start
	void	ProcessPacketsPlaying( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//在游戏状态
	void	HandleTurnPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//处理轮数据
	void	ProcessPacketsDelay( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress );//在等待状态
public:
	void	HandleConnectionReset( const SocketAddress& inFromAddress );//有用户断开连接

	void	SendPacket( const OutputMemoryBitStream& inOutputStream, const SocketAddress& inToAddress );

	void	TryStartGame();//主机试图开始游戏

			const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const	{ return mBytesReceivedPerSecond; }
			const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const	{ return mBytesSentPerSecond; }
	void	SetDropPacketChance( float inChance )	{ mDropPacketChance = inChance; }
	float	GetDropPacketChance() const				{ return mDropPacketChance; }
	void	SetSimulatedLatency( float inLatency )	{ mSimulatedLatency = inLatency; }  //模拟延迟？
	float	GetSimulatedLatency() const				{ return mSimulatedLatency; }               //模拟延迟？

	bool	IsMasterPeer() const { return mIsMasterPeer; }
	float	GetTimeToStart() const { return mTimeToStart; }
	
	GameObjectPtr	 GetGameObject( uint32_t inNetworkId ) const;   //从网络id得到游戏对象id
	GameObjectPtr 	RegisterAndReturn( GameObject* inGameObject );  //注册新的游戏对象
	void			UnregisterGameObject( GameObject* inGameObject );   //取消该游戏对象id

	NetworkManagerState GetState() const { return mState; }
	int	    	GetPlayerCount() const { return mPlayerCount; }
	int	    	GetTurnNumber() const { return mTurnNumber; }
	int		    GetSubTurnNumber() const { return mSubTurnNumber; }
	uint32_t GetMyPlayerId() const { return mPlayerId; }

private:

	void	AddToNetworkIdToGameObjectMap( GameObjectPtr inGameObject );//添加至：用网络id找游戏对象id的map
	void	RemoveFromNetworkIdToGameObjectMap( GameObjectPtr inGameObject );//移除：用网络id找游戏对象id的map
	void	RegisterGameObject( GameObjectPtr inGameObject );
	uint32_t GetNewNetworkId();

	uint32_t ComputeGlobalCRC(); //循环冗余检验

	bool	InitAsMasterPeer( uint16_t inPort, const string& inName );
	bool	InitAsPeer( const SocketAddress& inMPAddress, const string& inName );
	bool	InitSocket( uint16_t inPort );//创建UDPSocket,绑定,nonblocking
	
	class ReceivedPacket
	{
	public:
		ReceivedPacket( float inReceivedTime, InputMemoryBitStream& inInputMemoryBitStream, const SocketAddress& inAddress );

		const	SocketAddress&		GetFromAddress()	const	{ return mFromAddress; }
		float					                    GetReceivedTime()	const	{ return mReceivedTime; }
		InputMemoryBitStream&	GetPacketBuffer()			        { return mPacketBuffer; }

	private:
			
		float					                mReceivedTime;
		InputMemoryBitStream	mPacketBuffer;
		SocketAddress			        mFromAddress;

	};

    //ProcessIncomingPacket()中顺序调用
	void	ReadIncomingPacketsIntoQueue(); //读取到流
	void	ProcessQueuedPackets();                 //处理流中的packets
	void	UpdateBytesSentLastFrame();          //更新状态

	void	UpdateHighestPlayerId( uint32_t inId );
	void	EnterPlayingState();

	//these should stay ordered!
	typedef map< uint32_t, SocketAddress > IntToSocketAddrMap;  
	typedef map< uint32_t, string > IntToStrMap;
	typedef map< uint32_t, TurnData > IntToTurnDataMap;
	typedef map< uint32_t, GameObjectPtr > IntToGameObjectMap;

	typedef unordered_map< SocketAddress, uint32_t > SocketAddrToIntMap;

	bool	CheckSync( IntToTurnDataMap& inTurnMap );//是否是期待的包

	queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

	IntToGameObjectMap			mNetworkIdToGameObjectMap;          //网络id  --  游戏对象id
	IntToSocketAddrMap			mPlayerToSocketMap;                            //玩家id   --  socket地址
	SocketAddrToIntMap			mSocketToPlayerMap;                            //socket地址   --  玩家id
	IntToStrMap				        	mPlayerNameMap;                                 //所有玩家的名字

	//this stores all of our turn information for every turn since game start
	vector< IntToTurnDataMap >	mTurnData;

	UDPSocketPtr	mSocket;
	SocketAddress	mMasterPeerAddr;

	WeightedTimedMovingAverage	mBytesReceivedPerSecond;
	WeightedTimedMovingAverage	mBytesSentPerSecond;
	NetworkManagerState		        	mState;

	int					mBytesSentThisFrame;
	std::string		mName;

	float			mDropPacketChance;
	float			mSimulatedLatency;

	float			mTimeOfLastHello;
	float			mTimeToStart;

	int				mPlayerCount;
	//we track the highest player id seen in the event
	//the master peer d/cs and we need a new master peer
	//who can assign ids
	uint32_t		mHighestPlayerId;
	uint32_t		mNewNetworkId;
	uint32_t		mPlayerId;

	int				mTurnNumber;
	int				mSubTurnNumber;
	bool			mIsMasterPeer;
};
