#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef int ElemType;
/*
typedef struct {
	ElemType data;
	struct Lnode* next;
}LNode, *Linklist;


这种定义结构体报错
*/
typedef struct Lnode {
	ElemType data;
	Lnode* next;
}*Linklist;

//1.头插法建立链表
Linklist List_head_insert(Linklist& L)
{
	Linklist s;
	ElemType x;
	L = (Linklist)malloc(sizeof(Lnode));
	L->next = NULL;
	scanf("%d", &x);
	while (x != -1)
	{
		s = (Linklist)malloc(sizeof(Lnode));
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf("%d", &x);
	}
	return L;
}

//2.尾插法建立链表
Linklist List_tail_insert(Linklist& L)
{
	int x;
	L = (Linklist)malloc(sizeof(Lnode));
	Linklist s, r = L;
	scanf("%d", &x);
	while (x != -1)
	{
		s = (Linklist)malloc(sizeof(Lnode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = NULL;
	return L;
}

//3.按序号查找节点
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

//4.按数值查找节点
int LocateElem(Linklist L, ElemType e)
{
	int k = 1;
	Linklist p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
		k++;
	}
	return k;
}

//5.链表插入节点
bool ListFrontInsert(Linklist L, int i, ElemType e)
{
	Linklist p = GetElem(L, i - 1);
	if (p == NULL)
		return false;
	Linklist s = (Linklist)malloc(sizeof(Lnode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

//6.链表删除节点
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

//7.打印链表
void Printlist(Linklist L)
{
	L = L->next;
	while (L != NULL)
	{
		printf("%3d", L->data);
		L = L->next;
	}
	printf("\n");
}

int main()
{
	Linklist L;
	Linklist search;
	//?<=> LNode* L;

	//test：0 1 2 3 4 -1
	//1.头插法反序建立单链表
	//List_head_insert(L);
	//Printlist(L);

	//2.尾插法反序建立单链表
	List_tail_insert(L);
	Printlist(L);

	//3.按序号查找
	search = GetElem(L, 2);
	if (search != NULL) {
		printf("查找成功\n");
		printf("查找数值为%d\n", search->data);
	}

	//4.按数值查找
	int number;
	number = LocateElem(L, 4);
	if (search != NULL) {
		printf("查找成功\n");
		printf("查找序号为%d\n", number);
	}

	//5.插入节点
	ListFrontInsert(L, 2, 99);
	Printlist(L);

	//6.删除节点
	ListDelete(L, 4);
	Printlist(L);
	system("pause");
}