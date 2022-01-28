//在C++中，可调用实体主要包括：函数、函数指针、函数引用、可以隐式转换为函数指定的对象，或者实现了opetator()的对象。
//C++11中，新增加了一个std::function类模板，它是对C++中现有的可调用实体的一种类型安全的包裹。通过指定它的模板参数，
//它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟执行它们。


#include <iostream>
using namespace std;

int main()
{
    int j = 12;
    auto by_val_lambda = [=] { return j + 1;};
    auto by_ref_lambda = [&] { return j + 1;};
    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    j++;
    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    return 0;
}

// 第3次调用结果还是13，原因是由于by_val_lambda中，j被视为了一个常量，一旦初始化后不会再改变。

**************************************************************************************************************************

#include <iostream>
using namespace std;

class MyFunctor
{
public:
    MyFunctor(int tmp) : round(tmp) {}
    int operator()(int tmp) { return tmp + round; }

private:
    int round;
};

int main()
{
    //仿函数
    int round = 2;
    MyFunctor f1(round);//调用构造函数
    cout << "result1 = " << f1(1) << endl; //operator()(int tmp)

    //lambda表达式
    auto f2 = [=](int tmp) -> int { return tmp + round; } ;
    cout << "result2 = " << f2(1) << endl;

    return 0;
}