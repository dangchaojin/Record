#include <iostream>
//using namespace std;

//�趨�ṹ�塢�����Լ����Ա������ n �ֽڷ�ʽ����
//#pragma pack(push)  // �������״̬
//#pragma pack(n)                      // https://blog.csdn.net/hairetz/article/details/4084088

//...

//#pragma pack(pop)   // �ָ�����״̬

union un1
{
	char buffer[13];
	int number;
}ubu;

struct ss1
{
	char c;
	int i;
};
struct ss2
{
};

class BU
{
	int number;
	union UBffer
	{
		char buffer[13];
		int number;            //һ��Class����ռ���ڴ�ռ�Ϊ���Ǿ�̬��Ա�����ܺ�+ ���ݶ��봦��+�麯����
	}ubuf;                     //int=4��union=13+1=14��enum=4���ڴ��е���int���洢����4+14+4=22��fֻ��һ�����壬����ʵ���ϵ�ָ�룬û��ռ�ֽڡ�
	void foo() {}               //���� union�Ĵ�Сȡ���������еĳ�Ա�У�ռ�ÿռ�����һ����Ա�Ĵ�С��������Ҫ�ڴ���룬
	typedef char*(*f)(void*);  //������Ϊ#pragma pack(2)������union�Ĵ�СΪ14�������д#pragma pack(2),
	enum { hdd, ssd, blueray }disk;  //��ôunion��СΪ16����Ϊ��sizeof��int��=4���롿
	int *a;
}bu;

void func(char str[100])
{
    cout << sizeof(str);      //�˴���strҲ�Ǹ�ָ��һ�����ֽ�����ʵ������str��ָ�룬�����100ʵ���������õ�
}

int main()
{
	char s1[] = "Hello";
	char *p1 = s1;
	int n = 10;
	char s2[100] = "0123456789";
	void *p2 = malloc(100);

	int *pint;  char *p111;                  //��C������ָ����һ��unsigned���͵��޷�����������ռ�ڴ��ֽ�һ���Ǻͼ������CPU�ֳ���һ�µģ�
											 //��32λ�������˵��ָ����ռ���ڴ�ռ�һ��Ϊ4���ֽڣ�����char *����int *�ֻ���float *������4���ֽڡ�
											 //char *p ��һ��ָ��,�������������һ����ַ,ָ��(*p)������*p)�����Ǹ��ֽ�


	std::cout << "s1: " << sizeof(s1) << std::endl;
	std::cout << "p1: " << sizeof(p1) << std::endl;
	std::cout << "int	n: " << sizeof(n) << std::endl;
	std::cout << "s2: " << sizeof(s2) << std::endl;
	std::cout << "malloc	p2: " << sizeof(p2) << std::endl;

	std::cout << "��ָ��	pint: " << sizeof(pint) << "	p111: " << sizeof(p111) << std::endl;

	std::cout << "struct	ss1: " << sizeof(ss1) << std::endl;
	std::cout << "struct	ss2: " << sizeof(ss2) << std::endl;

	std::cout << "union: " << sizeof(ubu) << std::endl;
	std::cout << "bu: " << sizeof(bu) << std::endl;                  //һ��Class����ռ���ڴ�ռ�Ϊ�Ǿ�̬��Ա�����ܺ�+ ���ݶ��봦��+�麯��

	system("pause");
	return 0;
}