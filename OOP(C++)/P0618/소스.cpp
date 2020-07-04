#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Person {
	char *name;
	int age;
public:
	Person(const char* name, int age){
		//strcpy(this->name, name);
		this->name = new char[strlen(name)+1];
		strcpy(this->name, name);
		this->age = age;
	}
	~Person() {
		delete[] name;
	}
	char* GetName() { return name; }
	int GetAge() { return age; }
	void ShowName() { cout << "이름: " << name << endl; }
	void ShowAge() { cout << "나이: " << age << endl; }
};
class UnivStudent : public Person {
	char *major;
public:
	UnivStudent(const char* name, int age, const char* major):Person(name, age) {
		//strcpy(this->major, major);
		this->major = new char[strlen(major)+1];
		strcpy(this->major, major);
	}
	char* GetMajor() {
		return this->major;
	}
	void WhoAreYou() {
		//cout << "이름:" << GetName() << " 나이:" << GetAge() << " 전공:" << GetMajor() << endl;
		ShowName();
		ShowAge();
		cout << "전공: " << major << endl;
	}
	~UnivStudent() {
		delete[] major;
	}
};

int main() {
	UnivStudent std1("Kim", 20, "Security"); //객체 생성 시 부모의 멤버까지 초기화할 데이터 전달
	std1.WhoAreYou();
}