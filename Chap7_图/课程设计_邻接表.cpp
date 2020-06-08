#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX 5000
#pragma warning(disable:4996)

/*
2000点数据发生栈溢出，其它没有问题
*/

//数据结构
//邻接表 后面的结点（边的顶点）
typedef struct ENode {
	int ivex; //这条边顶点索引位置
	struct ENode* next_edge; //指向下一条弧的指针
}ENode, * PENode;

//邻接表 每一行头结点（点的顶点）
typedef struct VNode {
	int data; //顶点存的数据
	ENode* first_edge;
}VNode;

//邻接表定义图
typedef struct LGraph {
	int vexnum; //顶点数目
	int edgnum; //边的数目
	VNode vexs[MAX];
}LGraph;


//获取点ch在 邻接表头数组 的索引 
//用static int ？？
static int getposition(LGraph g, int ch) { //静态函数
	int i;
	for (i = 0; i < g.vexnum; i++) {
		if (g.vexs[i].data == ch)
			return i;
	}
	return -1;
}

//将node连接到链表尾
static void link_last(ENode* list, ENode* node) {
	ENode* p = list;
	while (p->next_edge)
		p = p->next_edge;  //找到表尾
	p->next_edge = node;  //将node连接至表尾
}


//创建无向图的邻接表结构
LGraph* creat_example_lgraph() {
	int c1, c2;
	int n, m;
	scanf("%d %d", &n, &m);
	int vexs[MAX];
	int edges[MAX][2];
	for (int k = 0; k < n; k++) {
		vexs[k] = k + 1;
	};
	for (int k = 0; k < m; k++) {
		scanf("%d %d", &edges[k][0], &edges[k][1]);
	}

	int vlen = n; //宏函数：求定点数
	int elen = m; //宏函数：求边数
	int i, p1, p2;

	ENode* node1;
	ENode* node2;
	LGraph* pG; //定义一个图

	if ((pG = (LGraph*)malloc(sizeof(LGraph))) == NULL)
		return NULL; //申请一个图的空间
	memset(pG, 0, sizeof(LGraph)); //??

	//向图中赋值边数与顶点数
	pG->vexnum = vlen;
	pG->edgnum = elen;

	//向邻接表中一个个放顶点
	for (i = 0; i < pG->vexnum; i++) {
		pG->vexs[i].data = vexs[i];
		pG->vexs[i].first_edge = NULL;
	}

	//向邻接表中一个个放 边结点
	for (i = 0; i < pG->edgnum; i++) {
		c1 = edges[i][0]; //第i条边的起点
		c2 = edges[i][1]; //第i条边的终点
		p1 = getposition(*pG, c1); //获取从起点c1在邻接表头数组的索引
		p2 = getposition(*pG, c2); //获取从终点c2在邻接表头数组的索引

		//node1
		node1 = (ENode*)calloc(1, sizeof(ENode)); //申请一个node空间存终点（c2）
		node1->ivex = p2; //仅放邻接表头索引
		if (pG->vexs[p1].first_edge == NULL)
			pG->vexs[p1].first_edge = node1; //将node1连接到“p1”（表头）所在链表末尾
		else
			link_last(pG->vexs[p1].first_edge, node1); //将node1连接到本行邻接表末尾
		//node2
		node2 = (ENode*)calloc(1, sizeof(ENode));
		node2->ivex = p1;
		if (pG->vexs[p2].first_edge == NULL)
			pG->vexs[p2].first_edge = node2;
		else
			link_last(pG->vexs[p2].first_edge, node2);
	}
}

//打印邻接表
void print_lgraph(LGraph G) {
	int i;
	ENode* node;
	printf("List Graph:\n");
	for (i = 0; i < G.vexnum; i++) {
		printf("%d(%d):", i, G.vexs[i].data);
		node = G.vexs[i].first_edge;
		while (node != NULL) {
			printf("%d(%d):", node->ivex, G.vexs[node->ivex].data);
			node = node->next_edge;
		}
		printf("\n");
	}
}

//排序邻接表（不要在指针里面操作，转到数组中操作，否则容易乱）
void Sort(LGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		ENode* head = G.vexs[i].first_edge;
		int adjarray[MAX];
		int j = 0, temp;
		while (head) {
			adjarray[j] = head->ivex;
			head = head->next_edge;			
			j++;
		}
		for (int k = 0; k < j - 1; k++) {
			for (int s = k + 1; s < j; s++) {
				if (G.vexs[adjarray[k]].data > G.vexs[adjarray[s]].data) {
					temp = adjarray[k];
					adjarray[k] = adjarray[s];
					adjarray[s] = temp;
				}
			}
		}
		ENode* p = G.vexs[i].first_edge;
		j = 0;
		while (p) {
			p->ivex = adjarray[j++];
			p = p->next_edge;
		}
	}
}

//广度优先遍历
void BFS(LGraph G) { //传给函数的是结构体
	int head = 0;
	int rear = 0; //队列头和尾
	int queue[MAX]; //辅助队列
	int visited[MAX]; //访问标记数组
	int i, j, k;
	ENode* node;
	ENode* nodetemp;

	//将每个顶点visited数组设置为未访问
	for (i = 0; i < G.vexnum; i++) {
		visited[i] = 0;
	}

	//从索引为0的顶点开始遍历
	//printf("BFS: ");
	for (i = 0; i < G.vexnum; i++) { //对每一个连通分量使用BFS，避免不连通图
		if (!visited[i]) { //未被访问过
			visited[i] = 1;
			printf("%d ", G.vexs[i].data);
			queue[rear++] = i; //访问后入队
		}

		while (head != rear) { //队列不空
			j = queue[head++]; //队头元素(的索引)出队列
			node = G.vexs[j].first_edge;
			//需要遍历这条邻接表找最小
			while (node != NULL) { //遍历这一条邻接表的所有node
				k = node->ivex; //k是node数组索引
				if (!visited[k]) {
					visited[k] = 1;
					printf("%d ", G.vexs[k].data);
					queue[rear++] = k; //访问后入队
				}
				nodetemp = node->next_edge;
				node = node->next_edge; //去下一条弧
			}
		}
	}
	printf("\n");
}

//深度优先DFS
static void DFS(LGraph G, int i, int* visited) {
	ENode* node;
	visited[i] = 1;
	printf("%d ", G.vexs[i].data);
	node = G.vexs[i].first_edge; //向后指
	while (node != NULL) {  //向第一边的方向不断深入
		if (!visited[node->ivex])
			DFS(G, node->ivex, visited);
		node = node->next_edge; //找邻接表下一个
	}

}

//深度优先遍历DFSTraverse
void DFSTraverse(LGraph G) {
	int visited[MAX]; //访问标记数组
	for (int i = 0; i < G.vexnum; i++) { //初始化所有顶点未被访问
		visited[i] = 0;
	}
	//printf("DFS: ");
	for (int i = 0; i < G.vexnum; i++) {  //从第一个连通分量开始遍历
		if (!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}

int main() {
	LGraph* pG;
	//1.无向图的创建
	pG = creat_example_lgraph();
	//2.以邻接表打印图
	//print_lgraph(*pG);
	//3.邻接表排序
	Sort(*pG);
	//4.广度优先遍历
	BFS(*pG);
	//5.深度优先遍历
	DFSTraverse(*pG);
	system("pause");
}