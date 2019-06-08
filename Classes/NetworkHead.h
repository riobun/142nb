// NetworkHead.h:    网络库头文件
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#ifndef  _NETWORK_HEAD_H_
#define  _NETWORK_HEAD_H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include "memory"

#include "vector"
#include "array"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"
#include "map"
#include "random"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;
using std::map;

//class RoboCat;
//class GameObject;//待定义
/* 自定义类示范
class Quaternion
{
public:
    float		mX, mY, mZ, mW;
};
*/

#include "cocos2d.h"

#include "StringUtils.h"
#include "RandGen.h"
#include "Timing.h"
#include "WeightedTimedMovingAverage.h"

#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"

//#include "MemoryBitStream.h"

#endif // _NETWORK_HEAD_H_


/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//音乐格式.aifc
//#define bg_music_1   "sound/home_bg.aifc"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//音乐格式.wav

#else
//音乐格式.mp3

#endif
*/