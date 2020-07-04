#include <iostream>
using namespace std;

class MyVector {
	int* p;
	int size;
public:
	
	MyVector(int size = 100){
		this->size = size;
		p = new int[size];
	}

	~MyVector() { delete[] p; }
};

int main(void) {
	MyVector* v1, * v2;
	v1 = new MyVector();
	v2 = new MyVector(1024);
	
	delete v1;
	delete v2;

	return 0;
}