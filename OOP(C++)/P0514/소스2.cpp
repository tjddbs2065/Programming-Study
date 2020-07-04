#include <iostream>
#include <string>
using namespace std;

//		call by value
//
//void swap(int a, int b) {
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(num1, num2); // call by value
//	cout << num1 << ' ' << num2 << endl;
//	
//	return 0;
//}
//		call by reference
//		- �ּҸ� �̿��� call by reference
//void swap(int* a, int* b) {
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(&num1, &num2); // call by value
//	cout << num1 << ' ' << num2 << endl;
//
//	return 0;
//}

//	reference  (����)
//	 - �̸��� ���ϴ� ������ ������ ���̴� ��(��, ��ȣ ��� ����)
//	 - �������� & ���۷����� = ���;

	//int num = 10;
	//int& ref = num;
	//cout << &num << " " << &ref << endl;

	//int* ptr = &num;
	//int* (&refptr) = ptr;
	
	//int arr[3] = {10, 20, 30};
	//int &ref = arr[0];

	//Circle donut;
	//Circle &objref = donut;

	//Circle* ptr = new Circle;
	//Circle* (&ref) = ptr;

//		- reference�� �̿��� call by reference
//void swap(int& a, int& b) {
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(num1, num2); // call by reference
//	cout << num1 << ' ' << num2 << endl;
//
//	return 0;
//}
//	int a = 10
// int &ref1 = 10; // ����� �޸𸮿� ���� �ö����� �̸��� ���⿡ &ref�� ������ ������ �� ����.
// int &ref2;

//Ŭ���� ��ü�� �Ű������� ������ �� call by value�� ������ �Ǹ� �����ڰ� ȣ����� ������, �Լ��� ����� �� �Ҹ��ڰ� ȣ��Ǿ� ���Ī ȣ���� �ȴ�.
//�̸� �ذ��ϱ� ���ؼ��� ��ü�� �޸� �ּҸ� �Ű������� �����ؼ� ���� ��ü�� ���� ������ �־�� �Ѵ�.

class Circle {
	int radius;
public:
	Circle(int r) { radius = r; }
	int getRadius() { return radius; }
	void setRadius(int r) { radius = r; }
	void show() { cout << "�������� " << radius << "�� ��" << endl; }
};

void increaseBy(Circle* x, Circle* y);
void increaseByRef(Circle& x, Circle& y);

int main(void) {
	Circle x(10), y(5);

	//increaseBy(&x, &y);
	increaseByRef(x, y);
	x.show();

	return 0;
}

void increaseBy(Circle* x, Circle* y) {
	x->setRadius(x->getRadius() + y->getRadius());
}

void increaseByRef(Circle& x, Circle& y) {
	x.setRadius(x.getRadius() + y.getRadius());
}

