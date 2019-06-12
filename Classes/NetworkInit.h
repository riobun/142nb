// NetworkInit.h:    初始化网络库
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

/*说明：

    初始化网络库：Network::StaticInit(std::string& player_name);
    所有连接建立完成,主机：Network::StaticInit->TryStartGame();

    轮询器显示有用户事件待处理：在CommandList中添加命令
    InputManager()->HandleInput();

    轮询器显示用户事件都已处理：发送网络包
    Network::sInstance->Update();
*/
#ifndef _NET_WORK_INIT_H_
#define _NET_WORK_INIT_H_

class Network
{
public:
    static bool StaticInit(std::string name, bool tobe_master_peer = false, uint16_t inPort = default_port, std::string addr = default_addr);
    virtual ~Network();
    static std::unique_ptr< Network>	sInstance;

    void        Update();
    void			SetShouldKeepRunning(bool inShouldKeepRunning) { mShouldKeepRunning = inShouldKeepRunning; }
    //bool      wantbe_master_peer;
protected:
    Network();

private:
    //int		DoRunLoop();
    bool	mShouldKeepRunning;
};

#endif // !_NET_WORK_INIT_H_

/*调试可以直接调用的模拟延迟：
  *GetSimulatedLatency()
  *SetSimulatedLatency()
  *示例：
case '+':
    case '=':
        {
            float latency = NetworkManager::sInstance->GetSimulatedLatency();
            latency += 0.1f;
            if( latency > 0.5f )
            {
                latency = 0.5f;
            }
            NetworkManager::sInstance->SetSimulatedLatency( latency );
            break;
        }
    case '-':
        {
            float latency = NetworkManager::sInstance->GetSimulatedLatency();
            latency -= 0.1f;
            if( latency < 0.0f )
            {
                latency = 0.0f;
            }
            NetworkManager::sInstance->SetSimulatedLatency( latency );
            break;
        }*/