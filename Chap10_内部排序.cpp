#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#define N 1000000

using namespace std;
typedef int ElemType;
typedef struct {   //动态数组结构体
	ElemType* elem; //只保留一个整形指针
	int TableLen;
}SSTable;

//1.动态数组初始化，申请空间
void ST_Init(SSTable& ST, int len) {
	ST.TableLen = len + 1; //多一个用于存哨兵
	ST.elem = (ElemType*)malloc(sizeof(ElemType) * ST.TableLen);
}

//2.打印排序表
void ST_print(SSTable ST) {
	for (int i = 1; i < ST.TableLen; i++) {
		cout << ST.elem[i];
		cout << " ";
	}
	cout << endl;
}

//3.直接插入排序（升序）
void InsertSort(ElemType A[], int n) {
	int i, j;
	for (i = 2; i <= n; i++) { //第一个不用插
		if (A[i] < A[i - 1]) { //后一个比前一个小
			A[0] = A[i]; //把A[i]存在哨兵
			for (j = i - 1; A[0] < A[j]; --j) { //从A[i-1]向前找，满足比A[0]大的都往后移
				A[j + 1] = A[j];
			}
			A[j + 1] = A[0]; //把暂存的哨兵放进去
		}
	}
}

//4.折半插入排序（升序）
void MidInsertSort(ElemType A[], int n) {
	int i, j, low, mid, high;
	for (i = 2; i <= n; i++) {
		A[0] = A[i];
		low = 1; high = i - 1; //为啥是i-1，不是n-1：在已经排好的元素中插入
		while (low <= high) { //二分查找位置,还是要加“=”的，退出条件一定是low>high
			mid = (low + high) / 2;
			if (A[mid] > A[0]) //mid大，在左边
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j >= high + 1; --j) { //最后一个开始，A[0]就该放在high+1这个位置，后面的统统后移
			A[j + 1] = A[j];
		}
		A[high + 1] = A[0];
	}
}

//5.冒泡排序
void Swap(ElemType& a, ElemType& b) {
	ElemType temp;
	temp = a;
	a = b;
	b = temp;
}
void BubbleSort(ElemType A[], int n) {
	int i, j;
	bool flag;
	for (i = 1; i < n; i++) { //两层循环的含义？？
		//一轮冒上去一个
		flag = false;
		for (j = n; j > i; j--) { //把最小值放在最前面
			if (A[j - 1] > A[j]) {
				Swap(A[j - 1], A[j]);
				flag = true;
			}
		}
		if (flag == false)  //扫一边发现没有换的，提前结束
			return;
	}
}

//6.快速排序(递归实现)
int Partition(ElemType A[], int low, int high) {
	ElemType pivot = A[low];
	while (low < high) { //注意多个while循环，外层的不能代替内层的，因为high，low在内层会变
		//这个while循环就是不断的把大的右移，小的左移，空出pivot该放的位置
		while (low < high && A[high] > pivot)
			high--;
		A[low] = A[high];
		while (low < high && A[low] <= pivot)
			low++;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}
void QuickSort(ElemType A[], int low, int high) {
	if (low < high) {
		int pivotpos = Partition(A, low, high); //一次分割，把枢轴排到合适位置
		QuickSort(A, low, pivotpos - 1); //排左边
		QuickSort(A, pivotpos + 1, high); //排右边
	}
}

//7.简单选择排序
void SelectSort(ElemType A[], int n) {
	int i, j, min; //min为最小元素下标
	for (i = 1; i < n; i++) { //第一个哨兵不用
		min = i;
		for (j = i + 1; j < n; j++) {
			if (A[j] < A[min])
				min = j;
		}
		if (min != i) {
			Swap(A[i], A[min]);
		}
	}
}

//8.堆排序
//调整某一个非叶子结点
void AdjustDown(ElemType A[], int k, int len) { //k:需要调整的非叶子结点
	int i;
	A[0] = A[k]; //把待调整的A[k]存起来，好空出一个位置
	for (i = 2 * k; i <= len; i *= 2) { //从第2k个左孩子开始，一行行下沉下去
		if (i < len && A[i] < A[i + 1]) { //先看左孩子
			i++; //不行看右孩子
		}
		if (A[0] >= A[i])
			break; //父节点大，不用换了，直接break
		else {
			A[k] = A[i];
			k = i; //i赋给k，孩子变父亲，继续下一轮循环下沉
		}
	}
	A[k] = A[0]; //暂存的放回去
}
//建大顶堆
void BuildMaxHeap(ElemType A[], int len) {
	for (int i = len / 2; i > 0; i--) { //从最后一个非叶子结点开始
		AdjustDown(A, i, len);
	}
}

void HeapSort(ElemType A[], int n) {
	int i;
	BuildMaxHeap(A, n); //建大顶堆
	for (i = n; i > 1; i--) {
		Swap(A[i], A[1]); //堆顶元素交换到堆底
		AdjustDown(A, 1, i - 1); //剩余元素继续排堆
	}
}

//9.归并排序(二路归并)
void Merge(ElemType A[], int low, int mid, int high) {
	ElemType B[N]; //辅助数组，用于存待排序的元素
	int i, j, k;
	for (k = low; k <= high; k++) { //把low-high中的元素先放进B中(两个一块放进去，后面用mid区分)
		B[k] = A[k];
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) { //合并两个有序数组
		if (B[i] <= B[j])
			A[k] = B[i++];
		else
			A[k] = B[j++];
	}
	while (i <= mid) { //放进剩余元素
		A[k++] = B[i++];
	}
	while (j <= high) {
		A[k++] = B[j++];
	}
}
void MergeSort(ElemType A[], int low, int high) { //low,high为需要排序的起止元素
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(A, low, mid);
		MergeSort(A, mid + 1, high);
		Merge(A, low, mid, high);
	}
}



int main() {
	SSTable ST;
	int n; //数据量
	cin >> n;
	ST_Init(ST, n); //申请动态数组空间
	/*
	int A[10] = { 64,94,95,79,69,84,18,22,12,99 };
	for (int i = 0; i < ST.TableLen; i++) {
		ST.elem[i+1] = A[i];
	}
	*/
	
	for (int i = 0; i < n; i++) {
		cin >> ST.elem[i + 1];
	}

	//1.直接插入排序
	//InsertSort(ST.elem, n);
	
	//2.折半插入排序
	//MidInsertSort(ST.elem, n);

	//3.交换排序：冒泡排序
	//BubbleSort(ST.elem, n); 
	
	//4.交换排序：快速排序（递归）
	//QuickSort(ST.elem, 1, n);

	//5.简单选择排序
	//SelectSort(ST.elem, n);

	//6.堆排序
	//HeapSort(ST.elem, n);

	//7.归并排序
	MergeSort(ST.elem, 1, n);

	ST_print(ST);
	system("pause");
}

