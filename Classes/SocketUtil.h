// SocketUtil类
//创建UDP socket
//      UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
//      mySock->SetNonBlockKingMode(true); 设置非阻塞
//处理错误
//* 配置socket：setsockopt() p92 *

//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.01

/*游戏循环
    while(gIsGameRunning)
    {
        char data[1500];
        SocketAddress socketAddress;
        int bytesReceived = mySock->ReceiveFrom(data, sizeof(data), socketAddress);
        if (bytesReceived > 0)
        {
            ProcessReceivedData(data, bytesReceived, socketAddress);
        }
        DoGameFrame();
    }
*/

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
public:

	static bool			StaticInit();
	static void			CleanUp();

	static void			ReportError( const char* inOperationDesc );
	static int			GetLastError();

	static int			Select( const vector< TCPSocketPtr >* inReadSet,
								vector< TCPSocketPtr >* outReadSet,
								const vector< TCPSocketPtr >* inWriteSet,
								vector< TCPSocketPtr >* outWriteSet,
								const vector< TCPSocketPtr >* inExceptSet,
								vector< TCPSocketPtr >* outExceptSet );

	static UDPSocketPtr	CreateUDPSocket( SocketAddressFamily inFamily );
            //UDPSocket唯一构造函数是私有的；是其友元类
	static TCPSocketPtr	CreateTCPSocket( SocketAddressFamily inFamily );

private:

	inline static fd_set* FillSetFromVector( fd_set& outSet, const vector< TCPSocketPtr >* inSockets, int& ioNaxNfds );
	inline static void FillVectorFromSet( vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet );
};