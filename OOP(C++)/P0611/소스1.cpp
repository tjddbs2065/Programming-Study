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
	//레퍼런스를 사용하지 않는 이유는 지역변수이기 때문에 소멸되기에 복사해서 사용한다.
	Power operator+(const int num) {
		Power tmp;
		tmp.kick = kick + num;
		tmp.punch = punch + num;
		return tmp;
	}
	Power operator+(const Power &pow) {
		Power tmp;
		tmp.kick = kick + pow.kick;
		tmp.punch = punch + pow.punch;
		return tmp;
	}
	Power& operator+=(const Power& pow) {
		kick += pow.kick;
		punch += pow.punch;
		return *this;
	}
	bool operator==(const Power pow) {
		if (kick == pow.kick && punch == pow.punch)
			return true;
		else return false;
	}
};

int main(void) {
	Power a(1, 2), b(2, 3), c, d, e;
	c = a + b;
	c.show();

	d = (a += b);
	a.show();
	d.show();

	if (a == d)
		cout << "두 객체는 같다." << endl;
	else
		cout << "두 객체는 다르다." << endl;

	e = a + 2;
	e.show();

 	return 0;
}