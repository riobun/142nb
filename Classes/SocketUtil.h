// SocketUtil类
//创建UDP socket
//      UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
//      mySock->SetNonBlockKingMode(true); 设置非阻塞
//处理错误
//* 配置socket：setsockopt() p92 *

//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.01

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

	static UDPSocketPtr	CreateUDPSocket( SocketAddressFamily inFamily );
            //UDPSocket唯一构造函数是私有的；是其友元类
};