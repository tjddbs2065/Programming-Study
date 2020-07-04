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
	Book& operator+=(const int sale) {
		price += sale;
		return *this;
	}
	Book& operator-=(const int sale) {
		price -= sale;
		return *this;
	}
	/*
	friend Book& operator+=(Book& bk1, int sale);
	friend Book& operator-=(Book& bk1, int sale);*/
};
/*
Book& operator+=(Book& bk1, int sale) {
	bk1.price += sale;
	return bk1;
}Book& operator-=(Book& bk1, int sale) {
	bk1.price -= sale;
	return bk1;
}*/
int main(void) {
	Book a("û��", 20000, 300), b("�̷�", 30000, 500);
	a += 500; // ��������
	b -= 500; // ���ݰ���
	a.show();
	b.show();
	return 0;
}