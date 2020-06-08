#include "function.h"

//��ʼ��ջ
void InitStack(SqStack& S)
{
	S.top = -1;
}

//ջ���пգ���ջ����true
bool StackEmpty(SqStack& S)
{
	if (S.top == -1)
		return true;
	else
		return false;
}

//��ջ
bool Push(SqStack& S, ElemType x)
{
	if (S.top == MaxSize - 1) //����Խ��
	{
		return false;
	}
	S.data[++S.top] = x;
}

//��ȡջ��Ԫ��
bool GetTop(SqStack& S, ElemType& x)
{
	if (S.top == MaxSize - 1) //����Խ��
	{
		return false;
	}
	x = S.data[S.top];
}

//����ջ��Ԫ��
bool Pop(SqStack& S, ElemType& x)
{
	if (S.top == -1) //ջ�գ��޷�����
	{
		return false;
	}
	x = S.data[S.top--];
	return true;

}
