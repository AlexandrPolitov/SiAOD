#include <iostream>
#include <string>
#include "Windows.h"

using namespace std;

struct school {
	string name;
	int count_pupils;
};

void out_menu() {
	cout << "1  Добавление школы в список" << endl;
	cout << "2  Вывод списка школ" << endl;
	cout << "3  Поиск школ по количеству учеников" << endl;
	cout << "0  Выход из программы" << endl;
}

bool try_parse(int& num) {
	num = 0;
	string str;

	getline(cin, str);

	if (str.length() > 7)
		return false;
	else {
		for (size_t index = 0; index < str.length(); index++)
			if (str[index] < '0' || str[index] > '9')
				return false;
		num = atoi(str.c_str());
		return true;
	}
}

void change_size(school *&list, int &length)
{
	school *new_list = new school[++length];

	for (int i = 0; i < length - 1; i++)
		new_list[i] = list[i];

	list = new_list;
}

void add(school *&list_of_schools, int &length) {

	string name;
	int count;

	cout << "Введите название школы: ";
	getline(cin, name);

	while (true) {
		cout << "Введите число учеников: ";
		if (try_parse(count))
			break;
	}

	change_size(list_of_schools, length);

	list_of_schools[length - 1].name = name;
	list_of_schools[length - 1].count_pupils = count;

}

void show(school *list_of_schools, int length) {
	cout << "Список школ:" << endl;
	for (int i = 0; i < length; i++) {
		cout << list_of_schools[i].name + "\t" << list_of_schools[i].count_pupils << endl;
	}
}

int search(school *list_of_schools, int length, int count_pupils, int iterations) {
	for (int i = 0; i < length; i++) {
		iterations += 2;
		if (list_of_schools[i].count_pupils = count_pupils) {
			iterations += 1;
			cout << "Найденная школа: " << list_of_schools[i].name + "\t" << list_of_schools[i].count_pupils << endl;
			return iterations;
		}
	}
	return iterations;
}

int search_barrier(school *list_of_schools, int length, int count_pupils, int iterations) {
	if (length != 0) {

		school last = list_of_schools[length - 1];
		school value = { "some school", count_pupils };
		list_of_schools[length - 1] = value;
		size_t i = 0;
		iterations += 8;
		for (i = 0; list_of_schools[i].count_pupils != value.count_pupils; ++i)
			iterations++;
		list_of_schools[length - 1] = last;
		if (i != (length - 1) || value.count_pupils == last.count_pupils) {
			return iterations;
		}
		else
			return iterations;
	}
	else
		return iterations;
}

int bin_search(school *list_of_schools, int left, int right, int Count_pupils, int iterations) {

	int middle = left + (right - left) / 2;
	iterations++;

	if (left >= right) return ++iterations;
	if (list_of_schools[middle].count_pupils == Count_pupils)
		return ++iterations;
	else if (list_of_schools[middle].count_pupils > Count_pupils)
		return bin_search(list_of_schools, left, middle, Count_pupils, ++iterations);
	else
		return bin_search(list_of_schools, middle + 1, right, Count_pupils, ++iterations);
}

int bin_gold_search(school *list_of_schools, int left, int right, int Count_pupils, int iterations) {

	double fi = 1.618;
	int middle = (int)((double)left + (double)(right - left) / (fi + 1));
	iterations++;

	if (left >= right) return ++iterations;
	if (list_of_schools[middle].count_pupils == Count_pupils)
		return ++iterations;
	else if (list_of_schools[middle].count_pupils > Count_pupils)
		return bin_search(list_of_schools, left, middle, Count_pupils, ++iterations);
	else
		return bin_search(list_of_schools, middle + 1, right, Count_pupils, ++iterations);
}

void search_school(school *list_of_schools, int length) {
	int count_pupils;

	while (true) {
		cout << endl << "Введите количество учеников: ";
		if (try_parse(count_pupils))
			break;
	}

	// Поиск перебором
	cout << "Количество операций(Поиск перебором): " << search(list_of_schools, length, count_pupils, 0) << endl;

	// Поиск с барьером
	cout << "Количество операций(Поиск с барьером): " << search_barrier(list_of_schools, length, count_pupils, 0) << endl;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (list_of_schools[i].count_pupils < list_of_schools[j].count_pupils) {
				school temp;
				temp = list_of_schools[i];
				list_of_schools[i] = list_of_schools[j];
				list_of_schools[j] = temp;
			}
		}
	}

	// Бинарный поиск
	cout << "Количество операций(бинарный поиск): " << bin_search(list_of_schools, 0, length, count_pupils, 0) << endl;

	// Бинарный поиск с золотым сечением
	cout << "Количество операций(бинарный поиск с золотым сечением): " << bin_gold_search(list_of_schools, 0, length, count_pupils, 0) << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	school *list_of_schools = new school[0];
	int length = 0;
	int comand = 0;

	out_menu();

	do {
		while (true) {
			cout << endl << "Введите команду: ";
			if (try_parse(comand))
				break;
		}

		switch (comand)
		{

		case 1:
			add(list_of_schools, length);
			break;

		case 2:
			show(list_of_schools, length);
			break;

		case 3:
			search_school(list_of_schools, length);
			break;

		case 0:
			cout << "Программа завершена.";
			break;

		default:
			break;
		}
	} while (comand != 0);
}