// SocketAddressFactory��
// ���ַ�������SocketAddress, ����������ָ��

//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.01

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString( const string& inString );
};