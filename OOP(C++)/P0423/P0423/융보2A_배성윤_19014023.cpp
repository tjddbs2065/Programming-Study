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
	//��ü�� stack ������ �����Ǳ� ������ �������� ������ ��ü�� ���� �Ҹ��Ų��.
	//destructor : ��ü �ȿ� ���� �Ҵ�� �޸𸮰� ���� ��� ��ü�� �Ҹ��� �� �޸𸮸� ������ �־�� �Ѵ�.
	//�Ҹ��ڴ� �����ε��� ���� �ʴ´�.

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
	cout << "����: " << add << " ����: " << min << " ����: " << mul << " ������: " << div << endl;
}