#include "function.h"

//1.前序遍历
void PreOrder(BiTree p) {
	if (p != NULL) {
		putchar(p->c);
		PreOrder(p->lchild);
		PreOrder(p->rchild);
	}
}

//2.中序遍历
void InOrder(BiTree p) {
	if (p != NULL) {
		InOrder(p->lchild);
		putchar(p->c);
		InOrder(p->rchild);
	}
}

//3.后序遍历
void PostOrder(BiTree p) {
	if (p != NULL) {
		PostOrder(p->lchild);
		PostOrder(p->rchild);
		putchar(p->c);
	}
}

//4.中序非递归遍历
void InOrder2(BiTree T) {
	SqStack S;
	InitStack(S);
	BiTree p = T; //把树根传进来
	while (p || !StackEmpty(S)) { //判断条件：树结点不为空 or 栈不为空, why？
		if (p) { //p不为NULL时候，不断压栈，p==NULL时候说明到头，该弹栈了
			Push(S, p);
			p = p->lchild;//向左孩子方向不断压栈
		} else {
			Pop(S, p);
			putchar(p->c);
			p = p->rchild;//向右孩子方向
		}
	}
}

//5.层序遍历(队列实现，广度优先遍历)
void LevelOrder(BiTree T) {
	LinkQueue Q;
	InitQueue(Q);
	BiTree p;
	EnQueue(Q, T); //树根入队
	while (!IsEmpty(Q)) {
		DeQueue(Q, p);
		putchar(p->c);
		if (p->lchild != NULL)
			EnQueue(Q, p->lchild);
		if (p->rchild != NULL)

			EnQueue(Q, p->rchild);
	}

}


int main() {
	BiTree pnew; //新结点
	int i, j, pos;
	char c;
	BiTree tree = NULL; //树根结点
	ptag_t phead = NULL, ptail = NULL, pcur =NULL; //链表头尾指针
	ptag_t listpnew;

	//输入数据 abcdefghijk
	while (scanf("%c", &c) != EOF) {
		if (c == '\n') {
			break;
		}
		//申请一个树结点类型的空间
		pnew = (BiTree)calloc(1, sizeof(BiTNode));
		pnew->c = c;//申请一个结点指针类型空间
		listpnew = (ptag_t)calloc(1, sizeof(tag_t));
		listpnew->p = pnew;
		if (tree == NULL) {
			tree = pnew;//赋值树根
			phead = listpnew;//链表头指向listpnew
			ptail = listpnew;//链表尾指向listpnew
			pcur = listpnew;//当前链表指针指向listpnew
			continue;//直接进行scanf下一个字符
		}
		else {
			ptail->pnext = listpnew;//新结点插入链表尾
			ptail = listpnew;
		}
		if (pcur->p->lchild == NULL) { //当前链表指针所指结点左孩子为空
			pcur->p->lchild = pnew;  //建立左孩子连接
		}
		else if (pcur->p->rchild == NULL){
			pcur->p->rchild = pnew; //建立右孩子连接
			pcur = pcur->pnext; //pcur本层已装满，父节点向前进
		}
	}
	printf("**********前序遍历**********\n");
	PreOrder(tree);
	printf("\n");
	printf("**********中序遍历**********\n");
	InOrder(tree);
	printf("\n");
	printf("**********后序遍历**********\n");
	PostOrder(tree);
	printf("\n");
	printf("*******中序非递归遍历*******\n");
	InOrder2(tree);
	printf("\n");
	printf("**********层序遍历**********\n");
	LevelOrder(tree);
	printf("\n");
	system("pause");
}
