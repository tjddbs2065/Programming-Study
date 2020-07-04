#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	void show() {
		cout << "kick: " << kick << "\tpunch:" << punch << endl;
	}
	Power& operator--() {
		kick--;
		punch--;
		return *this;
	}
	const Power operator--(int) {
		Power tmp;
		tmp.kick = --kick;
		tmp.punch = --punch;
		return tmp;
	}
};
int main() {
	Power a(10, 10);
	Power b = --a;
 