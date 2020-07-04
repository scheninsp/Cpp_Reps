// n stairs , 1 or 2 per step

#include "stdafx.h"
#include <iostream>

using namespace std;
int stairsSolution(int n)
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	if (n == 2)
	{
		return 2;
	}
	int s1 = 1;
	int s2 = 2;
	int temp = 0;
	for (int i = 3; i < n + 1; i++)
	{
		temp = s1 + s2;
		s1 = s2;
		s2 = temp;
	}
	return temp;
}

int main()
{
	cout << stairsSolution(10);

	getchar();

	return 0;
}
