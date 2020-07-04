#include <iostream>

void increment(int& r) {
	r++;
}
int main(void) {
	int num = 10;//&num
	std::cout << num << std::endl;
	increment(num);
	//increment(&num);
	std::cout << num << std::endl;
	return 0;
}