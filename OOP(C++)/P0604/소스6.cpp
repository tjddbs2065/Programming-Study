#include <iostream>
using namespace std;

class Person {
	double money; // 개인 소유의 돈
	static int sharedMoney; // 공금
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
		cout << "내돈 : " << this->money << "\t공금 : " << sharedMoney << endl;
	}
};
int Person::sharedMoney = 10;  // 10으로 초기화


int main() {
	Person han(100);
	//han.money = 100; // han의 개인 돈=100	
	han.addShared(200);

	Person lee(150);
	//lee.money = 150; // lee의 개인 돈=150
	lee.addMoney(200); // lee의 개인 돈=350
	Person::addShared(200); // static 멤버 접근, 공금=400

	han.show(); //내돈 100, 공금 400원
	lee.show(); //내돈 350, 공금 400원
}