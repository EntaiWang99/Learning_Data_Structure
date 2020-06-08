﻿#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef int ElemType;
typedef struct LinkNode {
	ElemType data;
	struct LinkNode* next;
}LinkNode;
typedef struct {
	LinkNode* front, * rear;
}LinkQueue;


//初始化队列
void InitQueue(LinkQueue& Q) {
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next = NULL;
}

//入队列
void EnQueue(LinkQueue& Q, ElemType x) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = x; //尾插法，后面续一个即可
	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
}

//出队列(头部删除法)
bool DeQueue(LinkQueue& Q, ElemType& x) {
	if (Q.front == Q.rear) {
		return false; //头尾指针相等时，队列为空
	}
	LinkNode* p = Q.front->next; //新定义一个指针p指向头结点下一个（头结点没有存数据，下一个才有）
	x = p->data;
	Q.front->next = p->next; //断链
	if (p == Q.rear) { //当p和Q.rear指向同一位置的时候，说明队空，需要将front和rear初始化
		Q.rear = Q.front;
	}
	free(p);
	return true;
}

int main() {
	LinkQueue Q;
	bool ret;
	ElemType element; //存出队元素
	InitQueue(Q);

	//入队
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	EnQueue(Q, 4);

	//出队
	for (int i = 0; i < 5; i++) {
		ret = DeQueue(Q, element);
		if (ret) {
			printf("Out Queue sucessfully! Element:%d\n", element);
		}
		else {
			printf("Out Queue failed!\n");
		}	
	}
	system("pause");
}
