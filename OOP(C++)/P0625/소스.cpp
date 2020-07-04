#include <iostream>
using namespace std;

class adder {
public:
	int add(int a, int b) { return a + b; }
};
class subtractor {
public:
	int minus(int a, int b) { return a - b; }
};
class Calculator : public adder, public subtractor {
public:
	int calc(char op, int a, int b) {
		switch (op)
		{
		case '+':
			return add(a, b);
			break;
		case '-':
			return minus(a, b);
			break;
		}
	}
};
int main() {
	Calculator handCalculator;
	cout << "2 + 4 = " << handCalculator.calc('+', 2, 4) << endl;
	cout << "100 - 8 = " << handCalculator.calc('-', 100, 8) << endl;
}