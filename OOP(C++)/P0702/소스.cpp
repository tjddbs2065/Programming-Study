#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Employee { // 추상 클래스 : 객체화 시킬 수 없는 클래스
				 // 순수 가상 함수를 하나 이상 포함하고 있는 클래스
				 // 객체가 생성되면 에러가 발생한다.
	int workTime;
	char name[30];
public:
	Employee(const char* name) {
		strcpy(this->name, name);
	}
	void ShowYourName() {
		cout << "이름 : " << name << endl;
	}
	virtual void ShowSalaryInfo() = 0; // 순수 가상 함수
	virtual int GetPay() = 0; // 순수 가상 함수
};
class PermanentWorker : public Employee { //정규직 직원 클래스
	int salary;
public:
	PermanentWorker(const char* name, int salary) : Employee(name) {
		this->salary = salary;
	}
	virtual int GetPay() {
		return this->salary;
	}
	void ShowSalaryInfo() {
		ShowYourName();
		cout << "급여 : " << GetPay() << endl << endl;
	}
};
class SalesWorker : public PermanentWorker {
	int salesResult;
	double bonusRatio;
public:
	SalesWorker(const char* name, int salary, double bonusRatio) : PermanentWorker(name, salary) {
		this->bonusRatio = bonusRatio;
		salesResult = 0;
	}
	void AddSalesResult(int salesResult) {
		this->salesResult += salesResult;
	}
	int GetPay() {
		return (PermanentWorker::GetPay() + (int)(salesResult * bonusRatio));
	}
};

class ForeignSalesWorker : public SalesWorker {
	char risk;
public:
	ForeignSalesWorker(const char* name, int salary, double bonusRatio, char risk) : SalesWorker(name, salary, bonusRatio) {
		this->risk = risk;
	}
	int GetPay() {
		if (risk == 'A')
			return SalesWorker::GetPay()+ (int)SalesWorker::GetPay()*0.3;
		else if (risk == 'B')
			return SalesWorker::GetPay()+ (int)SalesWorker::GetPay()*0.2;
		else if (risk == 'C')
			return SalesWorker::GetPay() + (int)SalesWorker::GetPay()*0.1;
	}
};

class TemporaryWorker : public Employee {
	int workTime;
	int payPerHour;
public:
	TemporaryWorker(const char* name, int payPerHour) : workTime(0), Employee(name) {
		this->payPerHour = payPerHour;
	}
	void AddWorkTime(int workTime) {
		this->workTime += workTime;
	}
	int GetPay() {
		return (workTime * payPerHour);
	}
	void ShowSalaryInfo() {
		ShowYourName();
		cout << "급여 : " << GetPay() << endl << endl;
	}
};

class EmployeeHandler {
	Employee* empList[50];
	//PermanentWorker* empList[50];
	int empNum;
public:
	EmployeeHandler() : empNum(0) {}
	void AddEmployee(Employee* emp) {
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

int main(void) {
	EmployeeHandler handler;
	//handler.AddEmployee(new Employee("tt"));	<- 추상클래스일 경우 실행 안됨

	handler.AddEmployee(new PermanentWorker("kim", 1000));
	handler.AddEmployee(new PermanentWorker("lee", 1500));
	handler.AddEmployee(new PermanentWorker("jun", 2000));

	//영업직 등록
	SalesWorker* seller = new SalesWorker("Hong", 1000, 0.1); // 이름, 기본급, 인센티브율
	seller->AddSalesResult(7000); // 영업실적 7000 추가
	handler.AddEmployee(seller);

	//임시직: 아르바이트생
	TemporaryWorker* alba = new TemporaryWorker("Jung", 70); //시간 당 페이
	alba->AddWorkTime(5);
	handler.AddEmployee(alba);

	//해외 영업직
	ForeignSalesWorker* fseller1 = new ForeignSalesWorker("Hong", 1000, 0.1, 'A');
	fseller1->AddSalesResult(7000);
	handler.AddEmployee(fseller1);
	ForeignSalesWorker* fseller2 = new ForeignSalesWorker("Yoon", 1000, 0.1, 'B');
	fseller2->AddSalesResult(7000);
	handler.AddEmployee(fseller2);
	ForeignSalesWorker* fseller3 = new ForeignSalesWorker("Lee", 1000, 0.1, 'C');
	fseller3->AddSalesResult(7000);
	handler.AddEmployee(fseller3);

	handler.ShowAllSalaryInfo();
	handler.ShowTotalSalary();

	return 0;
}