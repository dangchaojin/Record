#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void GetMemory(char *&p)
{
    p = (char*)malloc(100);  //只是赋给临时变量而已，所以没有给到外面的str赋值，要是引用就可以
}

int main()
{
    char* str = NULL;
    GetMemory(str);
    strcpy(str, "hello world");    //会产生段错误
    cout << str << endl;
    return 0;
}

//----------------------------------------------------------------------------------------------------------------

char *GetMemory(void)
{
	char p[] = "hello world";    //临时变量，退出会被释放
	return p;
}

int main()
{
	char* str = NULL;
	str = GetMemory();
	cout << str << endl;    //所以打印的是null
	return 0;
}

//----------------------------------------------------------------------------------------------------------------

void GetMemory(char **p, int num)
{
	*p = (char*)malloc(num);   //*p实际上就是对str进行操作了
}

int main()
{
	char* str = NULL;
	GetMemory(&str, 100);    //因为传的是str的地址
	strcpy(str, "hello");
	cout << str << endl;
	return 0;
}

//----------------------------------------------------------------------------------------------------------------

int main()
{
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str);
	if(str != NULL) {        //free只是释放申请的堆空间，没有对指针置空，所以str不为空
		strcpy(str, "world");
		cout << str << endl;   //linux和win都会段错误，但是win可能会打出world
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------