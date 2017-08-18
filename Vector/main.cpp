#include "vector.h"
#include <iostream>

using namespace std;

void output(int);

int main()
{
	int a[10] = { 2,6,8,5,9,1,0,3,4,7 };
	int* pa = a;
	Vector<int> myVec = Vector<int>(pa, 10);
	myVec.traverse(output);
	cout << endl;
	myVec.quickSort();
	myVec.traverse(output);
	cout << endl;



	cin.get();
	return 0;
}


void output(int num)
{
	cout << num << ' ';
}