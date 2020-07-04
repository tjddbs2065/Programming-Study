#include <iostream>
#include <string>
using namespace std;

class Person {
	string name;
	string tel;
public:
	Person();
	string getName() { return name; }
	string getTel() { return tel; }
	void Set(string name, string tel);
};

int main(void) {
	Person people[3];
	string name, tel;

	for (int i = 0; i < 3; i++) {
		string tmp;
		cout << "사람" << i << " >>";
		cin >> name >> tel;
		people[i].Set(name, tel);
	}

	cout << "모든 사람의 이름은 ";
	for (int i = 0; i < 3; i++) {
		cout << people[i].getName() << " ";
	}
	cout << endl;

	cout << "전화번호 검색합니다. 이름을 입력하세요 >>";
	cin >> name;
	for (int i = 0; i < 3; i++) {
		if (name.compare(people[i].getName()) == 0)
			cout << people[i].getTel() << endl;
		/*if (people[i].getName() == name)
			cout << people[i].getTel() << endl;*/
	}

	return 0;
}
Person::Person() {
	this->name = "홍길동";
	this->tel = "000-0000-0000";
}
void Person::Set(string name, string tel) {
	this->name= name;
	this->tel = tel;
}