#pragma once

//C++�������յ�pimpl ���÷�


#include <memory>

//��ʽ1:
//���а�������Ϊ Impl ��ָ���Ա����
class CSocketClient
{
public:
	CSocketClient();
	~CSocketClient();

	short getPort();

private:

	class Impl;
	Impl* m_pImpl;
};




//��ʽ2:
//���а�������Ϊ Impl ������ָ���Ա����
class CSocketClientV2
{
public:
	CSocketClientV2();
	~CSocketClientV2();

	short getPort();

private:

	class  Impl;
	std::unique_ptr<Impl> m_pImpl;
};
