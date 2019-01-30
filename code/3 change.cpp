#include <iostream>
using namespace std;


/*无需中间变量的交换两个数的其他方法*/
void swap11_sub(int &i, int &j)
{
	i = i + j;
	j = i - j;
	i = i - j;
}
void swap22_XOR(int &i, int &j)
{
	i ^= j;
	j ^= i;
	i ^= j;
}
void swap33(int &i, int &j)
{
	i = i + j - (j = i);
}

/*交换三种方式区别*/
void change1(int x, int y)
{
	int temp;
	temp = x; x = y; y = temp;
}
/*change1函数被调用时，创建两个临时变量x和y，属于change1的局部变量.
当change1函数被调用进行参数传递，main中x和y传给change1中临时变量x和y.
在change1交换的是change1的临时变量x和y的值，与main中x、y无关.
所以这种参数传递（称为值传递）无法实现交换两个变量的值*/

void change2(int* x, int* y)
{
	int temp;
	temp = *x; *x = *y; *y = temp;
}
/*指针传递（地址传递）
函数调用实参是main中x和y的地址，在change中操作*x和*y实际上是在操作main中x和y
*/

void change3(int &x, int &y)
{
	int temp;
	temp = x; x = y; y = temp;
}
/*引用传递
change3被调用时通过参数传递将change3的x和y初始化为main中x和y的别名，
访问change3的x和y与访问main中x和y效果是一样的*/

int main()
{
	int mm = 11, nn = 22;
	cout << "initial: " << mm << "	" << nn << endl;
	change1(mm, nn);
	cout << "change1: " << mm << "	" << nn << endl;
	cout << "*************************************************************" << endl;

	cout << "initia: " << mm << "	" << nn << endl;
	change2(&mm, &nn);
	cout << "change2: " << mm << "	" << nn << endl;
	cout << "*************************************************************" << endl;

	cout << "initial: " << mm << "	" << nn << endl;
	change3(mm, nn);
	cout << "change3: " << mm << "	" << nn << endl;
	cout << "*************************************************************" << endl;

	int x = 6, y = 5;
	cout << "initial: " << x << "	" << y << endl;
	swap11_sub(x, y);
	cout << "swap11_sub: " << x << "	" << y << endl;
	cout << "*************************************************************" << endl;

	int a = 8, b = 7;
	cout << "initial: " << a << "	" << b << endl;
	swap22_XOR(a, b);
	cout << "swap22_XOR: " << a << "	" << b << endl;
	cout << "*************************************************************" << endl;

	int m = 21, n = 22;
	cout << "initial: " << m << "	" << n << endl;
	swap33(m, n);
	cout << "awap33(false): " << m << "	" << n << endl;

	system("pause");
	return 0;
}

/*
1、不能建立数组的引用.

2、可以将变量的引用的地址赋给一个指针，此时指针指向的是原来的变量.
如： int a = 3;    int &b = a;    int* p = &b;

3、可以建立指针变量的引用.
如： int a = 3;    int* p = &a;    int* &rp = p;


由于引用不是一种独立的数据类型，不能建立指向引用的指针变量.
如： int & *p = &a; 是错误的
*/
