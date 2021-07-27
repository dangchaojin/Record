#include <iostream>
#include <memory>
using namespace std;
class AA {
public:
    AA();
    ~AA();
    void Display();
};

AA::AA()
{
    cout << "AA." << endl;
}
AA::~AA()
{
    cout << "~AA." << endl;
}
void AA::Display()
{
    cout << "display a:" << endl;
}

int main()
{
    shared_ptr<AA> testA;
    testA->Display();   // 应该指向代码区？所以运行不会报错？而有成员的时候会报错，是因为需要申请实际空间？
    cout << "test1" << endl;

    if (testA == nullptr) {
        testA = make_shared<AA>();
    }

    testA->Display();
    return 0;
}