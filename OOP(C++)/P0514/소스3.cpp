#include <iostream>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int r) { radius = r; }
	int getRadius() { return radius; }
	void setRadius(int r) { radius = r; }
	void show() { cout << "�������� " << radius << "�� ��" << endl; }
};
void swap(Circle& a, Circle& b) {
	Circle tmp = a;
	a = b;
	b = tmp;
}

int main(void) {
	Circle c1(30);
	Circle c2(100);

	cout << "ȣ���� c1 c2�� ������" << endl;
	cout << "c1�� ������" << c1.getRadius() << " c2�� ������ " << c2.getRadius() << endl;
	swap(c1, c2);
	cout << "ȣ�� �� c1 c2�� ������" << endl;
	cout << "c1�� ������" << c1.getRadius() << " c2�� ������ " << c2.getRadius() << endl;

	return 0;
}