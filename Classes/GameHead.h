#ifndef _GAME_HEAD_H
#define _GAME_HEAD_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;
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

#include"cocos2d.h"
//using namespace cocos2d;

#include<string.h>
#include "NetworkHead.h"



#include"ControllerListener.h"
#include"Controller1.h"
#include"HeroMoveController.h"
#include "MemoryBitStream.h"
#include"Entity.h"
#include"Hero.h"
#include"LaneTower.h"

#include "GameObjectRegistry.h"
#include "Command.h"
#include "CommandList.h"

#include "TurnData.h"
#include "NetworkInit.h"
#include "NetworkManager.h"

#include"TollgateScene.h"
#include"HelloWorldScene.h"

#define PRI_SPEED  30
#define SPRITE_SIZE 0.3
#define MOUSE_SIZE 0.5
#define Cystal_SIZE 0.6


typedef enum
{
	map_Tag = 99,
	mHero_Tag = 100,
	eHero_Tag = 101,
	mSoldier_Tag = 200,
	eSoldier_Tag = 201,
	mTower_Tag = 300,
	eTower_Tag = 301,
	mDiamond_Tag = 400,
	eDiamond_Tag = 401
}SpriteTags;


#endif //_GAME_HEAD_H

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