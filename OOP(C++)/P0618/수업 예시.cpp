#include <iostream>
using namespace std;

class Person {
	string name;
public:
	Person(string name) { this->name = name; }
	void Talk(){}
	void Eat(){}
	void Sleep() {}
	void Walk() {}
};

class Student : public Person
{
	int sno;
public:
	Student(string name, int sno) : Person(name)
	{

	}
	void Study(){}
};

int main() {
	
	return 0;
}