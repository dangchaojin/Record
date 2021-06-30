#include <iostream>
using namespace std;

int main()
{
	int a[2][3] = {0,2,4,6,8,10};

	cout << *(a+1) << " " << &a[1][0] <<endl;      //理解   *(a+1)是地址
	cout << *(a[1]+1) << " " << a[1][1] <<endl;    //a[1]是地址，地址加一按单位偏移
	cout <<**(a+1) << " " << **(a+1)+2 <<endl;
	cout << a << "	" << a[0] <<endl;
	cout << a[1][2] << endl;
    return 0;
}
