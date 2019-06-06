// UDPSocket类
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫，2019.06.01

class UDPSocket
{
public:

	~UDPSocket();

    //绑定端口
	int Bind( const SocketAddress& inToAddress ); 

    // 发送：
    //待发送数据起始指针；数据大小，<1300；接收者
    //成功进入发送队列则返回待发送的数据长度，失败返回-1
	int SendTo( const void* inToSend, int inLength, const SocketAddress& inToAddress );

    // 接收：
    //接收数据的缓冲区指针；缓冲区存储最大字节数(多出则丢弃)；发送者地址存储
    //成功返回已复制字节数，失败返回-1
	int ReceiveFrom( void* inToReceive, int inMaxLength, SocketAddress& outFromAddress );

	/*
	int SendTo( const MemoryOutputStream& inMOS, const SocketAddress& inToAddress );
	int ReceiveFrom( MemoryInputStream& inMIS, SocketAddress& outFromAddress );
	*/

    // 开启非阻塞模式
	int SetNonBlockingMode( bool inShouldBeNonBlocking );

private:
	friend class SocketUtil;
	UDPSocket( SOCKET inSocket ) : mSocket( inSocket ) {}
	SOCKET mSocket;

};

typedef shared_ptr< UDPSocket >	UDPSocketPtr;