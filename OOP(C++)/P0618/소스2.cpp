#include <iostream>
using namespace std;

class Rectangle {
	int w, h;
public:
	Rectangle(int w, int h) :w(w), h(h) {}
	void ShowAreaInfo() {
		cout << "¸éÀû: "<< w * h << endl;
	}
};
class Square : public Rectangle {
public:
	Square(int l) : Rectangle(l, l){}
};

int main() {
	Rectangle rect(4, 3);
	rect.ShowAreaInfo();

	Square sqr(7);
	sqr.ShowAreaInfo();

	return 0;
}