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
		cout << "���" << i << " >>";
		cin >> name >> tel;
		people[i].Set(name, tel);
	}

	cout << "��� ����� �̸��� ";
	for (int i = 0; i < 3; i++) {
		cout << people[i].getName() << " ";
	}
	cout << endl;

	cout << "��ȭ��ȣ �˻��մϴ�. �̸��� �Է��ϼ��� >>";
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
	this->name = "ȫ�浿";
	this->tel = "000-0000-0000";
}
void Person::Set(string name, string tel) {
	this->name= name;
	this->tel = tel;
}