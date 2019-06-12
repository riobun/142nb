//Single Proxy: 单机模式中转发命令的代理
// 杜玫，2019.06.09

#include "GameHead.h"

unique_ptr<SingleProxy> SingleProxy::sInstance;

bool SingleProxy::StaticInit()
{
    sInstance.reset(new SingleProxy());
}

void SingleProxy::SingleUpdate()
{
    CommandList::sInstance->ProcessCommands();
}