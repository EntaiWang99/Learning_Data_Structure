#include<stdio.h>
#include<iostream>
#include<stdlib.h>

/*
10 10
4
4
5
1
2
3
3
4
2
2
*/

using namespace std;
typedef int HTKeyType;
//哈希表数据状态
typedef enum State { //枚举类型
	EMPTY, //空
	EXITST, //存在有效数据
	DELETE //已被删除
}State;

//哈希表中的数据结构体
typedef struct Hashdata {
	State state;
	HTKeyType key;
}HashData;

//哈希表结构体
typedef struct HashTable {
	HashData* table; //数组
 	int len; //表长
	int size; //有效元素数量
}HashTable;

void HashTableInit(HashTable* ht, int len) {
	ht->table = (HashData*)malloc(sizeof(HashData) * len); //动态开辟数组
	ht->len = len;
	ht->size = 0; //没有有效元素
	//所有数据置空
	for (int i = 0; i < ht->len; i++) {
		ht->table[i].state = EMPTY;
	}
}

//计算哈希函数
int GetPosition(HashTable* ht, HTKeyType key) {
	return key % 11;
}

//查找
int HashTableFind(HashTable* ht, HTKeyType key) {
	//确定哈希地址
	int index = GetPosition(ht, key);
	int count = 0;
	//如果冲突，线性查找
	while (ht->table[index].state != EMPTY) {
		if (ht->table[index].key == key) { //发现key值一样
			if (ht->table[index].state == EXITST) {//这个元素状态是存在
				count++;
				return count;
			}
			else { //这个元素处于删除状态
				return 0;
			}
		}
		else {
			count++;
			index++; //找下一个
		}
	}
	return count;
}

//插入
int HasnTableInsert(HashTable* ht, HTKeyType key) {
	//确定插入位置
	int index = GetPosition(ht, key);
	//产生冲突，处理冲突
	while (ht->table[index].state == EXITST) {
		if (ht->table[index].key == key) { //存在相同元素，插入失败
			return 0;
		}
		else {
			++index;
		}
	}
	//找到位置，插入元素
	ht->table[index].state = EXITST;
	ht->table[index].key = key;
	ht->size++;
}

int main() {
	int n, m;
	cin >> n >> m;
	HashTable ht;
	//初始化哈希表
	HashTableInit(&ht, n);
	for (int i = 1; i <= m; i++) {
		HTKeyType key;
		cin >> key;
		int count;
		count = HashTableFind(&ht, key);
		if (count == 0) {
			cout << "NO" << endl;
			HasnTableInsert(&ht, key);
		}
		else {
			cout << count << endl;
		}
	}
}

