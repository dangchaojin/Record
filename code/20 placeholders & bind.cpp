//在C++中，可调用实体主要包括：函数、函数指针、函数引用、可以隐式转换为函数指定的对象，或者实现了opetator()的对象。
//C++11中，新增加了一个std::function类模板，它是对C++中现有的可调用实体的一种类型安全的包裹。通过指定它的模板参数，
//它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟执行它们。


#include <iostream>
#include <functional>   //std::bind
using namespace std;

void func(int x, int y)
{
    cout << x << " " << y << endl;
}

int main()
{
    bind(func, 1, 2)();                     //输出：1 2
    bind(func, std::placeholders::_1, 2)(1);//输出：1 2

    using namespace std::placeholders;    // adds visibility of _1, _2, _3,...
    bind(func, 2, _1)(1);       //输出：2 1
    bind(func, 2, _2)(1, 2);    //输出：2 2
    bind(func, _1, _2)(1, 2);   //输出：1 2
    bind(func,_2, _1)(1, 2);    //输出：2 1

    //err, 调用时没有第二个参数
    //bind(func, 2, _2)(1);

    return 0;
}

**************************************************************************************************************************

#include <iostream>
#include <functional>   //std::cout
using namespace std;
using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

class Test
{
public:
    int i = 0;

    void func(int x, int y)
    {
        cout << x << " " << y << endl;
    }
};

int main()
{
    Test obj; //创建对象

    function<void(int, int)> f1 = bind(&Test::func, &obj, _1, _2);
    f1(1, 2);   //输出：1 2

    function< int &()> f2 = bind(&Test::i, &obj);
    f2() = 123;
    cout << obj.i << endl;//结果为 123

    return 0;
}