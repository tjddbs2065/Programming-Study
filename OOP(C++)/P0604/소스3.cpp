#include <iostream>
using namespace std;

class Person {
private:
	int id;
	string name;
	double weight;
public:
	/*Person() {
		this->id = 1;
		this->name = "Grace";
		this->weight = 20.5;
	}
	Person(int id, string name) {
		this->id = id;
		this->name = name;
		this->weight = 20.5;
	}
	Person(int id, string name, double weight) {
		this->id = id;
		this->name = name;
		this->weight = weight;
	}*/
	//Default �Ű������� Ȱ���� ��� �Լ� �����ε� ȿ���� �� �� �ִ�.
	Person(int id = 1, string name = "Grace", double weight = 20.5) {
		this->id = id;
		this->name = name;
		this->weight = weight;
	}
	void show() {
		cout << this->id << '\t' << this->name << '\t' << this->weight;
		cout << endl;
	}
};
int main(void) {
	Person grace, ashley(2, "Ashley"), helen(3, "Helen", 32.5);
	grace.show();
	ashley.show();
	helen.show();

	return 0;
}