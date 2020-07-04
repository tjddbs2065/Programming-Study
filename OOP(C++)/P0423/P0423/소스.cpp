#include <iostream>
using namespace std;
//
//class Point {
//public:
//	int xpos = 0, ypos = 0; 
//	void ShowData();
//};
//
//int main(void) {
//	Point pos1;
//	pos1.xpos = 10;
//	pos1.ypos = 20;
//	pos1.ShowData();
//
//	Point pos2;
//	pos2.xpos = 30;
//	pos2.ypos = 40;
//	pos2.ShowData();
//
//	return 0;
//}
//
////Point 클래서에서 선언된 ShowData라는 함수를 정의
////선언과 정의를 분리한다.
//void Point::ShowData() {
//	cout << "xpos: " << xpos << " " << "ypos: " << ypos << endl;
//}


class Point {
	//기본은 private이다.
private:
	int xpos, ypos;
public:
	//생성자는 객체가 생성되는 동시에 딱 한번 자동으로 호출되는 멤버함수이다.
	//생성자의 이름은 클래스의 이름과 동일하다
	//생성자는 리턴값이 없고, 하면 안된다. 물론 리턴 타입도 없다.
	//생성자도 선언과 정의를 분리할 수 있다.
	//생성자는 오버로딩을 따라 여러개의 생성자가 존재할 수 있다.
	//생성자는 매개변수가 없을 때 Defualt가 아무값도 안들어가 있는 상태로 호출된다.
	//생성자는 객체가 생성될 때 객체가 필요한 초기화를 위해 사용한다.
	//Point::Point()
	Point(int x, int y) {
		xpos = x;
		ypos = y;
	}
	//void 생성자 = 매개변수가 없는 생성자
	Point() {
		xpos = 0;
		ypos = 0;
	}
	void ShowData() {
		cout << "xpos : " << xpos << "ypos : " << ypos << endl;
	}
};

int main(void) {
	Point pos1(10, 20);
	pos1.ShowData();

	Point pos2(30, 40);
	pos1.ShowData();

	Point pos3
}