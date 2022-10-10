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

void call_UniquePtr()
{
	std::unique_ptr<int> sp1(new int(123));

	std::unique_ptr<int> sp2;
	sp2.reset(new int(123));

	std::unique_ptr<int> sp3 = std::make_unique<int>(123);
// 	std::unique_ptr<int> sp4(sp3);
// 	std::unique_ptr<int> sp5 = sp3;
}

shared_ptr<string> testSharedPtrFunc(shared_ptr<string> sp)
{
	cout << "sp.use_count(): " << sp.use_count() << endl;
	return sp;
}

const auto use_factory(const string& arg)
{
	shared_ptr<string> p = make_shared<string>(arg);
	cout << "p.use_count(): " << p.use_count() << endl;
	return p;
}

class StrBlob
{
public:
	typedef vector<string>::size_type size_type;

private:
	shared_ptr<vector<string>> data_;
	void check(size_type i, const string& msg) const;

public:
	StrBlob() = default;
	StrBlob(std::initializer_list<string> il);
	size_type size() const { return data_->size(); }
	bool empty() const { return data_->empty(); }
	//添加和删除元素
	void push_back(const string& t) {data_->push_back(t); }
	void pop_back();

	//元素访问
	string& front();
	string& back();

};

void call_SharedPtr()
{
	std::shared_ptr<string> sp1;

	if (sp1 && sp1->empty())
		*sp1 = "hi";

	*sp1;
	cout << "sp1: " << sp1 << " sp1.get(): " << sp1.get() << endl;

	//sp1->size();
	//(*sp1).empty();
	std::shared_ptr<string> sp2;
	std::swap(sp1, sp2);
	sp1.swap(sp2);

	std::shared_ptr<string> sp3(new string("hello"));
	std::shared_ptr<string> sp4(sp3);
	std::shared_ptr<string> sp5;
	cout << "before swap: " << "sp3.use_count(): " << sp3.use_count() << " sp4.use_count(): " << sp4.use_count() << " sp5.use_count(): " << sp5.use_count() << endl;
	sp5.swap(sp4);
	cout << "after swap: " << "sp3.use_count(): " << sp3.use_count() << " sp4.use_count(): " << sp4.use_count() << " sp5.use_count(): " << sp5.use_count() << endl;

	std::shared_ptr<string> sp6(std::make_shared<string>("world"));
	//std::shared_ptr<int> sp7;
	//sp6.swap(sp7);  //编译不过, sp7中的指针必须能转成string*
	std::shared_ptr<string> sp8(new string("123"));
	cout << "before =: " << " sp6.use_count(): " << sp6.use_count() 
		 << " sp8.use_count(): " << sp8.use_count() << endl;
	sp8 = sp6;

	auto sp9 = std::make_shared<int>();
	auto sp10 = std::make_shared<string>();
	cout << "before call: " << "sp10.use_count(): " << sp10.use_count() << endl;
	testSharedPtrFunc(sp10);
	cout << "after call: " << "sp10.use_count(): " << sp10.use_count() << endl;

	string strArg("hello");
	auto sp11 = use_factory(strArg);
	cout << "sp11.use_count(): " << sp11.use_count() << endl;
}

bool testRetValue(const string& str)
{
	if (str.empty())
	{
		return false;
	}

	for (auto i = 0; i < 10; ++i)
	{
		return true;
	}

}

void call_testRetValue()
{
	cout << "testRetValue(123); " << testRetValue("123") << endl;
}