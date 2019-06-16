//  SocketUtil��
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.01

#include "NetworkHead.h"

bool SocketUtil::StaticInit()
{
#if _WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if ( iResult != NO_ERROR )
	{
		ReportError ("Starting Up");
		return false;
	}
#endif
	return true;
}

void SocketUtil::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif
}


void SocketUtil::ReportError( const char* inOperationDesc )
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();
	
	FormatMessage(
				  FORMAT_MESSAGE_ALLOCATE_BUFFER |
				  FORMAT_MESSAGE_FROM_SYSTEM |
				  FORMAT_MESSAGE_IGNORE_INSERTS,
				  NULL,
				  errorNum,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				  (LPTSTR) &lpMsgBuf,
				  0, NULL );
	
	
	LOG_SU( "Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf );
#else
	LOG_SU( "Error: %hs", inOperationDesc );
#endif
}

int SocketUtil::GetLastError()
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
	
}

UDPSocketPtr SocketUtil::CreateUDPSocket( SocketAddressFamily inFamily )
{
	SOCKET s = socket( inFamily, SOCK_DGRAM, IPPROTO_UDP );
	
	if( s != INVALID_SOCKET )
	{
		return UDPSocketPtr( new UDPSocket( s ) );
	}
	else
	{
		ReportError( "SocketUtil::CreateUDPSocket" );
		return nullptr;
	}
}