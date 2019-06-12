//Single Proxy: ����ģʽ��ת������Ĵ���
// ��õ��2019.06.09

#ifndef _SINGLE_PROXY_H_
#define _SINGLE_PROXY_H_

class SingleProxy
{
public:
    static unique_ptr< SingleProxy >	sInstance;

    static bool	StaticInit();
    void SingleUpdate();

private:
    SingleProxy()
    {}
    ~SingleProxy()
    {}

    CommandList mCommandList;

};

#endif // _SINGLE_PROXY_H_