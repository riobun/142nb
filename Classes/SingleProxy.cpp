//Single Proxy: ����ģʽ��ת������Ĵ���
// ��õ��2019.06.09

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