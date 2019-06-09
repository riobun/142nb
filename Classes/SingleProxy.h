//Single Proxy: ����ģʽ��ת������Ĵ���
// ��õ��2019.06.09


#ifndef _SINGLE_PROXY_H_
#define _SINGLE_PROXY_H_

class SingleProxy
{
public:
    //sent when accepted by master peer��ӭ����
    //static const uint32_t	kWelcomeCC = 'WLCM';
    //sent by new player to all non-master peers after being accepted
    static const uint32_t	kIntroCC = 'INTR';
    //contains data for a particular turn������
    static const uint32_t	kTurnCC = 'TURN';
    //notifies peers that the game will be starting soon���Ͽ�ʼ
    static const uint32_t	kStartCC = 'STRT';
    static const int		kMaxPacketsPerFrameCount = 10;//ÿ��10��

    enum SingleProxyState
    {
        SG_Lobby,             //��Ϣ
        //everything above this should be the pre-game/lobby/connection
        SG_Starting,           //���ڿ�ʼ��Ϸ����ʼ����
        SG_Playing,            //���ڽ�����Ϸ
        //NMS_Delay,              //��������ӳ�
    };

    // Ψһʵ��
    static unique_ptr< SingleProxy >	sInstance;
    //��ʼ��Ϊ����
    static bool	StaticInitAsMasterPeer(uint16_t inPort, const string& inName);
    //��ʼ��Ϊ�ֻ�
    static bool StaticInitAsPeer(const SocketAddress& inMPAddress, const string& inName);

    SingleProxy();
    ~SingleProxy();

    void	ProcessIncomingPackets();     //������ѭ��δ���������������
    void	SendOutgoingPackets();         //������ѭ��δ���������������
private:
    //void	UpdateSayingHello(bool inForce = false);  //��ʱ����Hello��
    //void	SendHelloPacket();                                           //����Hello��
    void UpdateLobby();
    void	UpdateStarting();                                              //��Ϸ��ʼ������
    void	UpdateSendTurnPacket();                             //��ÿ�������������ݰ�
   // void	TryAdvanceTurn();                                           //�Ƿ�����ӳ��Լ�����
public:
    //������հ�������:NMS_Hello,  Lobby, Playing, Delay
    void	ProcessPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);
private:
    //void	ProcessPacketsHello(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//��Hello״̬
    //void	HandleNotMPPacket(InputMemoryBitStream& inInputStream);//���������������·�
    //void	HandleWelcomePacket(InputMemoryBitStream& inInputStream);//�õ���ӭ��������id
    void	ProcessPacketsLobby(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//����Ϣ״̬
    //void	HandleHelloPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//��Ϣ�ӵ�hello
    void	HandleIntroPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//��Ϣ�ӵ�intro
    void	HandleStartPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//��Ϣ�ӵ�start
    void	ProcessPacketsPlaying(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//����Ϸ״̬
    void	HandleTurnPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//����������
    //void	ProcessPacketsDelay(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress);//�ڵȴ�״̬
public:
    //void	HandleConnectionReset(const SocketAddress& inFromAddress);//���û��Ͽ�����

    void	SendPacket(const OutputMemoryBitStream& inOutputStream, const SocketAddress& inToAddress);

    void	TryStartGame();//������ͼ��ʼ��Ϸ

    const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const { return mBytesReceivedPerSecond; }
    const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const { return mBytesSentPerSecond; }
    //void	SetDropPacketChance(float inChance) { mDropPacketChance = inChance; }
    //float	GetDropPacketChance() const { return mDropPacketChance; }
    //void	SetSimulatedLatency(float inLatency) { mSimulatedLatency = inLatency; }  //ģ���ӳ�
    //float	GetSimulatedLatency() const { return mSimulatedLatency; }               //ģ���ӳ�

    bool	IsMasterPeer() const { return mIsMasterPeer; }
    float	GetTimeToStart() const { return mTimeToStart; }

    EntityPtr	 GetGameObject(uint32_t inNetworkId) const;   //������id�õ���Ϸ����id
    EntityPtr 	RegisterAndReturn(Entity* inGameObject);  //ע���µ���Ϸ����
    void			UnregisterGameObject(Entity* inGameObject);   //ȡ������Ϸ����id

    SingleProxyState GetState() const { return mState; }
    int	    	GetPlayerCount() const { return mPlayerCount; }
    int	    	GetTurnNumber() const { return mTurnNumber; }
    int		    GetSubTurnNumber() const { return mSubTurnNumber; }
    uint32_t GetMyPlayerId() const { return mPlayerId; }

private:

    void	AddToNetworkIdToGameObjectMap(EntityPtr inGameObject);//�������������id����Ϸ����id��map
    void	RemoveFromNetworkIdToGameObjectMap(EntityPtr inGameObject);//�Ƴ���������id����Ϸ����id��map
    void	RegisterGameObject(EntityPtr inGameObject);
    uint32_t GetNewNetworkId();

    uint32_t ComputeGlobalCRC(); //ѭ���������

    bool	InitAsMasterPeer(uint16_t inPort, const string& inName);
    bool	InitAsPeer(const SocketAddress& inMPAddress, const string& inName);
    //bool	InitSocket(uint16_t inPort);//����UDPSocket,��,nonblocking

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

    //ProcessIncomingPacket()��˳�����
    void	ReadIncomingPacketsIntoQueue(); //��ȡ����
    void	ProcessQueuedPackets();                 //�������е�packets
    void	UpdateBytesSentLastFrame();          //����״̬

    void	UpdateHighestPlayerId(uint32_t inId);
    void	EnterPlayingState();

    //these should stay ordered!
    typedef map< uint32_t, SocketAddress > IntToSocketAddrMap;
    typedef map< uint32_t, string > IntToStrMap;
    typedef map< uint32_t, TurnData > IntToTurnDataMap;
    typedef map< uint32_t, EntityPtr > IntToGameObjectMap;

    typedef unordered_map< SocketAddress, uint32_t > SocketAddrToIntMap;

    //bool	CheckSync(IntToTurnDataMap& inTurnMap);//�Ƿ����ڴ��İ�

    //queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

    IntToGameObjectMap			mNetworkIdToGameObjectMap;          //����id  --  ʵ��ָ��
    //IntToSocketAddrMap			mPlayerToSocketMap;                            //���id   --  socket��ַ
    //SocketAddrToIntMap			mSocketToPlayerMap;                            //socket��ַ   --  ���id
public:
    IntToStrMap				        	mPlayerNameMap;                                 //����id -- ������֣���Ϊpubllic
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