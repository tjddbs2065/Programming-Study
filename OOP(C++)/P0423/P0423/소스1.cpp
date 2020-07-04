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

	cout << "사각형의 가로, 세로를 입력하세요: ";
	cin >> w >> h;

	Rectangle rect(w, h);
	cout << "사각형의 면적은 " << rect.showArea() << endl;*/

	int year, month, day;

	cout << "년 월 일을 입력하세요: ";
	cin >> year >> month >> day;
	
	Calendar today(year, month, day);
	cout << "오늘은 " << today.getYear() << "년 " << today.getMonth() << "월 " << today.getDay() << "일 입니다." << endl;

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