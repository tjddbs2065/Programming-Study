#include <iostream>
#include <string>
using namespace std;

int main(void) {
	/*
	string str;
	string str1 = "서울 서초구 양재동";
	string str2("서울 서초구 양재동");
	string str3(str2);
	cout << str1;*/


	/*string* ptr = new string("서울 서초구 양재동");
	cout << *ptr;
	delete ptr;*/

	// 1) 입력
	//cin >> str; // 공백 처리 X
	//getline(cin, str); //공백 처리 O

	// 2) 멤버함수
	// - compare(string &str) : 문자열과 str 비교, 같으면 0, 사전상으로 str보다 크면 음수, 작으면 양수
	// ==, !=, >, <, >=, <=
	/*string str1 = "kim";
	string str2 = "lee";
	if (str1.compare(str2) == 0) cout << "같다" << endl;
	if (str1 == str2)cout << "같다" << endl;*/

	// - append(string &str) : 문자열 뒤에 str 추가
	/*string str1 = "서울";
	cout << str1 << endl;
	str1.append(" 서초구");
	cout << str1 << endl;*/
	// +, +=
	/*string str1 = "서울";
	string str2 = " 서초구";
	string addr = str1 + str2;
	str1 += str2;*/
	
	// - insert (인덱스, 문자열) : 문자열 삽입
	/*string str1 = "I Love C++";
	str1.insert(1, " really");
	cout << str1 << endl;*/
	
	// - length() : 문자열 길이 정수로 반환, size()

	// - erase(인덱스, N(개수)) : 인덱스 부터 개수만큼 문자열 삭제
	/*string str1 = "I Really Love C++";
	str1.erase(2, 7);
	cout << str1 << endl;*/

	// - clear() : 객체에 저장된 문자열 초기화
	/*string str = "서울 서초구";
	str = "";*/

	// - substr(인덱스, N(개수)) : 인덱스 부터 개수만큼 문자열 추출
	/*string str1 = "I Love C++";
	string str2 = str1.substr(2, 4);
	cout << str2 << endl;*/
	
	// - find("love") : 위치 반환, 못찾으면 -1 반환
	// - find("love", 인덱스) : 인덱스부터 찾아서 위치 반환, 못찾으면 -1 반환
	/*string str1 = "I Love C++";
	int a = str1.find("Love");
	cout << a << endl;*/

	// - stoi : 문자열 숫자 치환
	/*string year = "2020";
	int n = stoi(year);
	cout << n << endl;*/

	// - at(인덱스) : 인덱스의 문자 하나 반환
	/*string str1 = "I Love C++";
	cout << str1.at(4) << endl;*/
	


	return 0;
}