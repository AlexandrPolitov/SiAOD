#include <iostream>
#include <list>
#include "Windows.h"

using namespace std;

double sum(list<double> list) {
	double sum = 0;

	for (double item : list) {
		sum += item;
	}

	return sum;
}

void add(list<double> &voltage, list<double> &current, list<double> &square_voltage, list<double> &square_current, list<double> &voltage_current) {
	
	double value;

	while (!(cin >> value)) {   
		cout << "error\n";  
		cin.clear();   
		fflush(stdin);    
	}
	voltage.push_front(value);

	while (!(cin >> value)) { 
		cout << "error\n"; 
		cin.clear();
		fflush(stdin);
	}
	current.push_front(value);

	cout << "значения успешно введены" << endl;

	list<double>::iterator it_vol = voltage.begin();
	list<double>::iterator it_cur = current.begin();

	square_voltage.push_front(*it_vol * *it_vol);
	square_current.push_front(*it_cur * *it_cur);
	voltage_current.push_front(*it_cur * *it_vol);
}

void show(list<double> &voltage, list<double> &current) {
	cout << "+------+------+------+------+------+" << endl;
	cout << "|   V  |   I  |  V^2 |  I^2 |  V*I |" << endl;
	cout << "+------+------+------+------+------+" << endl;

	for (size_t i = 0; i < voltage.size(); i++) {

		list<double>::iterator it_vol = voltage.begin();
		list<double>::iterator it_cur = current.begin();
		advance(it_vol, i);
		advance(it_cur, i);

		cout << "|";
		cout.precision(5);
		cout.fill(' ');
		cout.width(6);
		cout << *it_vol << "|";

		cout.precision(5);
		cout.fill(' ');
		cout.width(6);
		cout << *it_cur << "|";

		cout.precision(5);
		cout.fill(' ');
		cout.width(6);
		cout << *it_vol * *it_vol << "|";

		cout.precision(5);
		cout.fill(' ');
		cout.width(6);
		cout << *it_cur * *it_cur << "|";

		cout.precision(5);
		cout.fill(' ');
		cout.width(6);
		cout << *it_cur * *it_vol << "|" << endl;
	}

	cout << "+------+------+------+------+------+" << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	list<double> voltage;
	list<double> current;
	list<double> square_voltage;
	list<double> square_current;
	list<double> voltage_current;

	// пользовательские значения
	add(voltage, current, square_voltage, square_current, voltage_current);
	add(voltage, current, square_voltage, square_current, voltage_current);
	add(voltage, current, square_voltage, square_current, voltage_current);
	add(voltage, current, square_voltage, square_current, voltage_current);

	show(voltage, current);

	cout << endl << "Некоторые значения сумм" << endl;
	double voltage_sum = sum(voltage);
	cout << "V: " << voltage_sum << endl;
	double current_sum = sum(current);
	cout << "I: " << current_sum << endl;
	double square_voltage_sum = sum(square_voltage);
	cout << "V^2: " << square_voltage_sum << endl;
	double square_current_sum = sum(square_current);
	cout << "I^2: " << square_current_sum << endl;
	double voltage_current_sum = sum(voltage_current);
	cout << "V*I: " << voltage_current_sum << endl;
	cout << "+------+------+------+------+------+" << endl;

	// Супер-пупер-формула подсчета сопротивления
	double R = (((int)voltage.size() * voltage_current_sum) - current_sum * voltage_sum) 
		/ ((int)voltage.size() * square_voltage_sum - voltage_sum * voltage_sum);

	cout << endl << "Приближённое значение сопротивления: " << R << "(Ом)"<< endl;

	system("pause");
}