#include <iostream>
using namespace std;

void swap11(int &i, int &j)
{
	i = i + j;
	j = i - j;
	i = i - j;
}

void swap22(int &i, int &j)
{
	i ^= j;
	j ^= i;
	i ^= j;
}

void swap33(int &a, int &b)
{
	a = a + b - (b=a);
}

int main()
{
	int x = 6, y = 5;
	cout << "initial: " << x  << "	" << y << endl;
	swap11(x, y);
	cout << "awap11: " << x  << "	" << y << endl;
	cout << "**********************************************************************" << endl;

	int a = 8, b = 7;
	cout << "initial: " << a  << "	" << b << endl;
	swap22(a, b);
	cout << "awap22: " << a  << "	" << b << endl;
	cout << "**********************************************************************" << endl;

	int m = 21, n = 22;
	cout << "initial: " << m  << "	" << n << endl;
	swap22(m, n);
	cout << "awap22: " << m  << "	" << n << endl;
    
    return 0;
}
