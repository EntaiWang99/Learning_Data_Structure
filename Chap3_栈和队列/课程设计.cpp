#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxSize 50
typedef int ElemType;
//栈结构体
typedef struct {
	ElemType data_S[MaxSize];
	int top;
	int lenth = 0;
}SqStack;
//队列结构体
typedef struct {
	ElemType data_Q[MaxSize];
	int front, rear;
	int lenth = 0;
}SqQueue;

//初始化栈
void InitStack(SqStack& S)
{
	S.top = -1;
}
//栈的判空
bool StackEmpty(SqStack& S)
{
	if (S.top == -1)
		return true;
	else
		return false;
}
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

//打印Stack
void printStack(SqStack& S, int MaxSize_S)
{
	for (int i = 0; i < S.lenth; i++)
	{
		printf(" %4d", S.data_S[i]);
	}
}
//打印Queue
void printQueue(SqQueue& Q, int MaxSize_S)
{
	int i = Q.front;
	while(i < Q.rear)
	{
		printf(" %4d", Q.data_Q[i]);
		i = (i + 1) % MaxSize_S;
	}
}

//入栈
bool Push(SqStack& S, ElemType x, int MaxSize_S)
{
	if (S.top == MaxSize_S - 1) //访问越界
	{
		return false;
	}
	S.data_S[++S.top] = x;
	S.lenth++;
	return true;
}
//入队
bool EnQueue(SqQueue& Q, ElemType x, int MaxSize_Q)
{
	if ((Q.rear + 1) % MaxSize_Q == Q.front) //Q.rear下一个是Q.front，队列满
	{
		printf("The queue is full\n");
		return false;
	}
	Q.data_Q[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize_Q;
	Q.lenth++;
	return true;
}

//弹出栈顶元素
bool pop(SqStack& S, ElemType& x)
{
	if (S.top == -1) //栈空，无法弹出
	{
		return false;
	}
	x = S.data_S[S.top--];
	S.lenth--;
	return true;
}
bool DeQueue(SqQueue& Q, ElemType& x, int MaxSize_Q)
{
	if (Q.front == Q.rear)//队空
		return false;
	x = Q.data_Q[Q.front];
	Q.front = (Q.front + 1) % MaxSize_Q;
	Q.lenth--;
	return true;
}



int main()
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	int MaxSize_S = n;
	int MaxSize_Q = m;

	SqStack S;
	bool flag_S;
	ElemType element_S;//用于存放出栈元素
	InitStack(S);
	flag_S = StackEmpty(S);
	if (flag_S)
		printf("The Stack is empty!\n");

	SqQueue Q;
	bool flag_Q;
	ElemType element_Q;//用于存放出队元素
	InitQueue(Q);
	flag_Q = isEmpty(Q);
	if (flag_Q) 
		printf("The Queue is empty!\n");
	
	int i = 0;
	while (i < q) 
	{
		int op;
 		scanf("%d", &op);
		switch (op)
		{
			ElemType x;
		case 1:
		{
			scanf("%d", &x);
			flag_S = Push(S, x, MaxSize_S);
			if (flag_S == false) {
				EnQueue(Q, x, MaxSize_Q);
			}
			printf("parking lot:");
			printStack(S, MaxSize_S);
			printf("\n");
			printf("waiting queue:");
			printQueue(Q, MaxSize_Q);
			printf("\n");
			break;
		}
		case 2://只能所有元素出栈,然后一个个重新进栈?
		{
			ElemType search;
			int temp[MaxSize];
			int j = 0;
			scanf("%d", &search);
			flag_Q = DeQueue(Q, x, MaxSize_Q);
			if(flag_Q)//如果停车场不满的特殊情况
				temp[j++] = x;
			while (1)
			{
				pop(S, x);
				if (x == search)
					break;
				temp[j++] = x;
			}

			for (int k = 1; k <= j; k++)
			{
				Push(S, temp[j-k], MaxSize_S);
			}			
			printf("parking lot:");
			printStack(S, MaxSize_S);
			printf("\n");
			printf("waiting queue:");
			printQueue(Q, MaxSize_Q);
			printf("\n");
			break;
		}
		case 3: 
		{
			ElemType search;
			scanf("%d", &search);
			if (search > S.lenth)
				printf("-1\n");
			else
				printf("%d\n", S.data_S[search - 1]);
			break;
		}
		case 4:
		{
			ElemType search;
			scanf("%d", &search);
			if (search == 0 || search > Q.lenth)
				printf("-1\n");
			else
				printf("%d\n", Q.data_Q[Q.front + search - 1]);
			break;
		}
		}
		i++;
	}
}