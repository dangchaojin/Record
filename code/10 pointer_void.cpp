#include <iostream>

void test(int aa, void *pa)
{
	int *ppa = (int*)pa;
	std::cout << aa << std::endl;
	std::cout << *pa << std::endl;   //illegal indirection, ÒòÎªvoid
	std::cout << *ppa << std::endl;
	std::cout << &pa << std::endl;
}

int main()
{
	int a = 12;
	int* pp = &a;

	std::cout << a << std::endl;
	std::cout << pp << std::endl;
	std::cout << *pp << std::endl;
	std::cout << &pp << std::endl;

	std::cout << "*******************************" << std::endl;

	test(a, pp);


	return 0;
}