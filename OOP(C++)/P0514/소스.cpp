#include <iostream>
#include <string>
using namespace std;

int main(void) {
	/*
	string str;
	string str1 = "���� ���ʱ� ���絿";
	string str2("���� ���ʱ� ���絿");
	string str3(str2);
	cout << str1;*/


	/*string* ptr = new string("���� ���ʱ� ���絿");
	cout << *ptr;
	delete ptr;*/

	// 1) �Է�
	//cin >> str; // ���� ó�� X
	//getline(cin, str); //���� ó�� O

	// 2) ����Լ�
	// - compare(string &str) : ���ڿ��� str ��, ������ 0, ���������� str���� ũ�� ����, ������ ���
	// ==, !=, >, <, >=, <=
	/*string str1 = "kim";
	string str2 = "lee";
	if (str1.compare(str2) == 0) cout << "����" << endl;
	if (str1 == str2)cout << "����" << endl;*/

	// - append(string &str) : ���ڿ� �ڿ� str �߰�
	/*string str1 = "����";
	cout << str1 << endl;
	str1.append(" ���ʱ�");
	cout << str1 << endl;*/
	// +, +=
	/*string str1 = "����";
	string str2 = " ���ʱ�";
	string addr = str1 + str2;
	str1 += str2;*/
	
	// - insert (�ε���, ���ڿ�) : ���ڿ� ����
	/*string str1 = "I Love C++";
	str1.insert(1, " really");
	cout << str1 << endl;*/
	
	// - length() : ���ڿ� ���� ������ ��ȯ, size()

	// - erase(�ε���, N(����)) : �ε��� ���� ������ŭ ���ڿ� ����
	/*string str1 = "I Really Love C++";
	str1.erase(2, 7);
	cout << str1 << endl;*/

	// - clear() : ��ü�� ����� ���ڿ� �ʱ�ȭ
	/*string str = "���� ���ʱ�";
	str = "";*/

	// - substr(�ε���, N(����)) : �ε��� ���� ������ŭ ���ڿ� ����
	/*string str1 = "I Love C++";
	string str2 = str1.substr(2, 4);
	cout << str2 << endl;*/
	
	// - find("love") : ��ġ ��ȯ, ��ã���� -1 ��ȯ
	// - find("love", �ε���) : �ε������� ã�Ƽ� ��ġ ��ȯ, ��ã���� -1 ��ȯ
	/*string str1 = "I Love C++";
	int a = str1.find("Love");
	cout << a << endl;*/

	// - stoi : ���ڿ� ���� ġȯ
	/*string year = "2020";
	int n = stoi(year);
	cout << n << endl;*/

	// - at(�ε���) : �ε����� ���� �ϳ� ��ȯ
	/*string str1 = "I Love C++";
	cout << str1.at(4) << endl;*/
	


	return 0;
}