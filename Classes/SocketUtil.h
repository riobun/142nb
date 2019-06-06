// SocketUtil��
//����UDP socket
//      UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
//      mySock->SetNonBlockKingMode(true); ���÷�����
//�������
//* ����socket��setsockopt() p92 *

//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.01

/*��Ϸѭ��
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
            //UDPSocketΨһ���캯����˽�еģ�������Ԫ��
	static TCPSocketPtr	CreateTCPSocket( SocketAddressFamily inFamily );

private:

	inline static fd_set* FillSetFromVector( fd_set& outSet, const vector< TCPSocketPtr >* inSockets, int& ioNaxNfds );
	inline static void FillVectorFromSet( vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet );
};