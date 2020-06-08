#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

/*
***input***:
3 6
alice manager 1
bob staff 2
tom staff 3
1 2
2 3 lily staff 4
2 10 bob consultant 10
3 2
2 2 bob consultant 1000
3 1000
*/

//静态分配
#define MaxSize 50
//typedef int ElemType;
typedef struct ElemType {
	char Name[20];
	char Position[20];
	int id;
};
typedef struct {
	ElemType data[MaxSize];
	int lenth;
}SqlList;

//动态分配
#define InitSize 100
typedef struct {
	ElemType* data;
	int capacity;
	int lenth;
}SeqList;

//打印List
void printList(SqlList& L)
{
	for (int i = 0; i < L.lenth; i++)
	{
		printf("%s %s %d ", L.data[i].Name, L.data[i].Position, L.data[i].id);
		//printf("\n");
	}
}
//插入元素
bool ListInsert(SqlList& L, int i)
{
	ElemType data;
	scanf("%s %s %d", data.Name, data.Position, &data.id);
	if (i<1 || i>L.lenth + 1)
		return false;
	if (L.lenth >= MaxSize)
		return false;
	for (int j = L.lenth; j >= i; j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = data;
	L.lenth++;
	return true;
}

//删除元素
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

//查询元素
bool LocateElem(SqlList L, int e)
{
	for (int i = 1; i <= L.lenth; i++)
	{
		if (i == e) {
			printf("%s %s %d ", L.data[i-1].Name, L.data[i-1].Position, L.data[i-1].id);
			return true;
		}
	}
	return false;
}

int main()
{
	SqlList L;
	bool ret;//返回值
	ElemType del;//删除的元素

	int m;
	int n;
	scanf("%d %d", &n, &m);
	int i = 1;
	L.lenth = 0;
	while (i <= n)
	{
		ListInsert(L, i);
		i++;
	}
	for (int i = 1; i <= m; i++) {
		int op = 0;
		bool ret;
		scanf("%d", &op);
		switch (op)
		{
		case 1://删除节点
			int number;
			scanf("%d", &number);
			ret = ListDelete(L, number, del);
			if (ret == false) {
				printf("-1\n");
			}else {
				printList(L);
			}
			break;
		case 2://插入节点
			int x;
			scanf("%d", &x);
			ret = ListInsert(L, x);
			if (ret == false) {
				printf("-1\n");
			}
			else {
				printList(L);
			}
			break;
		case 3://查询节点
			scanf("%d", &number);
			ret = LocateElem(L, number);
			if (ret == false) {
				printf("-1\n");
			}
			break;
		}
	}
	system("pause");
}

//Question：题干所说的“入职”代表插入or替换？