//#include<bits/stdc++.h>
/*
5 10
1 2 2
1 3 4
1 4 1
2 5 5
3 4 3
2 4 1
4 5 4
2 3 2
3 5 4
1 5 2*/
#include <iostream>
#include <cstring>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const int N = 20;
const int inf = 9999;
int adj[N][N]; //邻接矩阵
int visited[N]; //visited数组
int d[N]; //表示结点i与树T结点之间最小的边权值
int n, m;

int main(){
	cin >> n >> m;
	memset(d, inf, sizeof d);  //初始化d数组至inf
	memset(visited, 0, sizeof visited);  //初始化visited数组至0
	memset(adj, inf, sizeof adj);  //初始化adj数组至inf
	for (int i = 1; i <= n; i++) {
		adj[i][i] = 0; //对角线元素为0
	}
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u][v] = adj[v][u] = w;
	}

		int cost = 0; //最小生成树的cost
		d[1] = 0;
		for (int i = 1; i <= n - 1; i++) { //找其余n-1个结点
			int mind = inf;
			int index = 1;
			for (int j = 1; j <= n; j++) { //找生成树下一个结点
				if (!visited[j] && (d[j] < mind)) {
					index = j;
					mind = d[j];
				}	
			}
			visited[index] = 1; //x已被访问
			for (int k = 1; k <= n; k++) { //找到一个点后，更新d[y]数组
				if (!visited[k]) {
					d[k] = min(d[k], adj[index][k]);
				}
			}
		}
		bool flag = false;
		for (int i = 2; i <= n; i++) {
			cost += d[i];
			if (d[i] == inf)
				flag = true; //依然有边未加入树中->不存在MST
		}
		if (flag)
			cout << "Failed";
		else {
			cout << cost << "";
			cout << "\n";
		}
}

