#include <iostream>
using namespace std;

class Car {
	int fuel;
public:
	Car(int fuel) : fuel(fuel) {}
	void ShowFuel() { cout << "�ܿ����ָ�: " << fuel << endl; }
};
class HybridCar : public Car {
	int electricity;
public:
	HybridCar(int fuel, int electricity) : Car(fuel) {
		this->electricity = electricity;
	}
	void ShowElectricity() { 
		cout << "�ܿ����ⷮ: " << electricity << endl; 
	}
};
class HybridWaterCar : public HybridCar {
	int water;
public:
	HybridWaterCar(int fuel, int electricity, int water) : HybridCar(fuel, electricity) {
		this->water = water;
	}
	void ShowCurrentGuage() {
		ShowFuel();
		ShowElectricity();
		cout << "�ܿ����ͷ�: " << water << endl;
	}
};

int main() {
	HybridWaterCar drive(80, 100, 100);
	drive.ShowCurrentGuage();

	return 0;
}