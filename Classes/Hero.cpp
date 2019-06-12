#include"GameHead.h"
using namespace cocos2d;

bool Hero::init() {
	return true;
}

EntityPtr Hero::StaticCreate() { 
    return NetworkManager::sInstance->RegisterAndReturn(new Hero()); 
}

void Hero::run(Sprite* sprite) {
	
	double iSpeed = PRI_SPEED;
	//Sprite* mouse = Sprite::create("mouse.png");
	//�����¼�����������������¼�
	auto myMouseListener = EventListenerMouse::create();
	//����ƶ�
	myMouseListener->onMouseMove = [=](Event * event) {


void Hero::WriteForCRC(OutputMemoryBitStream& inStream)
{
    inStream.Write(mPlayerId);
    inStream.Write(mNetworkId);
    //inStream.Write(mLocation);
    //inStream.Write(mHealth);
    //inStream.Write(mState);
    //inStream.Write(mTargetNetId);
}
