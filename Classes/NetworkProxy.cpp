// NetworkProxy:    网络库主要接口
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#include "GameHead.h"

namespace NetVar
{
uint16_t my_port = 45000;
std::string my_addr = "127.0.0.1:45000";
std::string my_name = "King";
bool wantbe_master = false;
}

unique_ptr< Network > Network::sInstance;

bool Network::StaticInit(std::string name, bool tobe_master_peer, uint16_t inPort, std::string addr)
{
    RandGen::StaticInit();
    SocketUtil::StaticInit();
    CommandList::StaticInit();
    sInstance.reset(new Network());//唯一实例
    if (tobe_master_peer)
    {
        NetworkManager::StaticInitAsMasterPeer(stoi(addr), name);
    }
    else
    {
        SocketAddressPtr targetAddress = SocketAddressFactory::CreateIPv4FromString(addr);
        if (!targetAddress)
        {
            LOG_SU("ERROR: Unable to create target address from destination.");
            return false;
        }
        NetworkManager::StaticInitAsPeer(*targetAddress, name);
    }

    return true;
}

Network::~Network()
{
    SocketUtil::CleanUp();
}

void Network::Update()
{
    Timing::sInstance.Update();
    if (NetworkManager::sInstance->GetState() != NetworkManager::NMS_Delay)
    {
        float delta = Timing::sInstance.GetDeltaTime();
        NetworkManager::sInstance->ProcessIncomingPackets();
        NetworkManager::sInstance->SendOutgoingPackets();
    }
    else
    {
        NetworkManager::sInstance->ProcessIncomingPackets();
    }

}