#include <iostream>
//#include <cstdlib>
#include <windows.h>
using namespace std;

/*判断一个正整数num是否为2的N次方
基本思想： 

十进制           二进制           N - 1           N & N - 1         是否为2的乘方
8                 1000            111             0                 是
16                10000           1111            0                 是
32                100000          11111           0                 是
100               1100100         1100011         1100000             否

算法的时间复杂度为O（1）,空间复杂度为O（1）
*/

bool Is2pow(unsigned int num)
{
	if (num == 0)
	{
		return false;
	}
	return (num & (num - 1)) == 0;
}

/*
计算一个正整数num转化为二进制后，0 的个数
基本思想：从右到左依次与1进行与操作，并统计其个数
算法的计算次数只与num的位数有关，与其大小无关
算法的时间复杂度为O（logN），空间复杂度为O（1）
*/

unsigned int NumberofZero(unsigned int num)
{
	unsigned int count = 0;
	while (num)
	{
		if ((num & 0x01) != 1)
		{
			count++;
		}
		num = num >> 1;
	}
	return count;
}

/*
计算一个正整数num转化为二进制后，1 的个数
基本思想：从右到左依次去除1，并统计其个数
算法的计算次数只与num的位数有关，与其大小无关
算法的时间复杂度为O（logN），空间复杂度为O（1）
*/

unsigned int NumberofOne(unsigned int num)
{
	unsigned int count = 0;
	while (num)
	{
		num = num & ( num - 1);
		count++;
	}
	return count;
}

int main()
{
	unsigned int m = 12, n = 32;

	cout << m << "是否为2的N次方: " << Is2pow(m) << endl;
	cout << n << "是否为2的N次方: " << Is2pow(n) << endl;

	cout << "********************************************************" << endl;

	cout << m << "转化为二进制后，0的个数: " << NumberofZero(m) << endl;

	cout << "********************************************************" << endl;

	cout << n << "转化为二进制后，1的个数: " << NumberofOne(n) << endl;

	//让结果窗口暂停
	//cin.get();
	//getchar();
	system("pause");
	//Sleep(10000);   
	/*      Windows下为--> windows.h       Linux 下为--> unistd.h
		（1）Sleep是区分大小写的，有的编译器是大写，有的是小写
		（2）Sleep括号里的时间，在windows下是已毫秒为单位，而Linux是以秒为单位*/
	return 0;
}

