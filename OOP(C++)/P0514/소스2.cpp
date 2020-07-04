#include <iostream>
#include <string>
using namespace std;

//		call by value
//
//void swap(int a, int b) {
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(num1, num2); // call by value
//	cout << num1 << ' ' << num2 << endl;
//	
//	return 0;
//}
//		call by reference
//		- 주소를 이용한 call by reference
//void swap(int* a, int* b) {
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(&num1, &num2); // call by value
//	cout << num1 << ' ' << num2 << endl;
//
//	return 0;
//}

//	reference  (참조)
//	 - 이름을 지니는 공간에 별명을 붙이는 것(단, 기호 상수 제외)
//	 - 데이터형 & 레퍼런스명 = 대상;

	//int num = 10;
	//int& ref = num;
	//cout << &num << " " << &ref << endl;

	//int* ptr = &num;
	//int* (&refptr) = ptr;
	
	//int arr[3] = {10, 20, 30};
	//int &ref = arr[0];

	//Circle donut;
	//Circle &objref = donut;

	//Circle* ptr = new Circle;
	//Circle* (&ref) = ptr;

//		- reference를 이용한 call by reference
//void swap(int& a, int& b) {
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main() {
//	int num1 = 10, num2 = 20;
//	cout << num1 << ' ' << num2 << endl;
//	swap(num1, num2); // call by reference
//	cout << num1 << ' ' << num2 << endl;
//
//	return 0;
//}
//	int a = 10
// int &ref1 = 10; // 상수는 메모리에 값이 올라가지만 이름이 없기에 &ref로 별명을 지어줄 수 없다.
// int &ref2;

//클래스 객체를 매개변수로 전달할 때 call by value로 보내게 되면 생성자가 호출되지 않지만, 함수가 종료될 때 소멸자가 호출되어 비대칭 호출이 된다.
//이를 해결하기 위해서는 객체의 메모리 주소를 매개변수로 전달해서 실제 객체의 값을 변경해 주어야 한다.

class Circle {
	int radius;
public:
	Circle(int r) { radius = r; }
	int getRadius() { return radius; }
	void setRadius(int r) { radius = r; }
	void show() { cout << "반지름이 " << radius << "인 원" << endl; }
};

void increaseBy(Circle* x, Circle* y);
void increaseByRef(Circle& x, Circle& y);

int main(void) {
	Circle x(10), y(5);

	//increaseBy(&x, &y);
	increaseByRef(x, y);
	x.show();

	return 0;
}

void increaseBy(Circle* x, Circle* y) {
	x->setRadius(x->getRadius() + y->getRadius());
}

void increaseByRef(Circle& x, Circle& y) {
	x.setRadius(x.getRadius() + y.getRadius());
}

