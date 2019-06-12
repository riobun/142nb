// Single Proxy：单机时转发命令
// 杜玫，2019.06.11


#include "GameHead.h"

unique_ptr<SingleProxy> SingleProxy::sInstance;

bool SingleProxy::StaticInit()
{
    sInstance.reset(new SingleProxy());
    return true;
}

void SingleProxy::SingleUpdate()
{
    CommandList::sInstance->ProcessCommands();
}