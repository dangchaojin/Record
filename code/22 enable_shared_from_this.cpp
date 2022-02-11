//std::enable_shared_from_this 能让其一个对象（假设其名为 t ，且已被一个 std::shared_ptr 对象 pt 管理）安全地生成其他额外的 std::shared_ptr 实例（假设名为 pt1, pt2, … ） ，它们与 pt 共享对象 t 的所有权。
//若一个类 T 继承 std::enable_shared_from_this ，则会为该类 T 提供成员函数： shared_from_this 。 当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr 类对象管理时，调用 T::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr 对象，它与 pt 共享 t 的所有权。


//需要在类对象的内部中获得一个指向当前对象的 shared_ptr 对象。
//如果在一个程序中，对象内存的生命周期全部由智能指针来管理。在这种情况下，要在一个类的成员函数中，对外部返回this指针就成了一个很棘手的问题。


//当一个类被 share_ptr 管理，且在类的成员函数里需要把当前类对象作为参数传给其他函数时，这时就需要传递一个指向自身的 share_ptr。
//一般来说，我们不能直接将this指针返回。如果函数将 this 指针返回到外部某个变量保存，然后这个对象自身已经析构了，但外部变量并不知道，此时如果外部变量再使用这个指针，就会使得程序崩溃。


#include <iostream>
#include <stdlib.h>
#include <memory>
using namespace std;

// 比较推荐的写法
struct Good : std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};

// 错误的用法：用不安全的表达式试图获得 this 的 shared_ptr 对象
struct Bad
{
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};
 
int main()
{
    // 正确的用法: 两个 shared_ptr 共享同一个对象
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
 
    // 错误的用法: 调用 shared_from_this 但其没有被 std::shared_ptr 占有 
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } 
    catch(std::bad_weak_ptr& e) {
        // 在 C++17 之前，编译器不能捕获 enable_shared_from_this 抛出的std::bad_weak_ptr 异常
        // 这是在C++17之后才有的特性
        std::cout << e.what() << '\n';    
    }
 
    // 错误的用法，每个 shared_ptr 都认为自己是对象的唯一拥有者
    // 调用错误的用法，会导致两次析构 Bad的对象，第二次析构时，指针指向的空间已经被析构，
    // 会导致程序出错
    std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
    std::cout << "bp1.use_count() = " << bp1.use_count() << '\n';
    std::shared_ptr<Bad> bp2 = bp1->getptr();
    std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';

    return 0;
}