#include <iostream>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int r) { radius = r; }
	int getRadius() { return radius; }
	void setRadius(int r) { radius = r; }
	void show() { cout << "반지름이 " << radius << "인 원" << endl; }
};
void swap(Circle& a, Circle& b) {
	Circle tmp = a;
	a = b;
	b = tmp;
}

int main(void) {
	Circle c1(30);
	Circle c2(100);

	cout << "호출전 c1 c2의 반지름" << endl;
	cout << "c1의 반지름" << c1.getRadius() << " c2의 반지름 " << c2.getRadius() << endl;
	swap(c1, c2);
	cout << "호출 후 c1 c2의 반지름" << endl;
	cout << "c1의 반지름" << c1.getRadius() << " c2의 반지름 " << c2.getRadius() << endl;

	return 0;
}