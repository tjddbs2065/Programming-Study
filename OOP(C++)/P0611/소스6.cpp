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
		cout << title << ' ' << price << "�� " << pages << " ������" << endl;
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
	Book a("��ǰ C++", 30000, 500), b("��ǰ C++", 30000, 500);
	if (a == 30000) 
		cout << "���� 30000��" << endl;
	if (a == "��ǰ C++")
		cout << "��ǰ C++�Դϴ�." << endl;
	if (a == b)
		cout << "�� å�� ���� å�Դϴ�." << endl;

	return 0;
}