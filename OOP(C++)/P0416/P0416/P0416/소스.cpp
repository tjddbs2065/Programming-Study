#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
using namespace std;

int main(void) {
	char name[20];
	cout << "이름을 입력하세요 : ";
	//cin >> name;
	
	cin.getline(name, 20);
	
	cout << "your name is " <<name << endl;

	return 0;
}
