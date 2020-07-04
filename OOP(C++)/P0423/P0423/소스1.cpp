#include <iostream>
using namespace std;

class Rectangle {
private:
	int width, height;
public:
	Rectangle(int x, int y);
	int showArea();
};

class Calendar {
private:
	int year, month, day;
public:
	Calendar(int y, int m, int d);
	int getYear();
	int getMonth();
	int getDay();
};

int main(void) {
	/*int w, h;

	cout << "�簢���� ����, ���θ� �Է��ϼ���: ";
	cin >> w >> h;

	Rectangle rect(w, h);
	cout << "�簢���� ������ " << rect.showArea() << endl;*/

	int year, month, day;

	cout << "�� �� ���� �Է��ϼ���: ";
	cin >> year >> month >> day;
	
	Calendar today(year, month, day);
	cout << "������ " << today.getYear() << "�� " << today.getMonth() << "�� " << today.getDay() << "�� �Դϴ�." << endl;

	return 0;
}

Rectangle::Rectangle(int x, int y) {
	width = x;
	height = y;
}
Calendar::Calendar(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

int Rectangle::showArea() {
	return width * height;
}

int Calendar::getYear() {
	return year;
}

int Calendar::getMonth() {
	return month;
}

int Calendar::getDay() {
	return day;
}