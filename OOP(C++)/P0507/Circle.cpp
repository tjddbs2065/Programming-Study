#include <iostream>
using namespace std;

class Point {
	int xPos;
	int yPos;
public:
	Point(int x, int y) : xPos(x), yPos(y){}
	int getXpos() { return xPos; }
	int getYpos() { return yPos; }
};

class Circle {
	Point center;
	int radius;
public:
	Circle(int x, int y, int r) : center(x, y) { radius = r; }
	void ShowData() {
		cout << "�߽����� " << center.getXpos() << ", " << center.getYpos() << "�Դϴ�." << endl;
		cout << "�������� " << radius << "�� ���� ���̴� " << getArea() << "�Դϴ�." << endl;
	}
	int getArea() { return 3.14 * radius * radius; }
};
int main() {
	Circle cir(10, 10, 15); // �߽��� (10, 10), �������� 15
	cir.ShowData(); // �߽����� 10, 10�Դϴ�. �������� 15�� ���� ���̴� 000�Դϴ�.
}