#include <iostream>
#include <memory>
using namespace std;


//unique_ptr持有对对象的独有权，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。
//unique_ptr指针本身的生命周期：从unique_ptr指针创建时开始，直到离开作用域。
//离开作用域时，若其指向对象，则将其所指对象销毁(默认使用delete操作符，用户可指定其他操作)。

int main()
{
    unique_ptr<int> up1(new int(11));   // 无法复制的unique_ptr
    //unique_ptr<int> up2 = up1;        // err, 不能通过编译
    cout << *up1 << endl;   // 11

    unique_ptr<int> up3 = move(up1);    // 现在p3是数据的唯一的unique_ptr

    cout << *up3 << endl;   // 11
    //cout << *up1 << endl;   // err, 运行时错误
    up3.reset();            // 显式释放内存
    up1.reset();            // 不会导致运行时错误
    //cout << *up3 << endl;   // err, 运行时错误

    unique_ptr<int> up4(new int(22));   // 无法复制的unique_ptr
    up4.reset(new int(44)); //"绑定"动态对象
    cout << *up4 << endl;

    up4 = nullptr;//显式销毁所指对象，同时智能指针变为空指针。与up4.reset()等价

    unique_ptr<int> up5(new int(55));
    int *p = up5.release(); //只是释放控制权，不会释放内存
    cout << *p << endl;
    //cout << *up5 << endl; // err, 运行时错误
    delete p; //释放堆区资源

    return 0;
}

**************************************************************************************************************************
//shared_ptr允许多个该智能指针共享第“拥有”同一堆分配对象的内存，这通过引用计数（reference counting）实现，
//会记录有多少个shared_ptr共同指向一个对象，一旦最后一个这样的指针被销毁，也就是一旦某个对象的引用计数变为0，这个对象会被自动删除。


int main()
{
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;

    cout << "count: " << sp2.use_count() << endl; //打印引用计数

    cout << *sp1 << endl;   // 22
    cout << *sp2 << endl;   // 22

    sp1.reset();    //显式让引用计数减1
    cout << "count: " << sp2.use_count() << endl; //打印引用计数

    cout << *sp2 << endl;   // 22
    //cout << *sp1 << endl;   // err(只要打印sp1就err，不管先打后打), 段错误(已经释放了一个了)

    system("pause");
    return 0;
}


**************************************************************************************************************************
//weak_ptr是为配合shared_ptr而引入的一种智能指针来协助shared_ptr工作，它可以从一个shared_ptr或另一个weak_ptr对象构造，它的构造和析构不会引起引用计数的增加或减少。
//没有重载 * 和 -> 但可以使用lock获得一个可用的shared_ptr对象
//weak_ptr的使用更为复杂一点，它可以指向shared_ptr指针指向的对象内存，却并不拥有该内存，而使用weak_ptr成员lock，则可返回其指向内存的一个share_ptr对象，且在所指对象内存已经无效时，返回指针空值nullptr。


void check(weak_ptr<int> &wp)
{
    shared_ptr<int> sp = wp.lock(); // 转换为shared_ptr<int>
    if (sp != nullptr)
    {
        cout << "still " << *sp << endl;
    }
    else
    {
        cout << "pointer is invalid" << endl;
    }
}

int main()
{
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    weak_ptr<int> wp = sp1; // 指向shared_ptr<int>所指对象

    cout << "count: " << wp.use_count() << endl; //打印计数器
    cout << *sp1 << endl;   // 22
    cout << *sp2 << endl;   // 22

    check(wp);              // still 22

    sp1.reset();
    cout << "count: " << wp.use_count() << endl;

    cout << *sp2 << endl;   // 22
    check(wp);              // still 22

    sp2.reset();
    cout << "count: " << wp.use_count() << endl;
    check(wp);              // pointer is invalid

    return 0;
}