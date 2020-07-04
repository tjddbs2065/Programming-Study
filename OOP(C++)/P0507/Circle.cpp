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
		cout << "중심점은 " << center.getXpos() << ", " << center.getYpos() << "입니다." << endl;
		cout << "반지름이 " << radius << "인 원의 넓이는 " << getArea() << "입니다." << endl;
	}
	int getArea() { return 3.14 * radius * radius; }
};
int main() {
	Circle cir(10, 10, 15); // 중심점 (10, 10), 반지름이 15
	cir.ShowData(); // 중심점은 10, 10입니다. 반지름이 15인 원의 넓이는 000입니다.
}