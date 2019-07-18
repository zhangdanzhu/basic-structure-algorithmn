/** @file merge_sort.cpp
 * @brief 归并排序及其优化和测试.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  优化：1：对于arr[mid] <= arr[mid+1]的情况,不进行merge 2：对于小数组, 使用插入排序；
 * @history
 *	 July 18,2019 - v1.0.0 - zdz - 初稿-仅递归版本，无迭代版本 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// 测试数据数量（未考虑内存溢出分配不成功问题） 
#define MAX 100000		// 定义最大值（测试数据最大50000） 用于设置哨兵 
#define MIN 50			// 当待排序数组元素个数小于MIN时使用插入排序 


/*********************************************************** 
* 未优化归并 
************************************************************/ 
/** 
 * @brief 未优化归并排序使用的合并函数[从小到大]（TODO 不完善） 
 * @param a:待排序数组; start，mid:第一段排好序的待合并元素范围，相应[mid+1, end]为第二段 
 * @return void	 
 * @note
 */
template<typename T>
void merge0(T *a, int start, int mid, int end) {
	// 一般可以考虑开辟一个新的满足总长的数组，然后排序在新的数组上，最后复制回原数组 
	// 这里开辟两个数组存放两段原数据，直接在原数组上存最终排序，并借助哨兵使代码简洁
	
	int size_left = mid - start + 1;	// 左半段数量 
	int size_right = end - mid;			// 右半段数量 
	T* left = new T[size_left + 1];		// 加1是为了多加一个哨兵位 
	T* right = new T[size_right + 1];
	int i = 0, j = 0, k = 0;			// 循环计数变量 
	
	// 复制 
	for (i = 0; i < size_left; ++i) {
		left[i] = a[start+i];
	}
	for (i = 0; i < size_right; ++i) {
		right[i] = a[mid+1+i];
	}
	// 加哨兵
	left[size_left] = MAX;
	right[size_right] = MAX; 
	
	// 按序生成新的数组
	for (k = start, i = 0, j = 0; k <= end; ++k) {
		if (left[i] <= right[j]) {
			// “<=” 保证稳定性
			a[k] = left[i];
			++i; 
		}
		else {
			a[k] = right[j];
			++j;
		}
	}
	// 释放动态内存 
	delete [] left;
	delete [] right; 
}
/** 
 * @brief 未优化归并排序使用的递归函数[从小到大]（TODO 不完善） 
 * @param a:待排序数组; start，end:待合并元素范围	
 * @return void	 
 * @note
 *	-可改进点: 1.两段排序后先看是否需要排序2.对于小数组使用插入排序；
 */
template<typename T>
void merge_sort0_r(T *a, int start, int end) {
	// 凡递归，先考虑递归终止条件
	if (start >= end) {
		return ;
	} 
	
	int mid = start+((end-start)>>1);	// 中间元素下标
	// 两段数据分开进行排序
	merge_sort0_r(a, start, mid);
	merge_sort0_r(a, mid+1, end);
	// 合并 
	merge0(a, start, mid, end);
}
/** 
 * @brief 未优化归并排序（递归版）[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	直接修改原 
 * @note
 *	-时间复杂度：最好 - O（nlog）；最坏 - O（nlogn）；平均 - O（nlogn）  【与待排序数据的有序度无关】 
 *	-空间复杂度：O(n);  ！！！不是原地排序算法！！！ 
 *	-稳定性：稳定【取决于merge】 
 *	-改进点: 1：对于arr[mid] <= arr[mid+1]的情况,不进行merge 2：对于小数组, 使用插入排序；
 */
template<typename T> 
void merge_sort0(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	// 递归进行归并排序
	merge_sort0_r(a, 0, len-1); 
} 




/*********************************************************** 
* 归并优化1 
************************************************************/ 
/** 
 * @brief 归并排序优化1使用的递归函数[从小到大]（TODO 不完善） 
 * @param a:待排序数组; start，end:待合并元素范围	
 * @return void	 
 * @note
 *	-改进点: 两段排序后先看是否需要排序；
 */
template<typename T>
void merge_sort1_r(T *a, int start, int end) {
	// 凡递归，先考虑递归终止条件
	if (start >= end) {
		return ;
	} 
	
	int mid = start+((end-start)>>1);	// 中间元素下标
	// 两段数据分开进行排序
	merge_sort1_r(a, start, mid);
	merge_sort1_r(a, mid+1, end);
	// 若无序则合并
	if (a[mid] > a[mid+1]) {
		merge0(a, start, mid, end);
	} 
}
/** 
 * @brief 归并排序优化1（递归版）[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	直接修改原 
 * @note
 *	-改进点：merge之前先判断 
 */
template<typename T> 
void merge_sort1(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	// 递归进行归并排序
	merge_sort1_r(a, 0, len-1); 
} 


/*********************************************************** 
* 归并优化2 
************************************************************/ 
template<typename T> 
void insert_sort(T *a, int start, int end) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || (end-start) <= 0) {
		return;
	}
	
	int cur = 0;	// 当前待排序的数据
	int j = 0;		// 内层循环（移动数据）计数变量   
	
	// 对未排序区间进行遍历 
	for (int i = start; i <= end; ++i) {
		// 记录当前数据值
		cur = a[i]; 
		// 在已排序区间中查找插入位置
		for (j = i-1; j >= start; --j) {
			if (a[j] > cur) {
				// 未找到插入位置，则往后移动已排序数据 
				a[j+1] = a[j]; 
			}
			else {
				// 比当前值小，则找到插入位置，结束循环 
				break;	
			}
		}  
		a[j+1] = cur; 
	} 
} 
/** 
 * @brief 归并排序优化2使用的递归函数[从小到大]（TODO 不完善） 
 * @param a:待排序数组; start，end:待合并元素范围	
 * @return void	 
 * @note
 *	-改进点: 数据少的时候使用插入排序；
 */
template<typename T>
void merge_sort2_r(T *a, int start, int end) {
	// 凡递归，先考虑递归终止条件
	if (start >= end) {
		return ;
	} 
	// 若数据量小则直接使用插入排序 
	if (end - start < MIN) {
		insert_sort(a, start, end);
	}
	else {
		int mid = start+((end-start)>>1);	// 中间元素下标
		// 两段数据分开进行排序
		merge_sort2_r(a, start, mid);
		merge_sort2_r(a, mid+1, end);
		// 若无序则合并
		if (a[mid] > a[mid+1]) {
			merge0(a, start, mid, end);
		} 
	}
}
/** 
 * @brief 归并排序优化2（递归版）[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	直接修改原 
 * @note
 *	-改进点: 归并之前判断+数据少的时候使用插入排序；
 */
template<typename T> 
void merge_sort2(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	// 递归进行归并排序
	merge_sort2_r(a, 0, len-1); 
} 



/******************************************* 
* 简单测试
*******************************************/ 
int main(int argc, char** argv) {
	// 计时用变量 
	clock_t start,finish;
	double totaltime;
 
	int standard[MAXNUM];	// 标准
	int test[MAXNUM];			// 测试用数组 
 
	/************************************** 
	* 测试自带排序，给出标准答案 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) {
		standard[i] = rand() % 50000 + 1;
	}

	int len = sizeof(standard)/sizeof(int);
	// 计时 
	start = clock();
	sort(standard, standard+len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"algorithm中排序函数运行时间为"<<totaltime<<"秒！"<<endl;	
	
	
	/************************************** 
	* 测试普通归并排序
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// 记录时间 
	start = clock();
	merge_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"归并排序未优化运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* 测试归并排序优化1 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// 记录时间 
	start = clock();
	merge_sort1(test, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"归并排序优化1运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	/************************************** 
	* 测试归并排序优化2 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// 记录时间 
	start = clock();
	merge_sort2(test, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"归并排序优化2运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
}
