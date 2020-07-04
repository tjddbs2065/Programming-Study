#include <iostream>
using namespace std;

class PermanentWorker {
	//string name;
	char name[20];
	int salary;
public:
	PermanentWorker(const char* name, int salary){
		strcpy_s(this->name, 20, name);
		//this->name = name;
		this->salary = salary;
	}

	int GetPay() { return salary; }
	void ShowSalaryInfo() { 
		cout << "name : " << name << endl;
		cout << "salary : " << salary << endl; 
		cout << endl;
	}
};

int main() {
	PermanentWorker kim("kim", 1000);
	PermanentWorker lee("lee", 1500);
	PermanentWorker jun("jun", 2000);

	int sum = 0;
	sum += kim.GetPay();
	sum += lee.GetPay();
	sum += jun.GetPay();

	kim.ShowSalaryInfo();
	lee.ShowSalaryInfo();
	jun.ShowSalaryInfo();

	cout << "salary sum : " << sum << endl;

	return 0;
}