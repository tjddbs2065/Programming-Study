#include <iostream>
using namespace std;

class Person {
	double money; // ���� ������ ��
	static int sharedMoney; // ����
public:
	Person(int money) {
		this->money = money;
	}
	void addMoney(int money) {
		this->money += money;
	}
	static void addShared(int n) {
		sharedMoney += n;
	}
	void show() {
		cout << "���� : " << this->money << "\t���� : " << sharedMoney << endl;
	}
};
int Person::sharedMoney = 10;  // 10���� �ʱ�ȭ


int main() {
	Person han(100);
	//han.money = 100; // han�� ���� ��=100	
	han.addShared(200);

	Person lee(150);
	//lee.money = 150; // lee�� ���� ��=150
	lee.addMoney(200); // lee�� ���� ��=350
	Person::addShared(200); // static ��� ����, ����=400

	han.show(); //���� 100, ���� 400��
	lee.show(); //���� 350, ���� 400��
}