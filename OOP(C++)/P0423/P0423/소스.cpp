#include <iostream>
using namespace std;
//
//class Point {
//public:
//	int xpos = 0, ypos = 0; 
//	void ShowData();
//};
//
//int main(void) {
//	Point pos1;
//	pos1.xpos = 10;
//	pos1.ypos = 20;
//	pos1.ShowData();
//
//	Point pos2;
//	pos2.xpos = 30;
//	pos2.ypos = 40;
//	pos2.ShowData();
//
//	return 0;
//}
//
////Point Ŭ�������� ����� ShowData��� �Լ��� ����
////����� ���Ǹ� �и��Ѵ�.
//void Point::ShowData() {
//	cout << "xpos: " << xpos << " " << "ypos: " << ypos << endl;
//}


class Point {
	//�⺻�� private�̴�.
private:
	int xpos, ypos;
public:
	//�����ڴ� ��ü�� �����Ǵ� ���ÿ� �� �ѹ� �ڵ����� ȣ��Ǵ� ����Լ��̴�.
	//�������� �̸��� Ŭ������ �̸��� �����ϴ�
	//�����ڴ� ���ϰ��� ����, �ϸ� �ȵȴ�. ���� ���� Ÿ�Ե� ����.
	//�����ڵ� ����� ���Ǹ� �и��� �� �ִ�.
	//�����ڴ� �����ε��� ���� �������� �����ڰ� ������ �� �ִ�.
	//�����ڴ� �Ű������� ���� �� Defualt�� �ƹ����� �ȵ� �ִ� ���·� ȣ��ȴ�.
	//�����ڴ� ��ü�� ������ �� ��ü�� �ʿ��� �ʱ�ȭ�� ���� ����Ѵ�.
	//Point::Point()
	Point(int x, int y) {
		xpos = x;
		ypos = y;
	}
	//void ������ = �Ű������� ���� ������
	Point() {
		xpos = 0;
		ypos = 0;
	}
	void ShowData() {
		cout << "xpos : " << xpos << "ypos : " << ypos << endl;
	}
};

int main(void) {
	Point pos1(10, 20);
	pos1.ShowData();

	Point pos2(30, 40);
	pos1.ShowData();

	Point pos3
}