#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;
//树的结构体
typedef struct Node {
	int data;
	struct Node* lchild;
	struct Node* rchild;
}BTNode;

//插入结点(递归写法)
void Insert(BTNode** root, int key) { //指向指针的指针的写法,why??
	if (*root == NULL) {  //正着插
		*root = (BTNode*)malloc(sizeof(BTNode));
		(*root)->data = key;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
	}
	else if (key < (*root)->data) {  //向左插
		Insert(&(*root)->lchild, key);
	}
	else if (key >= (*root)->data) {  //向右插
		Insert(&(*root)->rchild, key);
	}
}

//查找
BTNode* Search(BTNode* root, int key) {
	if (root == NULL)
		return NULL;
	else if (key == root->data)
		return root;
	else if (key < root->data)
		Search(root->lchild, key);
	else if (key > root->data)
		Search(root->rchild, key);
}


int main() {
	int n; //操作次数
	cin >> n;
	int key; //关键字
	BTNode* root = NULL;
	for (int i = 1; i <= n; i++) {
		cin >> key;
		BTNode* value;
		value = Search(root, key);
		if (value == NULL) {
			cout << "NO" << endl;
			Insert(&root, key); //这个&是给地址，不是引用
		}
		else {
			cout << "YES" << endl;
		}
	}
}