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
		cout << "==============�Խñ� ���==============" << endl;
		for (int i = 0; i < cnt; i++) {
			cout << msg[i] << endl;
		}
		cout << endl;
	}
};
int Board::cnt = 0;
string Board::msg[100];

int main(void) {
	Board::add("�߰���翡 ���ؼ� �����մϴ�.");
	Board::add("�߰���� ��� ����");
	Board::print();
	Board::add("�������л��� ������ȸ�� �Ի��ϼ̽��ϴ�.");
	Board::print();

	return 0;
}