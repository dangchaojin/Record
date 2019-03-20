#include <iostream>

void fun(int)
{
	std::cout << "fuck1" << std::endl;
}
//C++中的NULL，其实就是一个0

void fun(void *)
{
	std::cout << "fuck2" << std::endl;
}
//C++规定nullptr可以转为指针类型。而且是cv void *

int main(int argc, char *argv[])
{
	fun(NULL);
	std::cout << std::endl;
	fun(nullptr);
	system("pause");
	return 0;
}


// https://www.cnblogs.com/Philip-Tell-Truth/p/6594632.html