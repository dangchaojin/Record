#include <iostream>
#include <vector>

typedef unsigned int UINT;
std::vector<UINT> vec;
UINT result = 20;
int main()
{
	for (UINT i = 11; i >= 0; i--)
	{
		result += i;
		vec.push_back(i);
	}

	std::cout << result << std::endl;
	return 0;
}
