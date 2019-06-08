// NetworkInit:    初始化网络库
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#include "GameHead.h"
const std::string default_player_name = "无名";
const uint16_t default_port = 45000;

unique_ptr< Network > Network::sInstance;

Network::Network()
{

}

bool Network::StaticInit(std::string& name)//NetworkManager?
{
    RandGen::StaticInit();
    SocketUtil::StaticInit();

    //WindowManager::StaticInit()
    //GraphicsDriver::StaticInit( WindowManager::sInstance->GetMainWindow() )

    CommandList::StaticInit();
    sInstance.reset(new Network());//唯一实例

    //assume no colon implies this is just the port, which implies that this is the master peer
    //重写：自动设置端口，设置玩家名字
    /*
    if (destination.find_first_of(':') == string::npos)
    {
        NetworkManager::StaticInitAsMasterPeer(stoi(destination), name);
    }
    else
    {
        SocketAddressPtr targetAddress = SocketAddressFactory::CreateIPv4FromString(destination);
        if (!targetAddress)
        {
            LOG_SU("ERROR: Unable to create target address from destination.");
            return false;
        }
        NetworkManager::StaticInitAsPeer(*targetAddress, name);
    }
    */
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
        //World::sInstance->Update(delta);????重写
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



/*
void Engine::HandleEvent( SDL_Event* inEvent )
{
    switch( inEvent->type )
    {
    case SDL_KEYDOWN:
        InputManager::sInstance->HandleInput( EIA_Pressed, inEvent->key.keysym.sym );
        break;
    case SDL_KEYUP:
        InputManager::sInstance->HandleInput( EIA_Released, inEvent->key.keysym.sym );
        break;
    case SDL_MOUSEBUTTONDOWN:
        InputManager::sInstance->HandleMouseClick( inEvent->button.x, inEvent->button.y, inEvent->button.button );
        break;
    default:
        break;
    }
}*/