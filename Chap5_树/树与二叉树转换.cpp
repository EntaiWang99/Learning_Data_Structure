#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX_Tree_SIZE 500


//？？输出格式是先序、后序、层序遍历？
/*
5
1 2
1 5
2 3
2 4
*/
/*
10
1 2
1 3
1 4
1 8
2 9
3 5
3 6
3 7
8 10
*/

typedef int TElemType;
//双亲法结点数据结构
typedef struct PTNode
{
	TElemType data;
	int parent;
}PTNode;

//双亲法树的数据结构
typedef struct {
	PTNode node[MAX_Tree_SIZE];
	int count; 
}PTree;

typedef int ElemType;
//孩子兄弟法结点数据结构
typedef struct CSNode {
	ElemType data;
	struct CSNode* firstchild;
	struct CSNode* nextsibling;
}CSNode, *CSTree;

//孩子兄弟法树的数据结构
CSNode GetTreeNode(ElemType x) {
	CSNode t;
	t.data = x;
	t.firstchild = t.nextsibling = NULL;
	return t;
}

CSNode* Transfer(PTree T) {
	int i, j = 0;
	CSNode p[MAX_Tree_SIZE];
	CSNode* ip, * is,* ir, * tree;
	ip = (CSNode*)malloc(sizeof(CSNode));
	is = (CSNode*)malloc(sizeof(CSNode));
	ir = (CSNode*)malloc(sizeof(CSNode));
	tree = (CSNode*)malloc(sizeof(CSNode));

	for (i = 0; i <= T.count; i++) {
		p[i] = GetTreeNode(T.node[i].data);
	}

	for (i = 1; i <= T.count; i++) {
		ip = &p[i];  //孩子结点
		is = &p[j]; //双亲结点
		while (T.node[i].parent != is->data) {
			j++;
			is = &p[j]; //找好双亲结点
		}
		if (!(is->firstchild)) //左孩子非空放在左孩子那里
		{
			is->firstchild = ip;
			ir = ip;
		}
		else {
			ir->nextsibling = ip;
			ir = ip;
		}
	}		
	tree = &p[0];
	return tree;
}

//先序遍历输出
void PreOrder(CSNode* T) {
	if (T != NULL) {
		printf("%d ", T->data);
		if (T->firstchild != NULL) {
			printf("%d ", T->firstchild->data);
		}
		else
			printf("0 ");
		if (T->nextsibling != NULL) {
			printf("%d ", T->nextsibling->data);
		}
		else
			printf("0");
		printf("\n");
		PreOrder(T->firstchild);
		PreOrder(T->nextsibling);
	}
}


int main()
{
	//构建双亲树
	int n;
	scanf("%d", &n);
	PTree T;
	CSNode* Tree;
	T.count = -1;

	PTNode p;
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		p.data = y;
		p.parent = x;
		T.count++;
		
		if (i == 1) {
			T.node[T.count].data = p.parent;
			T.node[T.count].parent = NULL;
			T.count++;
		}
		T.node[T.count].data = p.data;
		T.node[T.count].parent = p.parent;
	}

	Tree = Transfer(T);
	PreOrder(Tree);

	system("pause");
}