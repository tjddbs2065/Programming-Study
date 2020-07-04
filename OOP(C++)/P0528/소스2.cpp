#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Person {
	char* name;
	int id;
public:
	Person(int id, const char* name) {
		this->id = id;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	Person(const Person& copy) {
		id = copy.id;
		name = new char[strlen(copy.name) + 1];
		strcpy(name, copy.name);
	}
	~Person() {
		delete[] this->name;
	}
	void changeName(const char* name) {
		memset(this->name, 0, strlen(this->name) + 1);
		strcpy(this->name, name);
	}
	void show() { cout << id << ',' << name << endl; }
};

int main() {
	Person father(1, "Kitae");
	// Person daughter = father;
	Person daughter(father);
	cout << "daughter 객체생성 이후 ---" << endl;
	father.show();
	daughter.show();
	daughter.changeName("Grace");
	cout << "daughter 이름 변경 이후 ---" << endl;
	father.show();
	daughter.show();

	return 0;
}