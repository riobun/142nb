// SocketAddressFactory类
// 从字符串创造SocketAddress, 返回其智能指针

//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.01

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString( const string& inString );
};