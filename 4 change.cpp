#include <iostream>
using namespace std;


/*�����м�����Ľ�������������������*/
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

/*�������ַ�ʽ����*/
void change1(int x, int y)
{
	int temp;
	temp = x; x = y; y = temp;
}
/*change1����������ʱ������������ʱ����x��y������change1�ľֲ�����.
��change1���������ý��в������ݣ�main��x��y����change1����ʱ����x��y.
��change1��������change1����ʱ����x��y��ֵ����main��x��y�޹�.
�������ֲ������ݣ���Ϊֵ���ݣ��޷�ʵ�ֽ�������������ֵ*/

void change2(int* x, int* y)
{
	int temp;
	temp = *x; *x = *y; *y = temp;
}
/*ָ�봫�ݣ���ַ���ݣ�
��������ʵ����main��x��y�ĵ�ַ����change�в���*x��*yʵ�������ڲ���main��x��y
*/

void change3(int &x, int &y)
{
	int temp;
	temp = x; x = y; y = temp;
}
/*���ô���
change3������ʱͨ���������ݽ�change3��x��y��ʼ��Ϊmain��x��y�ı�����
����change3��x��y�����main��x��yЧ����һ����*/

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
1�����ܽ������������.

2�����Խ����������õĵ�ַ����һ��ָ�룬��ʱָ��ָ�����ԭ���ı���.
�磺 int a = 3;    int &b = a;    int* p = &b;

3�����Խ���ָ�����������.
�磺 int a = 3;    int* p = &a;    int* &rp = p;


�������ò���һ�ֶ������������ͣ����ܽ���ָ�����õ�ָ�����.
�磺 int & *p = &a; �Ǵ����
*/