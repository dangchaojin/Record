#include "firstclass.h"
//先主函数再子函数，先进程主体继之进程分支再各过程，由大到小的顺序排版
//类的实现部分应按照先构造/析构函数，再公用函数，最后私有函数的顺序排版

/*
FirstClass::FirstClass()
{
	//
}*/

//sizeof来确定数组、结构、联合或变量占用的空间
FirstClass::FirstClass(int pNum = 2)      //好像这个2不可以用作默认构造参数！！！！！！！！！！
{
	m_num = pNum;
}

/*/拷贝构造函数的定义
FirstClass::FirstClass( const FirstClass& CopyTarget)
{
	m_num = CopyTarget.m_num;
}*/

FirstClass::~FirstClass()
{
	//delete[] pBuffer;
}

//对代码的注释应放在其上方或右方（对单条语句的注释）相邻位置，不可放在下面
void FirstClass::Show()
{
	std::cout << m_num << std::endl;
	std::cout << sizeof(m_num) << std::endl;
	std::cout << typeid(m_num).name() << std::endl;      //C++输出变量的类型
	std::cout << sizeof(unsignedint) << std::endl;
	std::cout << typeid(unsignedint).name() << std::endl;      //C++输出变量的类型

	//
}

void FirstClass::DisplayOfIf()
{
	//if、else、for、do、while、case、switch、default等语句自占一行
	//且if、else、for、do、while语句的执行语句部分无论多少都要加括号｛｝
	if ( true )
	{
		//
	}
	return;
}

void Showlog()
{
	std::cout << "logloglogloglog" << std::endl;
}