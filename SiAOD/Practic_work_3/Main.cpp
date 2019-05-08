#include <iostream>
#include "Windows.h"
#include "string"
#include <ctime>
using namespace std;

bool tryParse (int& num) {
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

// ������� ���������� �����
int sortShell (int *arr, int size) {
	int iterator = 0;

	int step = size / 2;
	while (step > 0) {
		for (int i = 0; i < (size - step); i++) {
			int j = i;
			while (j >= 0 && arr[j] > arr[j + step]) {
				int temp = arr[j];
				arr[j] = arr[j + step];
				arr[j + step] = temp;
				j--;

				iterator++;
			}
		}
		step = step / 2;
	}
	return iterator;
}

// ������� ���������� ������ �������
int sortSelection (int *arr, int size) {
	int iterator = 0;

	int min, temp; 
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min])
				min = j;
			iterator++;
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	return iterator;
}

// ������� ���������� ���������
int sortBubble (int *arr, int size) {
	int iterator = 0;
	int temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) 
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				iterator++;
			}
	return iterator;
}

// ������� ���������� ���������
int sortInsert (int *arr, int size) {
	int x;
	int i, j;
	int iterator = 0;

	for (i = 0; i < size; i++) { 
		x = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > x; j--) {
			arr[j + 1] = arr[j];
			iterator++;
		}
		arr[j + 1] = x;
	}
	return iterator;
}

// ������� ������ ���������
void findItems(int *arr, int size) {
	int count;
	cout << endl << "����� ���������� ���������" << endl;
	cout << "������� ���������� ���������: ";
	while (!tryParse(count));

	int temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}

	for (int i = 0; i < count; i++) {
		cout << arr[size - i - 1] << " ";
	}

	cout << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	cout << "������� ������ �������: ";
	while (!tryParse(size));

	int *arr = new int[size];
	cout << "������ ������: " << endl;
	for (int i = 0; i < size; i++) {
		if (!tryParse(arr[i])) i--;
	}

	cout << "���������� �����: " << sortShell(arr, size) << endl;
	cout << "���������� ������ �������: " << sortSelection(arr, size) << endl;

	cout << endl << "����� ������ ������ ����������" << endl;

	unsigned int start_time = clock();
	sortInsert(arr, size);
	unsigned int end_time = clock();
	cout << "���������� ���������: " << end_time - start_time << " ��" << endl;

	start_time = clock();
	sortBubble(arr, size);
	end_time = clock();
	cout << "���������� ���������: " << end_time - start_time << " ��" << endl;

	start_time = clock();
	sortSelection(arr, size);
	end_time = clock();
	cout << "���������� �������: " << end_time - start_time << " ��" << endl;

	findItems(arr, size);

	system("pause");
}