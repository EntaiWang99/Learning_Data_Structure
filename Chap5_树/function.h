//���ݽṹ�ļ�

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//1.�������ݽṹ
typedef char BiElemType;
typedef struct BiTNode {
	BiElemType c;//cΪ�������data
	struct BiTNode* lchild;//����
	struct BiTNode* rchild;//�Һ���
}BiTNode, * BiTree;


//2.�������ݽṹ
typedef struct tag {
	BiTree p;//�����������ָ��
	struct tag* pnext;
}tag_t, * ptag_t;

//3.ջ���ݽṹ
#define MaxSize 50
typedef BiTree ElemType;
typedef struct {
	ElemType data[MaxSize];//����ջ�Ͷ��д�Ķ���������ָ���𣿣�
	int top;
}SqStack;

void InitStack(SqStack& S);
bool StackEmpty(SqStack& S);
bool Push(SqStack& S, ElemType x);
bool Pop(SqStack& S, ElemType &x);
bool GetTop(SqStack& S, ElemType& x);

//4.�������ݽṹ
typedef struct LinkNode {
	ElemType data;
	struct LinkNode* next;
}LinkNode;
typedef struct {
	LinkNode* front, * rear;
}LinkQueue;

void InitQueue(LinkQueue& Q);
bool IsEmpty(LinkQueue Q);
void EnQueue(LinkQueue& Q, ElemType x);//�����У��������޷����ӣ���Ϊvoid����
bool DeQueue(LinkQueue& Q, ElemType& x);

