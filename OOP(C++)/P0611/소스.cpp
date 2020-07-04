#include <iostream>
using namespace std;

class Point {
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) {
		xpos = x;
		ypos = y;
	}
	void showPos() {
		cout << xpos << ", " << ypos << endl;
	}
	Point operator+ (const Point pos) {
		Point tmp;
		tmp.xpos = xpos + pos.xpos;
		tmp.ypos = ypos + pos.ypos;
		return tmp;
	}
	Point& operator+=(Point& pos) {
		xpos += pos.xpos;
		ypos += pos.ypos;
		return *this;
	}
};
int main(void) {
	Point pos1(10, 20), pos2(20, 30), pos3, pos4;
	pos3 = pos1 + pos2;
	pos4 = (pos1 += pos2) += pos2;

	pos1.showPos();
	pos4.showPos();

	return 0;
}