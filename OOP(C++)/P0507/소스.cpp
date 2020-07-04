class Point {
	int xpos;
	int ypos;
public:
	Point(int x, int y) : xpos(x), ypos(y) {

	}
	int getXpos() { return xpos; }
	int getYpos() { return ypos; }

};
class Rectangle {
	Point lefttop;
	Point rightbottom;
public:
	Rectangle(int x, int y, int z, int w) : lefttop(x,y), rightbottom(z, w)
	{}
	void showData() {
		cout << "ÁÂ»ó´ÜÀº " << lefttop
		cout << "ÁÂ»ó´ÜÀº "
	}

};