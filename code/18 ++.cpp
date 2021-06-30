#include <stdio.h>
struct m {
	int x;
	int *y;
}*p;
int a[4] = {12, 33, -40, 100};
struct m b[4] = {10, &a[2], 9, &a[3], 8, &a[0], 7, &a[1]};

int main()
{
	p = b;
	printf("%d\n", p->x);    // 10
	printf("%d %d\n", p->x, ++p->x);    //这行 p->x 和 ++p->x 输出一样，应该是统一先算出值，才打印
	
	printf("%d\n", (++p)->x);
	printf("%d\n", ++(*p->y));
    return 0;
}

int main1()
{
    int a=10,b,c,d;
	b = a++;       //先把值给出去再++
	c = ++a;       //先++再把值给出去
	d = 10*a++;    //先把值给出去再++
	cout << "b, c, d: " << b << ", " << c << ", " << d << endl;
    return 0;
}

