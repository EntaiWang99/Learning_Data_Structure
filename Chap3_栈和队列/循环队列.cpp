#include<stdio.h>
#include<stdlib.h>

#define MaxSize 5
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;

//初始化队列
void InitQueue(SqQueue& Q) 
{
	Q.rear = Q.front = 0;
}
//队列判空
bool isEmpty(SqQueue& Q) 
{
	if (Q.rear == Q.front)
		return true;
	else
		return false;
}

//入队
bool EnQueue(SqQueue& Q, ElemType x) 
{
	if ((Q.rear + 1) % MaxSize == Q.front) //Q.rear下一个是Q.front，队列满
	{
		printf("The queue is full\n");
		return false;
	}
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize;
	return true;
}

//出队
bool DeQueue(SqQueue& Q, ElemType& x) 
{
	if (Q.front == Q.rear)//队空
		return false;
	x = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	return true;
}

int main()
{
	SqQueue Q;
	bool ret;//判断返回值
	ElemType element;//用于存放出队元素

	//初始化队列
	InitQueue(Q);
	ret = isEmpty(Q);//队列判空
	if (ret) {
		printf("The queue is empty!\n");
	}else{
		printf("The queue is not empty!\n");
	}

	//入队
	EnQueue(Q, 1001);
	EnQueue(Q, 1002);
	EnQueue(Q, 1003);
	EnQueue(Q, 1004);
	EnQueue(Q, 1005);
	EnQueue(Q, 1006);

	//出队
	for (int i = 0; i <= 2; i++) {
		ret = DeQueue(Q, element);
		if (ret) {
			printf("Out Queue sucessfully! Element:%d\n", element);
		}else {
			printf("Out Queue failed!\n");
		}
	}
	system("pause");
}