#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
using namespace std;

int main(void) {
	char name[20];
	cout << "�̸��� �Է��ϼ��� : ";
	//cin >> name;
	
	cin.getline(name, 20);
	
	cout << "your name is " <<name << endl;

	return 0;
}
