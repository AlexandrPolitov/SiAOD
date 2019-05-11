#include <iostream>
#include "Windows.h"
#include "string"
#include "vector"

using namespace std;

bool tryParse(int& num) {
	num = 0;
	string str;
	getline(cin, str);
	if (str.length() > 7)
		return false;
	else {
		if (str[0] != '-' && (str[0] < '0' || str[0] > '9')) return false;
		for (size_t index = 1; index < str.length(); index++)
			if (str[index] < '0' || str[index] > '9')
				return false;
		num = atoi(str.c_str());
		return true;
	}
}

void addValues(vector<int> &array, int &size) {
	cout << "Введите размер последовательности: ";
	while (!tryParse(size));
	for (int i = 0; i < size; i++)
		array.push_back(rand() % 20 - 10);
}

void show(vector<int> &array, int size) {
	cout << "Последовательность: ";
	for (int i = 0; i < size; i++)
		cout << " " << array.at(i);
	cout << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size = 0;
	vector<int> array;

	cout << "1 - Заполнение последовательности" << endl;
	cout << "2 - Внешняя сортировка простым слиянием" << endl;
	cout << "3 - Вывод последовательности" << endl;
	cout << "0 - Выход из программы" << endl;

	int comand = 10;
	while (comand != 0) {
		cout << "Введите команду: ";
		while (!tryParse(comand));
		switch (comand) {
		case 1:
			addValues(array, size);
			break;
		case 2:
			break;
		case 3:
			show(array, size);
			break;
		case 0:
			break;
		}
	}
	system("pause");
}