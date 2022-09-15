#pragma once

#include <iostream>

using  std::cout;
using  std::endl;

void call_StructuredBinding()
{
	//std::tuple
	std::tuple<string, string, int, int, string> userInfo("Tom", "12345", 0, 25, "Pudong Street");
	auto name = std::get<0>(userInfo);
	string password = std::get<1>(userInfo);
	cout << "gender: " << std::get<2>(userInfo) << endl;
	cout << "age: " << std::get<3>(userInfo) << endl;
	cout << "address: " << std::get<4>(userInfo) << endl;

	//结构化绑定
	//形式1
	std::map<int, string> someMap;
	auto [iterator, inserted] = someMap.insert(std::make_pair(1, "hello"));
	cout << "iterator->first, iterator->second: " << iterator->first << " " << iterator->second << " " << "inserted:" << inserted << endl;
	//形式2
	double myArray[3] = { 1.0, 2.0, 3 };
	auto& [a, b, c] = myArray;
	c = 5.0;
	//auto& [h, i, j] = myArray;
	cout << "a, b, c: " << a << " " << b << " " << c << endl;
	cout << "myArray[1,2,3]: " << myArray[0] << " " << myArray[1] << " " << myArray[2] << endl;

	//形式3
	struct Point
	{
		double x;
		double y;
	};
	Point myPoint{ 10.0, 20.0 };
	auto [myX, myY] = myPoint;
	cout << "myX, myY: " << myX << " " << myY << endl;

	map<string, int> cities;
	cities["beijing"] = 0;
	cities["shanghai"] = 1;
	cities["shenzhen"] = 2;
	cities["guangzhou"] = 3;

	for (auto& [cityName, cityNumber] : cities)
	{
		cout << "" << cityName << " " << cityNumber << endl;
	}

	auto [first, second] = pair<int, int>{1,2};
	static auto [firstV2, secondV2] = pair<int, int>{ 1,2 };
	cout << firstV2 << ": " << secondV2 << endl;
	//constexpr auto [firstV3, secondV3] = pair<int, int>{ 1,2 }; 编译不通过
}

void call_Emplace()
{
	class Test
	{
	private:
		int ma;
		int mb;
		int mc;

	public:
		Test(int a, int b, int c)
		{
			ma = a;
			mb = b;
			mc = c;
			cout << "Test constructed." << endl;
		}

		~Test()
		{
			cout << "Test destructed." << endl;
		}

		Test(const Test& rhs)
		{
			if (this == &rhs)
				return;

			this->ma = rhs.ma;
			this->mb = rhs.mb;
			this->mc = rhs.mc;

			cout << "Test copy-constructed." << endl;
		}

	};

	list<Test> collections;
	for (int i = 0; i < 10; ++i)
	{
		Test t(i*1, i*2, i*3);
		collections.push_back(t);
	}

	for (int i = 0; i < 10; ++i)
	{
		collections.emplace_back(i * 1, i * 2, i * 3);
	}

	int x;
}
