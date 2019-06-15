// NetworkProxy:    网络库主要接口
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

/*
    联机模式接口：
    初始化网络库：Network::StaticInit(std::string name, bool tobe_master_peer, uint16_t inPort, std::string addr)
    添加命令至命令队列：见Command.h，与单机模式相同
    每次循环更新：Network::sInstance->Update();
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
