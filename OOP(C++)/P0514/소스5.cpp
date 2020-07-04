#include <iostream>
using namespace std;

void swapPointer(int* (&a), int* (&b)) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void) {
	int num1 = 5;
	int* ptr1 = &num1;
	int num2 = 10;
	int* ptr2 = &num2;

	cout << *ptr1 << ' ' << *ptr2 << endl;
	swapPointer(ptr1, ptr2);
	cout << *ptr1 << ' ' << *ptr2 << endl;

	return 0;
}