#include "SharedPtr.h"

#include <memory>
#include <iostream>

//using std::auto_ptr;

using std::unique_ptr;
using std::make_unique;

using std::shared_ptr;
using std::make_shared;

using std::cout;
using std::endl;

unique_ptr<int> func(int val)
{
    unique_ptr<int> up(new int(val));
    return up;
}

void SharedPtr::test()
{
    ////std::auto_ptr
    ////初始化方式1
    //auto_ptr<int> ap1(new int(8));
    //cout << "  *ap1: " << *ap1 << "  ap1.get(): " << ap1.get() << endl;
    ////初始化方式2
    //auto_ptr<int> ap2;
    //ap2.reset(new int(8));
    //cout << "  *ap2: " << *ap2
    //    << "  ap2.get(): " << ap2.get() << endl;

    ////测试拷贝构造
    //auto_ptr<int> ap3(new int(2));
    //auto_ptr<int> ap4(ap3);
    //if (nullptr != ap3.get())
    //{
    //    cout << "ap3 is not nullptr" << endl;
    //}else {

    //    cout << "ap3 is nullptr" << endl;
    //}

    //if (nullptr != ap4.get())
    //{
    //    cout << "ap4 is not nullptr" << endl;
    //}else {
    //    cout << "ap4 is nullptr" << endl;
    //}

    ////测试赋值构造
    //auto_ptr<int> ap5(new int(5));
    //auto_ptr<int> ap6 = ap5;
    //if (nullptr != ap5.get())
    //{
    //    cout << "ap5 is not nullptr" << endl;
    //}
    //else {

    //    cout << "ap5 is nullptr" << endl;
    //}

    //if (nullptr != ap6.get())
    //{
    //    cout << "ap6 is not nullptr" << endl;
    //}
    //else {
    //    cout << "ap6 is nullptr" << endl;
    //}

    //-----------------------------------------------


    //std::unique_ptr
    //初始化方式1
    unique_ptr<int> usp1(new int(23));

   //初始化方式2
    unique_ptr<int> usp2;
    usp2.reset(new int(88));

   //初始化方式3
    unique_ptr<int> usp3 = make_unique<int>(99);

    //std::unique_ptr 拷贝构造函数和赋值运算符都被删除
    //unique_ptr<int> usp4(make_unique<int>(99));
    //unique_ptr<int> usp5(usp4);
    //unique_ptr<int> usp6 = usp4;

    //可以通过一个函数返回一个 std::unique_ptr
    unique_ptr<int> usp7 =  func(345);
    cout << "*usp7: " << *usp7 << endl;

    //使用移动构造
    unique_ptr<int> usp8(make_unique<int>(99));
    cout << "usp8: " << usp8 << endl;
    unique_ptr<int> usp9(std::move(usp8));
    cout << "usp8: " << usp8 << "  usp9: " << usp9 << endl;
    unique_ptr<int> usp10 = std::move(usp9);
    cout << "usp8: " << usp8 << "  usp9: " << usp9 << "  usp10: "<< usp10 << endl;

    //std::unique_ptr还可以持有一组堆对象
    //创建10个int类型的堆对象
    //形式1
    unique_ptr<int[]> usp11(new int[10]);
    //形式2
    unique_ptr<int[]> usp12;
    usp12.reset(new int[10]);
    //形式3
    unique_ptr<int[]> usp13 = make_unique<int[]>(10);
    for (int i = 0; i < 10; ++i)
    {
        usp11[i] = i;
        usp12[i] = i;
        usp13[i] = i;
    }

    for (int i = 0; i < 10; ++i)
    {
        cout << usp11[i] << ", " << usp12[i] << ", " << usp13[i] << endl;
    }

    //-----------------------------------------------





    shared_ptr<int> sp1 = make_shared<int>(42);
    cout << "sp1: " << sp1 << "  *sp1: " << *sp1
        << "  sp1.get(): " << sp1.get() << endl;



}