#include "PimplMode.h"



//��ʽ1:
//���а�������Ϊ Impl ��ָ���Ա����
class CSocketClient::Impl
{

public:

    //һЩ����,�ɹ���ָ�����

public:
    short                           m_nPort;
    char                            m_szServer[64];
    long                            m_nLastDataTime;        //���һ���շ����ݵ�ʱ��
    long                            m_nHeartbeatInterval;   //������ʱ��������λ��
};

CSocketClient::CSocketClient()
{
    m_pImpl = new Impl();
}

CSocketClient::~CSocketClient()
{
    delete m_pImpl;
}

short CSocketClient::getPort() 
{
    return m_pImpl->m_nPort;
}





//��ʽ2:
//���а�������Ϊ Impl ������ָ���Ա����
class CSocketClientV2::Impl
{

public:

    //һЩ����,�ɹ���ָ�����

public:
    short                           m_nPort;
    char                            m_szServer[64];
    long                            m_nLastDataTime;        //���һ���շ����ݵ�ʱ��
    long                            m_nHeartbeatInterval;   //������ʱ��������λ��
};


CSocketClientV2::CSocketClientV2()
 :m_pImpl(std::make_unique<Impl>())
{
}

CSocketClientV2::~CSocketClientV2()
{
}

short CSocketClientV2::getPort()
{
    return m_pImpl->m_nPort;
}