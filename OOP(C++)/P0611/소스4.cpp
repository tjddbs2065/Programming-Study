#include <iostream>
using namespace std;
class Point {
	int xpos;
	int ypos;
public:
	Point(int a = 0, int b = 0) {
		xpos = a;
		ypos = b;
	}
	void show() {
		cout << xpos << ", " << ypos << endl;
	}
	friend Point operator+(const Point& p1, const Point& p2);
	friend Point& operator+=(Point& p1, const Point& p2);
	friend Point& operator--(Point& p1);
	friend const Point operator--(Point& p1, int);

};
Point operator+(const Point& p1, const Point& p2) {
	Point tmp;
	tmp.xpos = p1.xpos + p2.xpos;
	tmp.ypos = p1.ypos + p2.ypos;
	return tmp;
}
Point& operator+=(Point& p1, const Point& p2) {
	p1.xpos += p2.xpos;
	p1.ypos += p2.ypos;
	return p1;
}
Point& operator--(Point& p1) {
	p1.xpos--;
	p1.ypos--;
	return p1;
}
const Point operator--(Point& p1, int) {
	Point tmp(p1);
	p1.xpos = --tmp.xpos;
	p1.ypos = --tmp.ypos;
	return tmp;
}
int main() {
	Point pos1(10, 20), pos2(20, 30), pos3;
	pos3 = pos1 + pos2;//operator + (pos1, pos2)
	pos3.show();

	Point pos4 = pos1 += pos2;//operator+=(pos1, pos2)
	pos1.show();
	pos4.show();

	Point pos5 = --pos1;//operator--(pos1)
	pos1.show();
	pos5.show();

	Point pos6 = pos1--;//operator--(pos1, int)
	pos1.show();
	pos6.show();
	return 0;
}