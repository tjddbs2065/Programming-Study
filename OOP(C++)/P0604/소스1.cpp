#include <iostream>
using namespace std;

int sum(int a, int b) {
	int result = 0;
	for (int i = a; i <= b; i++) result += i;
	return result;
}
int sum(int a) {
	int result = 0;
	for (int i = 1; i <= a; i++) result += i;
	return result;
}

int main(void) {
	cout << sum(3, 5) << endl;
	cout << sum(3) << endl;
	cout << sum(100) << endl;
	return 0;
}