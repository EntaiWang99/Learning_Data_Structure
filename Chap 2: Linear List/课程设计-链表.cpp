#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
/*
struct staff{
	char Name[10];
	char Position[10];
	int id;
};

typedef struct LNode{
	struct staff data;
	LNode* next;
}*Linklist;
可以定义双重结构体?
*/

typedef struct LNode {
	char Name[20];
	char Position[20];
	int id;
	LNode* next;
}*Linklist;

Linklist List_tail_insert(Linklist& L, int n)
{
	char name[20];
	char position[20];
	int no;
	L = (Linklist)malloc(sizeof(LNode));
	Linklist s, r = L;
	int k = 0;
	while (k<n)
	{
 		scanf("%s %s %d", name, position, &no);
		s = (Linklist)malloc(sizeof(LNode));
		strcpy(s->Name,name);
		strcpy(s->Position, position);
		s->id = no;
		r->next = s;
		r = s;
		k++;
	}
	r->next = NULL;
	return L;
}

Linklist GetElem(Linklist L, int i)
{
	int j = 1;
	Linklist p = L->next;
	if (i == 0) {
		return L;//查找序号为0的元素，返回L
	}
	if (i < 1) {
		return NULL;//查找序号为非法序号的值
	}
	while (p && j < i) {
		p = p->next;
		j++;
	}
	return p;
}

bool ListDelete(Linklist L, int i)
{
	Linklist p = GetElem(L, i - 1);
	if (p == NULL)
		return false;
	Linklist q;
	q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

bool ListFrontInsert(Linklist& L)
{	char name[20];
	char position[20];
	int no;
	int x;
	scanf("%d %s %s %d", &x, name, position, &no);
	Linklist p = GetElem(L, x - 1);
	if (p == NULL)
		return false;
	Linklist s = (Linklist)malloc(sizeof(LNode));
	strcpy(s->Name, name);
	strcpy(s->Position, position);
	s->id = no;
	s->next = p->next;
	p->next = s;
	return true;
}
//报错：数组越界或指针越界
//Run-Time Check Failure #2 - Stack around the variable 'position' was corrupted.
//方法：配置属性 -> C++ -> 代码生成 -> 基本运行时检查 -> 设置为 (1) 默认值，就不再进行 stack frame run-time error checking。

void Printlist(Linklist L)
{
	L = L->next;
	while (L != NULL)
	{
		printf("%s %s %d ", L->Name, L->Position, L->id);
		L = L->next;
	}
	printf("\n");
}

int main()
{
	int m;
	int n;
	scanf("%d %d", &n, &m);
	Linklist L;

	List_tail_insert(L,n);
	//Printlist(L);

	for (int i = 1; i <= m; i++)
	{
		int op = 0;
		bool ret;
		Linklist search;
		scanf("%d", &op);
		switch (op)
		{
		case 1://删除节点
			int number;
			scanf("%d", &number);
			ret = ListDelete(L, number);
			if (ret == false) {
				printf("-1\n");
			}
			Printlist(L);
			break;
		case 2://插入节点
			ret = ListFrontInsert(L);
			if (ret == false) {
				printf("-1\n");
			}else{
				Printlist(L);
			}
			break;
		case 3://查询节点
			scanf("%d", &number);
			search = GetElem(L, number);
			if (search != NULL) {
				printf("%s %s %d", search->Name, search->Position, search->id);
			}
			else {
				printf("-1\n");
			};
			break;
		}
	}
	system("pause");
}