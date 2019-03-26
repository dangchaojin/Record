#pragma once

#ifndef _FIRSTCLASS_H_
#define _FIRSTCLASS_H_
//头部顺序为：文件引用、宏定义、类型定义、常量定义、类定义、函数原型定义 
#include <iostream>

class FirstClass   //类名采用大小写结合的方法，不同单词之间不要用下划线连接
{
//“.h”文件中，接口的定义应按照先函数，后变量
//函数要求先构造/析构函数，再公用函数、保护函数、私有函数的顺序
//变量要求先公有，再保护，后私有的顺序
public:
	FirstClass(int pNum);
	FirstClass();
	~FirstClass();
	
	void Show();           //函数名一般采用大小写字母结合的形式
	void DisplayOfIf();    //函数名的首字母一般情况下建议大写
	
protected:

private:


public:   //以下为变量

protected:

private:
    int m_num;    //类的成员变量统一在前面加m_前缀（member）
};

//要求必须在此注释出此“#endif”对应于哪个"#ifdef"
#endif //_FIRSTCLASS_H_