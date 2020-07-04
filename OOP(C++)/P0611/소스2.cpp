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
	Point& operator++() {
		xpos++;
		ypos++;
		return *this;
	}
	const Point operator++(int) {
		Point tmp(xpos, ypos);
		xpos++;
		ypos++;
		return tmp;
	}
};
int main() {
	Point pos1(2, 3);
	Point pos2 = ++(++pos1); // pos1.operator++()
	pos1.show();
	pos2.show();

	Point pos3 = pos1++; // pos1.operator++(int)
	pos1.show();
	pos3.show();

	return 0;
}