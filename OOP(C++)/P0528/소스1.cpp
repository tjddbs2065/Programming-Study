#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Book {
	int price;
	int pages;
	char* title;
	char* name;
public:
	Book(int price, int pages, const char* title, const char* name) {
		this->price = price;
		this->pages = pages;
		this->title = new char[strlen(title)+1];
		strcpy(this->title, title);
		this->name = new char[strlen(name)+1];
		strcpy(this->name, name);
	}
	void ShowBook() {
		cout << "가격:" << price << endl;
		cout << "페이지:" << pages << endl;
		cout << "책제목:" << title << endl;
		cout << "저자:" << name << endl;
	}

	//깊은 복사를 하는 복사 생성자 구현
	Book(const Book& copy) {
		price = copy.price;
		pages = copy.pages;
		title = new char[strlen(copy.title) + 1];
		strcpy(title, copy.title);

		name = new char[strlen(copy.name) + 1];
		strcpy(name, copy.name);
	}
	~Book() {
		delete[] this->name;
		delete[] this->title;
	}
};
int main(void) {
	Book cpp(20000, 400, "명품C++", "황기태");
	Book cplusplus(cpp);

	cpp.ShowBook();
	cplusplus.ShowBook();
	
	return 0;
}