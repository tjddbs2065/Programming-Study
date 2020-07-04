#include <iostream>
using namespace std;

class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title;
		this->price = price;
		this->pages = pages;
	}
	void show() {
		cout << title << ' ' << price << "원 " << pages << " 페이지" << endl;
	}
	friend bool operator==(Book& bk, int num);
	friend bool operator==(Book& bk, string title);
	friend bool operator==(Book& bk1, Book& bk2);
};

bool operator==(Book& bk, int num) {
	if (bk.price == num)return true;
	else return false;
}
bool operator==(Book& bk, string title) {
	if (bk.title == title)return true;
	else return false;
}
bool operator==(Book& bk1, Book& bk2) {
	if (bk1.title == bk2.title && bk1.price == bk2.price && bk1.pages == bk2.pages)
		return true;
	else return false;
}
int main() {
	Book a("명품 C++", 30000, 500), b("고품 C++", 30000, 500);
	if (a == 30000) 
		cout << "정가 30000원" << endl;
	if (a == "명품 C++")
		cout << "명품 C++입니다." << endl;
	if (a == b)
		cout << "두 책이 같은 책입니다." << endl;

	return 0;
}