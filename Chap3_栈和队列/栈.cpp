#include<stdio.h>
#include<stdlib.h>

#define MaxSize 50
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int top;
}SqStack;

//初始化栈
void InitStack(SqStack& S)
{
	S.top = -1;
}

//栈的判空
bool StackEmpty(SqStack& S)
{
	if (S.top == -1)
		return false;
	else
		return true;
}

//入栈
bool Push(SqStack& S, ElemType x) 
{
	if (S.top == MaxSize - 1) //访问越界
	{
		return false;
	}
	S.data[++S.top] = x;
}

//读取栈顶元素
bool GetTop(SqStack& S, ElemType &x)
{
	if (S.top == MaxSize - 1) //访问越界
	{
		return false;
	}
	x = S.data[S.top] ;
}

//弹出栈顶元素
bool pop(SqStack& S, ElemType &x)
{
	if (S.top == - 1) //栈空，无法弹出
	{
		return false;
	}
	x = S.data[S.top--];
	return true;

}

int main()
{
	SqStack S;
	bool flag;
	ElemType m;//用于存放读取/弹出元素

	//初始化栈
	InitStack(S);
	//栈的判空
	flag = StackEmpty(S);
	if (flag) 
	{
		printf("The Stack is empty!");
	}
	//入栈
	Push(S, 1001);
	Push(S, 1002);
	Push(S, 1003);
	Push(S, 1004);
	Push(S, 1005);
	//获取栈顶元素m
	flag = GetTop(S, m);
	{
		printf("The top element is %d\n",m);
	}
	//弹出栈顶元素（弹出时数据并没有从内存中消失，只是top指针位置变化）
	flag = pop(S, m);
	flag = pop(S, m);
	flag = pop(S, m);

	if (flag)
	{
		printf("The pop element is %d\n", m);
	}
	system("pause");
}