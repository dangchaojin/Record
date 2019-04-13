#include <iostream>

bool test(int aa)
{
	int bb = 123, cc = 12;
	aa = bb + cc;
	return true;
}

bool test_and(int &aa)    //&  ??  非类函数的给私有变量赋值
{
	int bb = 123, cc = 12;
	aa = bb + cc;
	return true;
}

int main()
{
	int a = 0;
	
	std::cout << a << std::endl;

	std::cout << "***************test****************" << std::endl;
	
	test(a);

	std::cout << a << std::endl;
	
	std::cout << "*************test_and**************" << std::endl;
	
	test_and(a);

	std::cout << a << std::endl;


	return 0;
}