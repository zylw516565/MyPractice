#include "PimplMode.h"



//方式1:
//类中包含类型为 Impl 的指针成员变量
class CSocketClient::Impl
{

public:

    //一些方法,可供用指针调用

public:
    short                           m_nPort;
    char                            m_szServer[64];
    long                            m_nLastDataTime;        //最近一次收发数据的时间
    long                            m_nHeartbeatInterval;   //心跳包时间间隔，单位秒
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





//方式2:
//类中包含类型为 Impl 的智能指针成员变量
class CSocketClientV2::Impl
{

public:

    //一些方法,可供用指针调用

public:
    short                           m_nPort;
    char                            m_szServer[64];
    long                            m_nLastDataTime;        //最近一次收发数据的时间
    long                            m_nHeartbeatInterval;   //心跳包时间间隔，单位秒
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