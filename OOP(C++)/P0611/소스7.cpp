#include <iostream>
using namespace std;

class Matrix {
	int arr[4];
public:
	Matrix(int a = 0, int b = 0, int c = 0, int d = 0) {
		arr[0] = a;
		arr[1] = b;
		arr[2] = c;
		arr[3] = d;
	}
	void show() {
		cout << "{ ";
		for (int i = 0; i < 4; i++)
			cout << arr[i] << " ";
		cout << '}' << endl;
	}
	Matrix operator+(Matrix mt2) {
		Matrix tmp;
		for (int i = 0; i < 4; i++)
			tmp.arr[i] = arr[i] + mt2.arr[i];
		return tmp;
	}
	Matrix& operator+=(Matrix mt2) {
		for (int i = 0; i < 4; i++)
			arr[i] += mt2.arr[i];
		return *this;
	}
	bool operator==(Matrix mt2) {
		for (int i = 0; i < 4; i++) {
			if (arr[i] != mt2.arr[i])
				return false;
		}
		return true;
	}
	friend void operator>>(Matrix mt1, int arr[]);
	friend void operator<<(Matrix& mt1, int arr[]);
	/*
	void operator>>(int arr[]) {
		for (int i = 0; i < 4; i++)
			arr[i] = this->arr[i];
	}
	void operator<<(int arr[]) {
		for (int i = 0; i < 4; i++)
			this->arr[i] = arr[i];
	}*/
	/*
	friend Matrix operator+(Matrix mt1, Matrix mt2);
	friend Matrix& operator+=(Matrix& mt1, Matrix mt2);
	friend bool operator==(Matrix mt1, Matrix mt2);*/
};/*
Matrix operator+(Matrix mt1, Matrix mt2) {
	Matrix tmp;
	for (int i = 0; i < 4; i++)
		tmp.arr[i] = mt1.arr[i] + mt2.arr[i];
	return tmp;
}
Matrix& operator+=(Matrix& mt1, Matrix mt2) {
	for (int i = 0; i < 4; i++)
		mt1.arr[i] += mt2.arr[i];
	return mt1;
}
bool operator==(Matrix mt1, Matrix mt2) {
	for (int i = 0; i < 4; i++) {
		if (mt1.arr[i] != mt2.arr[i])
			return false;
	}
	return true;
}*/
void operator>>(Matrix mt1, int arr[]) {
	for (int i = 0; i < 4; i++)
		arr[i] = mt1.arr[i];
}
void operator<<(Matrix &mt1, int arr[]) {
	for (int i = 0; i < 4; i++)
		mt1.arr[i] = arr[i];
}
int main(void) {/*
	Matrix a(1, 2, 3, 4), b(2, 3, 4, 5), c;
	c = a + b;
	a += b;
	a.show(), b.show(), c.show();
	if (a == c) 
		cout << "a and c are the same" << endl;*/
	Matrix a(4, 3, 2, 1), b;
	int x[4], y[4] = { 1,2,3,4 };
	a >> x;
	b << y;

	cout << "{ ";
	for (int i = 0; i < 4; i++) cout << x[i] << ' ';
	cout << '}';
	cout << endl;
	b.show();

	return 0;
}