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
	//���۷����� ������� �ʴ� ������ ���������̱� ������ �Ҹ�Ǳ⿡ �����ؼ� ����Ѵ�.
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
		cout << "�� ��ü�� ����." << endl;
	else
		cout << "�� ��ü�� �ٸ���." << endl;

	e = a + 2;
	e.show();

 	return 0;
}