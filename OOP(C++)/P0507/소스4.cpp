#include <iostream>
using namespace std;

class Point {

};

int main(void) {
	int* ptr = new int;
	int* ptr1 = new int[5];

	delete ptr;
	delete [] ptr1;

	return 0;
}