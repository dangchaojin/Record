#include <iostream>
//using namespace std;

//设定结构体、联合以及类成员变量以 n 字节方式对齐
//#pragma pack(push)  // 保存对齐状态
//#pragma pack(n)                      // https://blog.csdn.net/hairetz/article/details/4084088

//...

//#pragma pack(pop)   // 恢复对齐状态

union un1
{
	char buffer[13];
	int number;
}ubu;

struct ss1
{
	char c;
	int i;
};
struct ss2
{
};

class BU
{
	int number;
	union UBffer
	{
		char buffer[13];
		int number;            //一个Class对象占用内存空间为：非静态成员变量总和+ 数据对齐处理+虚函数。
	}ubuf;                     //int=4，union=13+1=14，enum=4（内存中当成int来存储），4+14+4=22，f只是一个定义，不是实际上的指针，没有占字节。
	void foo() {}               //另外 union的大小取决于它所有的成员中，占用空间最大的一个成员的大小，并且需要内存对齐，
	typedef char*(*f)(void*);  //这里因为#pragma pack(2)，所以union的大小为14，如果不写#pragma pack(2),
	enum { hdd, ssd, blueray }disk;  //那么union大小为16【因为与sizeof（int）=4对齐】
	int *a;
}bu;

void func(char str[100])
{
    cout << sizeof(str);      //此处的str也是跟指针一样的字节数，实际上是str是指针，后面的100实际上是无用的
}

int main()
{
	char s1[] = "Hello";
	char *p1 = s1;
	int n = 10;
	char s2[100] = "0123456789";
	void *p2 = malloc(100);

	int *pint;  char *p111;                  //在C语言中指针是一个unsigned类型的无符号数，其所占内存字节一般是和计算机的CPU字长是一致的，
											 //拿32位计算机来说，指针所占的内存空间一般为4个字节，不管char *还是int *抑或是float *，都是4个字节。
											 //char *p 是一个指针,它保存的内容是一个地址,指向(*p)，而（*p)才是那个字节


	std::cout << "s1: " << sizeof(s1) << std::endl;
	std::cout << "p1: " << sizeof(p1) << std::endl;
	std::cout << "int	n: " << sizeof(n) << std::endl;
	std::cout << "s2: " << sizeof(s2) << std::endl;
	std::cout << "malloc	p2: " << sizeof(p2) << std::endl;

	std::cout << "纯指针	pint: " << sizeof(pint) << "	p111: " << sizeof(p111) << std::endl;

	std::cout << "struct	ss1: " << sizeof(ss1) << std::endl;
	std::cout << "struct	ss2: " << sizeof(ss2) << std::endl;

	std::cout << "union: " << sizeof(ubu) << std::endl;
	std::cout << "bu: " << sizeof(bu) << std::endl;                  //一个Class对象占用内存空间为非静态成员变量总和+ 数据对齐处理+虚函数

	system("pause");
	return 0;
}