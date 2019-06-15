// Single Proxy������ʱת������
// ��õ��2019.06.11

/*
    ����ģʽ�ӿڣ�
    ��ʼ��������������SingleProxy::StaticInit();
    ���������������У���Command.h��������ģʽ��ͬ
    ÿ��ѭ�����£�SingleProxy::sInstance->Update();
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