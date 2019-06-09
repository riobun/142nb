// NetworkInit:    ��ʼ�������
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

#include "GameHead.h"

unique_ptr< Network > Network::sInstance;

Network::Network()
{

}

bool Network::StaticInit(std::string name, bool tobe_master_peer, uint16_t inPort, std::string addr)
{
    RandGen::StaticInit();
    SocketUtil::StaticInit();
    CommandList::StaticInit();
    sInstance.reset(new Network());//Ψһʵ��
    //EntityRegistry::StaticInit();
    //EntityRegistry::sInstance->RegisterCreationFunction('HERO', Hero::StaticCreate);
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
        //World::sInstance->Update(delta);????��д
        NetworkManager::sInstance->ProcessIncomingPackets();
        NetworkManager::sInstance->SendOutgoingPackets();
    }
    else
    {
        //only grab the incoming packets because if I'm in delay,
        //the only way I'm getting out is if an incoming packet saves me
        NetworkManager::sInstance->ProcessIncomingPackets();
    }

}