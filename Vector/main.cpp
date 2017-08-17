#include "vector.h"
#include <iostream>

using namespace std;

int main()
{
	int a[10] = { 2,6,8,5,9,1,0,3,4,7 };
	int* pa = a;
	Vector<int> myvec = Vector<int>(pa, 9);

	cin.get();
	return 0;
}