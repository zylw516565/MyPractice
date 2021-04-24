#pragma once

//C++必须掌握的pimpl 惯用法


#include <memory>

//方式1:
//类中包含类型为 Impl 的指针成员变量
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




//方式2:
//类中包含类型为 Impl 的智能指针成员变量
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
