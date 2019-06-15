// Single Proxy：单机时转发命令
// 杜玫，2019.06.11

/*
    单机模式接口：
    初始化单机代理器：SingleProxy::StaticInit();
    添加命令至命令队列：见Command.h，与联机模式相同
    每次循环更新：SingleProxy::sInstance->Update();
*/

#ifndef _SINGLE_PROXY_H_
#define _SINGLE_PROXY_H_

class SingleProxy
{
public:
    static unique_ptr< SingleProxy >	sInstance;

    ~SingleProxy()
    {}

    static bool	StaticInit();
    void SingleUpdate();

private:
    SingleProxy()
    {}

    CommandList mCommandList;

};

#endif // _SINGLE_PROXY_H_