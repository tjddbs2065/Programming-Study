#include <iostream>
using namespace std;

class PermanentWorker {
	//string name;
	char name[20];
	int salary;
public:
	PermanentWorker(const char* name, int salary) {
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

class SalesWorker : PermanentWorker {
	int salesResult;//판매실적
	double bonusRatio;//인센티브
public:
	void AddSalesResult(int value);
	int GetPay();
};
class EmployeeHandler {
	PermanentWorker* empList[50];
	int empNum;

public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(PermanentWorker* emp) {
		empList[empNum++] = emp;
	}
	void ShowAllSalaryInfo() {
		for (int i = 0; i < empNum; i++) {
			empList[i]->ShowSalaryInfo();
		}
	}
	void ShowTotalSalary() {
		int sum = 0;
		for (int i = 0; i < empNum; i++) {
			sum += empList[i]->GetPay();
		}
		cout << "salary sum : " << sum << endl;
	}
};
int main() {
	EmployeeHandler emp;
	emp.AddEmployee(new PermanentWorker("Kim", 1000));
	emp.AddEmployee(new PermanentWorker("Lee", 1500));
	emp.AddEmployee(new PermanentWorker("Jun", 2000));

	emp.ShowAllSalaryInfo();
	emp.ShowTotalSalary();

	return 0;
}