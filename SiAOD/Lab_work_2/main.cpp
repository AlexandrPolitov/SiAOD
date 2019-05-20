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