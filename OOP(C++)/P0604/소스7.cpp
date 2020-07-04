#include <iostream>
using namespace std;

class Board {
	static string msg[100];
	static int cnt;

public:
	static void add(string text){
		msg[cnt] = text;
		cnt++;
	}
	static void print() {
		cout << "==============게시글 출력==============" << endl;
		for (int i = 0; i < cnt; i++) {
			cout << msg[i] << endl;
		}
		cout << endl;
	}
};
int Board::cnt = 0;
string Board::msg[100];

int main(void) {
	Board::add("중간고사에 대해서 공지합니다.");
	Board::add("중간고사 결과 공지");
	Board::print();
	Board::add("진수린학생이 경진대회에 입상하셨습니다.");
	Board::print();

	return 0;
}