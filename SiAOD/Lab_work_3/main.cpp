#include "iostream"
#include "Windows.h"
#include <vector>
#include "string"

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

void addPoint(vector<vector<int>> &graph, vector<int> &link) {
	vector<int> temp;
	for (int i = 0; i < graph.size(); i++) {
		temp.push_back(link.at(i));
	}
	graph.push_back(temp);

	for (int i = 0; i < graph.size() - 1; i++) {
		graph.at(i).push_back(link.at(i));
	}
	graph.at(graph.size() - 1).push_back(0);
}

void show(vector<vector<int>> graph) {
	cout << "Граф: "  << "\t";
	for (int i = 0; i < graph.size(); i++) {
		cout <<  i + 1 << ":\t";
	}
	cout << endl << endl;

	for (int i = 0; i < graph.size(); i++) {
		cout << i + 1 << ":\t";
		for (int j = 0; j < graph.size(); j++) {
			cout << graph.at(i).at(j) << "\t";
		}
		cout << endl<< endl;
	}
}

void optiFine(vector<vector<int>> &graph) {
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			for (int k = 0; k < graph.size(); k++) {

				if (graph.at(i).at(k) == -1 && graph.at(i).at(j) > 0 && graph.at(j).at(k) > 0)
					graph.at(i).at(k) = graph.at(i).at(j) + graph.at(j).at(k);

				if (graph.at(i).at(j) > 0 && graph.at(j).at(k) > 0 && graph.at(i).at(k) > 0 && graph.at(i).at(j) + graph.at(j).at(k) < graph.at(i).at(k))
					graph.at(i).at(k) = graph.at(i).at(j) + graph.at(j).at(k);
			}
		}
	}
}

void check(vector<vector<int>> &graph) {
	int temp = 0;
	for (int i = 0; i < graph.size(); i++) {
		for (int j = i + 1; j < graph.size(); j++) {
			if (graph.at(i).at(j) > 100)
				temp++;
		}
	}
	cout << ((temp > 3) ? "Нельзя оптимизировать дороги" : "Можно оптимизировать дороги");
	cout << endl;
}

void add(vector<vector<int>> &graph) {
	vector<int> link;
	link.clear();
	for (int i = 0; i < graph.size(); i++) {
		cout << i + 1 << ": ";
		int temp;
		if (!tryParse(temp)) i--;
		else link.push_back(temp);
	}
	addPoint(graph, link);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	vector<vector<int>> graph;
	add(graph);

	int comand = 10;
	cout << "1 - Добавление города" << endl; 
	cout << "2 - Вывод графа" << endl;
	cout << "3 - Проверка на возможность оптимизации" << endl;
	cout << "0 - Выход из программы" << endl;
	while (comand != 0) {
		cout << "Введите команду: ";
		while (!tryParse(comand));
		switch (comand) {
		case 1:
			add(graph);
			break;
		case 2:
			show(graph);
			break;
		case 3:
			optiFine(graph);
			check(graph);
			show(graph);
			break;
		case 0:
			break;
			}
	}
		system("pause");
}