//数据结构文件

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//1.树的数据结构
typedef char BiElemType;
typedef struct BiTNode {
	BiElemType c;//c为树结点存的data
	struct BiTNode* lchild;//左孩子
	struct BiTNode* rchild;//右孩子
}BiTNode, * BiTree;


//2.链表数据结构
typedef struct tag {
	BiTree p;//这里存树结点的指针
	struct tag* pnext;
}tag_t, * ptag_t;

//3.栈数据结构
#define MaxSize 50
typedef BiTree ElemType;
typedef struct {
	ElemType data[MaxSize];//这里栈和队列存的都是树结点的指针吗？？
	int top;
}SqStack;

void InitStack(SqStack& S);
bool StackEmpty(SqStack& S);
bool Push(SqStack& S, ElemType x);
bool Pop(SqStack& S, ElemType &x);
bool GetTop(SqStack& S, ElemType& x);

//4.队列数据结构
typedef struct LinkNode {
	ElemType data;
	struct LinkNode* next;
}LinkNode;
typedef struct {
	LinkNode* front, * rear;
}LinkQueue;

void InitQueue(LinkQueue& Q);
bool IsEmpty(LinkQueue Q);
void EnQueue(LinkQueue& Q, ElemType x);//连队列，不存在无法进队，故为void类型
bool DeQueue(LinkQueue& Q, ElemType& x);

