#include <iostream>
using namespace std;

class Calculator {
private:
	int add, min, mul, div;
	
public:
	Calculator() {
		add = min = mul = div = 0;
	}
	int Add(int a, int b);
	int Min(int a, int b);
	int Mul(int a, int b);
	double Div(int a, int b);
	void ShowOpCount();
};

int main(void) {
	//객체는 stack 구조로 생성되기 때문에 마지막에 생성된 객체를 먼저 소멸시킨다.
	//destructor : 객체 안에 동적 할당된 메모리가 있을 경우 객체가 소멸할 때 메모리를 해제해 주어야 한다.
	//소멸자는 오버로딩이 되지 않는다.

	Calculator cal;

	cout << "3 + 5 = " << cal.Add(3, 5) << endl;
	cout << "3 / 5 = " << cal.Div(3, 5) << endl;
	cout << "12 - 4 = " << cal.Min(12, 4) << endl;
	cout << "12 / 4 = " << cal.Div(12, 4) << endl;
	cal.ShowOpCount();
	return 0;
}

int Calculator::Add(int a, int b) {
	add += 1;
	return a + b;
}
int Calculator::Min(int a, int b) {
	min += 1;
	return a - b;
}
int Calculator::Mul(int a, int b) {
	mul += 1;
	return a * b;
}
double Calculator::Div(int a, int b) {
	div += 1;
	return a / (double)b;
}
void Calculator::ShowOpCount() {
	cout << "덧셈: " << add << " 뺄셈: " << min << " 곱셈: " << mul << " 나눗셈: " << div << endl;
}