#include <iostream>
using namespace std;

int big(int a, int b) {
	if (a > b) return a;
	else return b;
}
int big(int arr[], int a) {
	int max = arr[0];
	for (int i = 1; i < a; i++) {
		if (max < arr[i]) max = arr[i];
	}
	return max;
}
int main(void) {

	int array[5] = { 1,9,-2,8,6 };
	cout << big(2, 3) << endl;
	cout << big(array, 5) << endl;
	
	return 0;
}