#include <iostream>
//使用define要注意的地方!!!

#define pin int*
//#define pin (int*)   这样写不可以??

int main(int argc, char *argv[])
{
    pin a, b;

	int i = 1, j = 2;

	int* m = &i;

	int mm, nn;
	mm = a == m;
	nn = b == j;

	std::cout << "a == i ?? : " << mm << std::endl;
	std::cout << "b == i ?? : " << nn << std::endl;

	return 0;
}