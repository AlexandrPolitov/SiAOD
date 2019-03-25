#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
};

void add_node(int value, Node *&MyTree) {

	if (NULL == MyTree) {
		MyTree = new Node;
		MyTree->value = value;
		MyTree->left = MyTree->right = NULL; 
	}

	if (value == MyTree->value) return;

	if (value < MyTree->value) {
		if (MyTree->left != NULL)
			add_node(value, MyTree->left);
		else {
			MyTree->left = new Node;
			MyTree->left->left = MyTree->left->right = NULL;
			MyTree->left->value = value;
		}
	}

	if (value > MyTree->value) {
		if (MyTree->right != NULL) 
			add_node(value, MyTree->right);
		else {
			MyTree->right = new Node;
			MyTree->right->left = MyTree->right->right = NULL;
			MyTree->right->value = value;
		}
	}
}

void del(Node *&Tree) {
	if (Tree != NULL) {
		del(Tree->left);
		del(Tree->right);
		delete Tree;
		Tree = NULL;
	}
}

void show(Node *Tree) {
	if (Tree != NULL) {
		cout << Tree->value << " ";
		show(Tree->left);
		show(Tree->right);
	}
}

int count_of_items(int &count, Node* tree) {
	if (tree == NULL) return count;

	if (count == 0) count++;

	if (tree->left != NULL) {
		count++;
		count_of_items(count ,tree->left);
	}

	if (tree->right != NULL) {
		count++;
		count_of_items(count ,tree->right);
	}

	return count;
}

int height_of_tree(int &height, Node* tree) {

	if (height == 0 && tree != NULL) height++;

	if (tree == NULL) return height--;

	if (tree->right != NULL) {
		height++;
		height_of_tree(height, tree->right);
	}

	if (tree->left != NULL) {
		height++;
		height_of_tree(height, tree->left);
	}

	return height;
}

int count_of_nodes(int &count, Node* tree) {

	if (tree == NULL) return count;

	int a, b ,c , d;
	a = b = c = d = 0;

	if (count_of_items(a, tree->right) == count_of_items(b, tree->left) ||
		height_of_tree(c, tree->right) == height_of_tree(d, tree->left))
		count++;

	if(tree->left != NULL)
		count_of_nodes(count, tree->left);
	if (tree->right != NULL)
		count_of_nodes(count, tree->right);

	return count;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node *tree = NULL;

	cout << "Введите количество элементов: ";
	int count;
	while (!(cin >> count)
) {
		cout << "Ошибка чтения!\n";
		cin.clear();
		fflush(stdin);
	}

	cout << "Введите элементы: ";
	for (int i = 0; i < count; i++) {
		int value;
		while (!(cin >> value)) {
			cout << "Ошибка чтения!\n";
			cin.clear();
			fflush(stdin);
		}
		add_node(value, tree);
	}

	count = 0;
	cout << endl << "Количество узлов: " << count_of_nodes(count, tree) << endl;

	del(tree);
	system("pause");
}

//string parse(string str) {
//	for (size_t str_index = 0; str_index < str.length(); str_index++) {
//		str[str_index] = tolower(str[str_index]);
//	}
//	return str;
//}
//
//void calc_prefix_function(vector<int> & prefix_func, string & str)
//{
//	const size_t str_length = str.size();
//
//	prefix_func.clear();
//	prefix_func.resize(str_length);
//	if (0 == str_length) return;
//
//	prefix_func[0] = 0;
//
//	for (size_t current = 1; current < str_length; ++current) {
//		size_t matched_prefix = current - 1;
//		size_t candidate = prefix_func[matched_prefix];
//
//		while (candidate != 0 && str[current] != str[candidate]) {
//			matched_prefix = prefix_func[matched_prefix] - 1;
//			candidate = prefix_func[matched_prefix];
//		}
//
//		if (candidate == 0)
//			prefix_func[current] = str[current] == str[0] ? 1 : 0;
//		else
//			prefix_func[current] = candidate + 1;
//	}
//}
//
//string func_KMP(string form, string str, bool registr) {
//	if (!registr) {
//		form = parse(form);
//		str = parse(str);
//	}
//	vector<int> pref_form;
//	calc_prefix_function(pref_form, form);
//
//	size_t form_index = 0;
//
//	for (size_t str_index = 0; str_index < str.length(); str_index++) {
//
//		if (str[str_index] == form[form_index]) {
//			form_index++;
//			if (form_index == form.length())
//				return "Слово найдено на позиции: " + to_string(str_index - form_index + 2);
//		}
//
//		else {
//			if (form_index == 0) {
//				if (str_index == str.length() - 1) return "Искомое слово не найдено";
//			}
//
//			else form_index = pref_form[form_index - 1];
//		}
//	}
//	return "Искомое слово не найдено";
//}
