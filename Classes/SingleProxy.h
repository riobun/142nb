//Single Proxy: 单机模式中转发命令的代理
// 杜玫，2019.06.09


#ifndef _SINGLE_PROXY_H_
#define _SINGLE_PROXY_H_

class SingleProxy
{
public:
    //sent when accepted by master peer欢迎加入
    //static const uint32_t	kWelcomeCC = 'WLCM';
    //sent by new player to all non-master peers after being accepted
    static const uint32_t	kIntroCC = 'INTR';
    //contains data for a particular turn轮数据
    static const uint32_t	kTurnCC = 'TURN';
    //notifies peers that the game will be starting soon马上开始
    static const uint32_t	kStartCC = 'STRT';
    static const int		kMaxPacketsPerFrameCount = 10;//每秒10轮

    enum SingleProxyState
    {
        SG_Lobby,             //休息
        //everything above this should be the pre-game/lobby/connection
        SG_Starting,           //正在开始游戏（初始化）
        SG_Playing,            //正在进行游戏
        //NMS_Delay,              //其它伙伴延迟
    };

    // 唯一实例
    static unique_ptr< SingleProxy >	sInstance;
    //初始化为主机
    static bool	StaticInitAsMasterPeer(uint16_t inPort, const string& inName);
    //初始化为分机
    static bool StaticInitAsPeer(const SocketAddress& inMPAddress, const string& inName);

    SingleProxy();
    ~SingleProxy();

    void	ProcessIncomingPackets();     //该轮主循环未发送网络包，接收
    void	SendOutgoingPackets();         //该轮主循环未发送网络包，发送
private:
    //void	UpdateSayingHello(bool inForce = false);  //定时发送Hello包
    //void	SendHelloPacket();                                           //发送Hello包
    void UpdateLobby();
    void	UpdateStarting();                                              //游戏初始化更新
    void	UpdateSendTurnPacket();                             //给每个对象发送轮数据包
   // void	TryAdvanceTurn();                                           //是否出现延迟以及处理
public:
    //处理接收包，分类:NMS_Hello,  Lobby, Playing, Delay
    void	ProcessPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);
private:
    //void	ProcessPacketsHello(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//在Hello状态
    //void	HandleNotMPPacket(InputMemoryBitStream& inInputStream);//他不是主机，重新发
    //void	HandleWelcomePacket(InputMemoryBitStream& inInputStream);//得到欢迎包，处理id
    void	ProcessPacketsLobby(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//在休息状态
    //void	HandleHelloPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//休息接到hello
    void	HandleIntroPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//休息接到intro
    void	HandleStartPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//休息接到start
    void	ProcessPacketsPlaying(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//在游戏状态
    void	HandleTurnPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//处理轮数据
    //void	ProcessPacketsDelay(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//在等待状态
public:
    //void	HandleConnectionReset(const SocketAddress& inFromAddress);//有用户断开连接

    void	SendPacket(const OutputMemoryBitStream& inOutputStream, const SocketAddress& inToAddress);

    void	TryStartGame();//主机试图开始游戏

    const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const { return mBytesReceivedPerSecond; }
    const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const { return mBytesSentPerSecond; }
    //void	SetDropPacketChance(float inChance) { mDropPacketChance = inChance; }
    //float	GetDropPacketChance() const { return mDropPacketChance; }
    //void	SetSimulatedLatency(float inLatency) { mSimulatedLatency = inLatency; }  //模拟延迟
    //float	GetSimulatedLatency() const { return mSimulatedLatency; }               //模拟延迟

    bool	IsMasterPeer() const { return mIsMasterPeer; }
    float	GetTimeToStart() const { return mTimeToStart; }

    EntityPtr	 GetGameObject(uint32_t inNetworkId) const;   //从网络id得到游戏对象id
    EntityPtr 	RegisterAndReturn(Entity* inGameObject);  //注册新的游戏对象
    void			UnregisterGameObject(Entity* inGameObject);   //取消该游戏对象id

    SingleProxyState GetState() const { return mState; }
    int	    	GetPlayerCount() const { return mPlayerCount; }
    int	    	GetTurnNumber() const { return mTurnNumber; }
    int		    GetSubTurnNumber() const { return mSubTurnNumber; }
    uint32_t GetMyPlayerId() const { return mPlayerId; }

private:

    void	AddToNetworkIdToGameObjectMap(EntityPtr inGameObject);//添加至：用网络id找游戏对象id的map
    void	RemoveFromNetworkIdToGameObjectMap(EntityPtr inGameObject);//移除：用网络id找游戏对象id的map
    void	RegisterGameObject(EntityPtr inGameObject);
    uint32_t GetNewNetworkId();

    uint32_t ComputeGlobalCRC(); //循环冗余检验

    bool	InitAsMasterPeer(uint16_t inPort, const string& inName);
    bool	InitAsPeer(const SocketAddress& inMPAddress, const string& inName);
    //bool	InitSocket(uint16_t inPort);//创建UDPSocket,绑定,nonblocking

    /*
    class ReceivedPacket
    {
    public:
        ReceivedPacket(float inReceivedTime, InputMemoryBitStream& inInputMemoryBitStream, const SocketAddress& inAddress);

        const	SocketAddress&		GetFromAddress()	const { return mFromAddress; }
        float					                    GetReceivedTime()	const { return mReceivedTime; }
        InputMemoryBitStream&	GetPacketBuffer() { return mPacketBuffer; }

    private:

        float					                mReceivedTime;
        InputMemoryBitStream	mPacketBuffer;
        SocketAddress			        mFromAddress;

    };
    */

    //ProcessIncomingPacket()中顺序调用
    void	ReadIncomingPacketsIntoQueue(); //读取到流
    void	ProcessQueuedPackets();                 //处理流中的packets
    void	UpdateBytesSentLastFrame();          //更新状态

    void	UpdateHighestPlayerId(uint32_t inId);
    void	EnterPlayingState();

    //these should stay ordered!
    typedef map< uint32_t, SocketAddress > IntToSocketAddrMap;
    typedef map< uint32_t, string > IntToStrMap;
    typedef map< uint32_t, TurnData > IntToTurnDataMap;
    typedef map< uint32_t, EntityPtr > IntToGameObjectMap;

    typedef unordered_map< SocketAddress, uint32_t > SocketAddrToIntMap;

    //bool	CheckSync(IntToTurnDataMap& inTurnMap);//是否是期待的包

    //queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

    IntToGameObjectMap			mNetworkIdToGameObjectMap;          //网络id  --  实体指针
    //IntToSocketAddrMap			mPlayerToSocketMap;                            //玩家id   --  socket地址
    //SocketAddrToIntMap			mSocketToPlayerMap;                            //socket地址   --  玩家id
public:
    IntToStrMap				        	mPlayerNameMap;                                 //网络id -- 玩家名字，改为publlic
private:
    //this stores all of our turn information for every turn since game start
    vector< IntToTurnDataMap >	mTurnData;

    //UDPSocketPtr	mSocket;
    //SocketAddress	mMasterPeerAddr;

    WeightedTimedMovingAverage	mBytesReceivedPerSecond;
    WeightedTimedMovingAverage	mBytesSentPerSecond;
    SingleProxyState		        	mState;

    int					mBytesSentThisFrame;
    std::string		mName;

    //float			mDropPacketChance;
    //float			mSimulatedLatency;

    //float			mTimeOfLastHello;
    float			mTimeToStart;

    int				mPlayerCount;
    //int                 mIntroCount;
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
#endif // !_SINGLE_PROXY_H_