#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Book {
	char* title;
	char* isbn;
	int price;
public:
	Book(const char* title, const char* isbn, int price) {
		this->title = new char[strlen(title) + 1];
		strcpy(this->title, title);
		this->isbn = new char[strlen(isbn) + 1];
		strcpy(this->isbn, isbn);
		this->price = price;
	}
	~Book() {
		delete[] title;
		delete[] isbn;
	}
	void ShowBookInfo() {
		cout << "책제목:\t" << title << endl;
		cout << "ISBN:\t" << isbn << endl;
		cout << "책가격:\t" << price << endl;
	}
};
class Ebook : public Book {
	char* DRMKey;
public:
	Ebook(const char* title, const char* isbn, int price, const char* DRMKey)
		: Book(title, isbn, price) {
		this->DRMKey = new char[strlen(DRMKey) + 1];
		strcpy(this->DRMKey, DRMKey);
	}
	~Ebook() {
		delete[] DRMKey;
	}
	void ShowEBookInfo() {
		ShowBookInfo();
		cout << "DRMKey:\t" << DRMKey << endl;
	}
};

int main(){
	Book book("좋은 C++", "555-12345-890-0", 20000);
	book.ShowBookInfo();

	cout << endl;
	Ebook ebook("좋은 C++ ebook", "555-12345-890-1", 10000, "fdx9w0i8kiw");
	ebook.ShowEBookInfo();

	return 0;
}