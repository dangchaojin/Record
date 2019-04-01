//虚函数的作用就是实现多态性;  多态性是将接口域实现经行分离;
//关键：用指向基类的指针或引用操作对象
#include <iostream>

class A
{
public:
	A(){}
	virtual ~A(){}   //优秀的程序员常常把基类的析构函数定义为虚函数!!!!!!
	void show() { std::cout << "<show> this is aa." << std::endl; }

	//把基类的成员函数设为virtual,其派生类的相应的函数也会自动变为虚函数
	virtual void print() { std::cout << "<print> this is A." << std::endl; }

	virtual void fun(){ std::cout << "A::fun" << std::endl; }
	virtual void fun2(){ std::cout << "A::fun2" << std::endl; }
};

class B : public A
{
public:
	B(){}
	~B(){}
	void show() { std::cout << "<show> this is b." << std::endl; }

	void print() { std::cout << "<print> this is B." << std::endl; }
	
	void fun(){ std::cout << "B::fun" << std::endl;}
	void fun2(){ std::cout << "B::fun2" << std::endl;}
};

int main()
{
	std::cout << "*******************************分界线*******************************" << std::endl;
	std::cout << "***************************测试构造、引用***************************" << std::endl;

	A a;
	B b;
	a.show();
	b.show();

	B *bb = new B();
	bb->show();

	A *aaa = new B();
	aaa->show();
	//B *bbb = new A();  //No

	A *aaaa = &a;
	aaaa->show();
	A *aaaa1 = &b;     //
	aaaa1->show();
	//B *bbbb = &a;   //No

	std::cout << "*******************************分界线*******************************" << std::endl;
	std::cout << "*****************************测试虚函数*****************************" << std::endl;

	/* 如print不是虚函数(像上面的aaaa和aaaa1一样)，则以下两个皆输出: <print> this is A.可
	是p2明明指向的是class B的对象但却是调用的class A的print()函数，这不是我们所期望的结果*/
	A *p1 = &a;
	A *p2 = &b;
	p1->print();
	p2->print();
	//结论:指向基类的指针在操作它的多态类对象时，会根据不同
	//的类对象，调用其相应的函数，这个函数就是虚函数


	std::cout << "*******************************分界线*******************************" << std::endl;
	std::cout << "**************************虚函数实质思考题**************************" << std::endl;
	
	void(A::*fun)();//定义一个函数指针
	A *p=new B;
	fun=&A::fun;
	(p->*fun)();
	fun=&A::fun2;  //想想答案
	(p->*fun)();  //参考虚函数百度百科：https://baike.baidu.com/item/虚函数/2912832?fr=aladdin
	delete p;


	system("pause");
	return 0;
}

/*定义虚函数的限制：
（1）非类的成员函数不能定义为虚函数，类的成员函数中静态成员函数和构造函数也不能定义为
虚函数，但可以将析构函数定义为虚函数。实际上，优秀的程序员常常把基类的析构函数定义为虚
函数。因为，将基类的析构函数定义为虚函数后，当利用delete删除一个指向派生类定义的对象指
针时，系统会调用相应的类的析构函数。而不将析构函数定义为虚函数时，只调用基类的析构函数。
（2）只需要在声明函数的类体中使用关键字“virtual”将函数声明为虚函数，而定义函数时不需要
使用关键字“virtual”。 （3）当将基类中的某一成员函数声明为虚函数后，派生类中的同名函
数（函数名相同、参数列表完全一致、返回值类型相关）自动成为虚函数。
（4）如果声明了某个成员函数为虚函数，则在该类中不能出现和这个成员函数同名并且返回值、参
数个数、类型都相同的非虚函数。在以该类为基类的派生类中，也不能出现和这个成员函数同名并
且返回值、参数个数、类型都相同的非虚函数。
*/