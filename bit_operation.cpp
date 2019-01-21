#include <iostream>
//#include <cstdlib>
#include <windows.h>
using namespace std;

/*�ж�һ��������num�Ƿ�Ϊ2��N�η�
����˼�룺 

ʮ����           ������           N - 1           N & N - 1         �Ƿ�Ϊ2�ĳ˷�
8                 1000            111             0                 ��
16                10000           1111            0                 ��
32                100000          11111           0                 ��
100               1100100         1100011         1100000             ��

�㷨��ʱ�临�Ӷ�ΪO��1��,�ռ临�Ӷ�ΪO��1��
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
����һ��������numת��Ϊ�����ƺ�0 �ĸ���
����˼�룺���ҵ���������1�������������ͳ�������
�㷨�ļ������ֻ��num��λ���йأ������С�޹�
�㷨��ʱ�临�Ӷ�ΪO��logN�����ռ临�Ӷ�ΪO��1��
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
����һ��������numת��Ϊ�����ƺ�1 �ĸ���
����˼�룺���ҵ�������ȥ��1����ͳ�������
�㷨�ļ������ֻ��num��λ���йأ������С�޹�
�㷨��ʱ�临�Ӷ�ΪO��logN�����ռ临�Ӷ�ΪO��1��
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

	cout << m << "�Ƿ�Ϊ2��N�η�: " << Is2pow(m) << endl;
	cout << n << "�Ƿ�Ϊ2��N�η�: " << Is2pow(n) << endl;

	cout << "********************************************************" << endl;

	cout << m << "ת��Ϊ�����ƺ�0�ĸ���: " << NumberofZero(m) << endl;

	cout << "********************************************************" << endl;

	cout << n << "ת��Ϊ�����ƺ�1�ĸ���: " << NumberofOne(n) << endl;

	//�ý��������ͣ
	//cin.get();
	//getchar();
	system("pause");
	//Sleep(10000);   
	/*      Windows��Ϊ--> windows.h       Linux ��Ϊ--> unistd.h
		��1��Sleep�����ִ�Сд�ģ��еı������Ǵ�д���е���Сд
		��2��Sleep�������ʱ�䣬��windows�����Ѻ���Ϊ��λ����Linux������Ϊ��λ*/
	return 0;
}

