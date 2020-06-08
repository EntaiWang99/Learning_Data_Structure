#include "function.h"

//初始化栈
void InitStack(SqStack& S)
{
	S.top = -1;
}

//栈的判空，空栈返回true
bool StackEmpty(SqStack& S)
{
	if (S.top == -1)
		return true;
	else
		return false;
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
bool GetTop(SqStack& S, ElemType& x)
{
	if (S.top == MaxSize - 1) //访问越界
	{
		return false;
	}
	x = S.data[S.top];
}

//弹出栈顶元素
bool Pop(SqStack& S, ElemType& x)
{
	if (S.top == -1) //栈空，无法弹出
	{
		return false;
	}
	x = S.data[S.top--];
	return true;

}
