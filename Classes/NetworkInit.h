// NetworkInit.h:    ��ʼ�������
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

/*˵����

    ��ʼ������⣺Network::StaticInit(std::string& player_name);
    �������ӽ������,������Network::StaticInit->TryStartGame();

    ��ѯ����ʾ���û��¼���������CommandList���������
    InputManager()->HandleInput();

    ��ѯ����ʾ�û��¼����Ѵ������������
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

/*���Կ���ֱ�ӵ��õ�ģ���ӳ٣�
  *GetSimulatedLatency()
  *SetSimulatedLatency()
  *ʾ����
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