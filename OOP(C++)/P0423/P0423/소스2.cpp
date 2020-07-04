#include <iostream>
using namespace std;

class Rectangle {
private:
	int width, height;
public:
	Rectangle();
	Rectangle(int w, int h);
	Rectangle(int len);
	bool isSquare(); 
};

int main(void) {
	Rectangle rect1;
	Rectangle rect2(3, 5);
	Rectangle rect3(3);

	if (rect1.isSquare())
		cout << "rect1은 정사각형이다." << endl;
	if (rect2.isSquare())
		cout << "rect2은 정사각형이다." << endl;
	if (rect3.isSquare())
		cout << "rect3은 정사각형이다." << endl;

	return 0;
}

bool Rectangle::isSquare() {
	if (width == height)
		return true;
	else
		return false;
}
Rectangle::Rectangle() {
	width = 1;
	height = 1;
}

Rectangle::Rectangle(int w, int h) {
	width = w;
	height = h;
}
Rectangle::Rectangle(int len) {
	width = len;
	height = len;
}