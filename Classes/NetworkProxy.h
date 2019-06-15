// NetworkProxy:    �������Ҫ�ӿ�
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

/*
    ����ģʽ�ӿڣ�
    ��ʼ������⣺Network::StaticInit(std::string name, bool tobe_master_peer, uint16_t inPort, std::string addr)
    ���������������У���Command.h���뵥��ģʽ��ͬ
    ÿ��ѭ�����£�Network::sInstance->Update();
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

protected:
    Network()
    {}

private:
    bool	mShouldKeepRunning;
};

#endif // !_NET_WORK_INIT_H_
