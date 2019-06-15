// SocketUtil��
//����UDP socket
//      UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
//      mySock->SetNonBlockKingMode(true); ���÷�����
//�������
//* ����socket��setsockopt() p92 *

//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.01

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
            //UDPSocketΨһ���캯����˽�еģ�������Ԫ��
};