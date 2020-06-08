#include<stdio.h>
#include<stdlib.h>

//��̬����
#define MaxSize 50
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int lenth;
}SqlList;

//��̬����
#define InitSize 100
typedef struct {
	ElemType* data;
	int capacity;
	int lenth;
}SeqList;

//��ӡList
void printList(SqlList& L)
{
	for (int i = 0; i < L.lenth; i++)
	{
		printf("%4d", L.data[i]);
		printf("\n");
	}
}

//�㷨2.4
bool ListInsert(SqlList& L, int i, ElemType e)
{
	if (i<1 || i>L.lenth + 1)
		return false;
	if (L.lenth >= MaxSize)
		return false;
	for (int j = L.lenth; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.lenth++;
	return true;
}
//�㷨2.5
bool ListDelete(SqlList& L, int i, ElemType& e)
{
	if (i<1 || i>L.lenth + 1)
		return false;
	e = L.data[i - 1];
	for (int j = i; j < L.lenth; j++)
		L.data[j - 1] = L.data[j];
	L.lenth--;
	return true;
}
//�㷨2.6
int LocateElem(SqlList L, ElemType e)
{
	for (int i = 0; i < L.lenth; i++)
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;
}

int main()
{
	SqlList L;
	bool ret;//����ֵ
	ElemType del;//ɾ��Ԫ��ֵ
	//��ֵ
	L.data[0] = 1;
	L.data[1] = 2;
	L.data[2] = 3;
	L.lenth = 3;

	//����
	ret = ListInsert(L, 2, 60);
	if (ret)
	{
		printf("Insert OK\n");
		printList(L);
	}
	else {
		printf("Insert Failed\n");
	}

	//ɾ��
	ret = ListDelete(L, 1, del);
	if (ret)
	{
		printf("Delete OK\n");
		printf("Delete value = %d\n", del);
	}
	else {
		printf("Delete Failed\n");
	}

	//��λ
	int pos = 0;
	pos = LocateElem(L, 3);
	if (pos)
	{
		printf("Locate OK\n");
		printf("Locate postion = %d\n", pos);
	}
	else {
		printf("Delete Failed\n");
	}
	system("pause");
}

