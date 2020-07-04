#include <iostream>
using namespace std;

class Point {
	int xPos;
	int yPos;
public:
	Point(int x=0, int y=0) : xPos(x), yPos(y) {}
	int getXpos() { return xPos; }
	int getYpos() { return yPos; }
	void ShowPos() { cout << "xÁÂÇ¥ : " << xPos << " yÁÂÇ¥ : " << yPos << endl; }
	void SetXY(int x, int y) { xPos = x; yPos = y; }
};
int main() {
	Point arr[3] = { Point(10, 20), Point(30, 40), Point(40,50) };
	for (int i = 0; i < 3; i++) {
		arr[i].SetXY(i + 1, i + 1);
	}
	for (int i = 0; i < 3; i++)
		arr[i].ShowPos();

	Point* p = arr;
	for (int i = 0; i < 3; i++) {
		p->ShowPos();
		p++;
	}

	return 0;
}