/*
9 10
ABCDEFGHI
0   1
0   3
0   4
1   2
1   4
2   5
3   6
4   6
6   7
7   8
*/
#include <iostream>
#include <queue>
using namespace std;
const int N = 20;

//数据结构，一维数组存点，二维数组存边
typedef struct {
    char vertex[N];
    int adj[N][N]; //邻接矩阵
    int n, e; //点数，边数
}MatGraph;

//创建图
void CreatGraph(MatGraph& g) {
    cin >> g.n >> g.e;
    for (int i = 0; i < g.n; i++) {
        cin >> g.vertex[i];
    }
    //初始化邻接矩阵
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            g.adj[i][j] = 0;
        }
    }

    int u, v;
    for (int i = 0; i < g.e; i++) {
        cin >> u >> v;
        g.adj[u][v] = g.adj[v][u] = 1;
    }
}

//DFS
void DFS(const MatGraph& g, int v0, int visited[]) {
    cout << g.vertex[v0] << ""; //访问输出
    visited[v0] = 1;
    for (int w = 0; w < g.n; w++) {
        if (g.adj[v0][w] == 1 && !visited[w])
            DFS(g, w, visited); //遍历v0这一行没有被visited的w开始
    }
}
void TraverseGraph(const MatGraph &g) { //const变量，遍历不被修改
    int visited[N] = { 0 };
    for (int i = 0; i < g.n; i++) { //从第i个开始遍历
        if (!visited[i])
            DFS(g, i, visited);
    }
}


//BFS
void BFS(const MatGraph& g, int v0, int visited[]) {
    queue<int>q; //定义一个队列
    cout << g.vertex[v0] << "";
    visited[v0] = 1;
    q.push(v0); //读取后入队
    int v;
    while (!q.empty()) {
        v = q.front(); //获取队头元素
        q.pop(); //弹出队头元素
        for (int w = 0; w < g.n; w++) {
            if (g.adj[v][w] == 1 && !visited[w]) { //获取没有访问到的邻接点（v这一行）
                cout << g.vertex[w] << "";
                visited[w] = 1;
                q.push(w); //先访问再入队
            }
        }

    }
}

void TraverseGraph2(const MatGraph& g) { //const变量，遍历不被修改
    int visited[N] = { 0 };
    for (int i = 0; i < g.n; i++) { //从第i个开始遍历
        if (!visited[i])
            BFS(g, i, visited);
    }
}


int main()
{
    MatGraph g;
    CreatGraph(g);
    TraverseGraph(g);
    cout << "\n";
    TraverseGraph2(g);
    cout << "\n";
    system("pause");
}