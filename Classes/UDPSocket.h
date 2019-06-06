// UDPSocket��
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ��2019.06.01

class UDPSocket
{
public:

	~UDPSocket();

    //�󶨶˿�
	int Bind( const SocketAddress& inToAddress ); 

    // ���ͣ�
    //������������ʼָ�룻���ݴ�С��<1300��������
    //�ɹ����뷢�Ͷ����򷵻ش����͵����ݳ��ȣ�ʧ�ܷ���-1
	int SendTo( const void* inToSend, int inLength, const SocketAddress& inToAddress );

    // ���գ�
    //�������ݵĻ�����ָ�룻�������洢����ֽ���(�������)�������ߵ�ַ�洢
    //�ɹ������Ѹ����ֽ�����ʧ�ܷ���-1
	int ReceiveFrom( void* inToReceive, int inMaxLength, SocketAddress& outFromAddress );

	/*
	int SendTo( const MemoryOutputStream& inMOS, const SocketAddress& inToAddress );
	int ReceiveFrom( MemoryInputStream& inMIS, SocketAddress& outFromAddress );
	*/

    // ����������ģʽ
	int SetNonBlockingMode( bool inShouldBeNonBlocking );

private:
	friend class SocketUtil;
	UDPSocket( SOCKET inSocket ) : mSocket( inSocket ) {}
	SOCKET mSocket;

};

typedef shared_ptr< UDPSocket >	UDPSocketPtr;