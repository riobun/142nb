// Single Proxy：单机时转发命令
// 杜玫，2019.06.11

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