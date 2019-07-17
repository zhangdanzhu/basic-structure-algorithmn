/** @file selection_sort.cpp
 * @brief 选择排序及其优化和测试.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  优化1：每次找最小值和最大值，安排两个数；
 * @history
 *	 July 17,2019 - v1.0.0 - zdz - 初稿 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// 测试数据数量（未考虑内存溢出分配不成功问题） 


/** 
 * @brief 选择排序[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	原地排序，直接修改
 * @note
 *	-时间复杂度：最好 - O（n^2）；最坏 - O（n^2）；平均 - O（n^2） 
 *	-空间复杂度：O(1);是原地排序算法 
 *	-稳定性：！！！不稳定！！！ 
 *	-改进点: 改进-1.每次找最小值和最大值两个数 
 */
template<typename T> 
void select_sort0(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int min = 0;	// 当前待排序的数据中最小值的下标 
	int j = 0;		// 内层循环（移动数据）计数变量   
	T temp = 0;		// 用于数据交换的临时变量 
	
	// 对未排序区间进行遍历 
	for (int i = 0; i < len; ++i) {
		min = i;
		// 在未排序区间中查找最小值 
		for (j = i+1; j < len; ++j) {
			if (a[j] < a[min]) {
				// 更新最小值下标 
				min = j; 
			}
		}  
		// 数据交换 
		temp = a[i];
		a[i] = a[min];
		a[min] = temp; 
	} 
} 


/** 
 * @brief 选择排序优化1[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	原地排序，直接修改
 * @note
 *	-时间复杂度：与未优化相同，但是耗时是原来的一半左右 
 *	-空间复杂度：O(1);是原地排序算法 
 *	-稳定性：！！！不稳定！！！ 
 *	-改进点: 每次找最小值和最大值两个数 
 */
template<typename T> 
void select_sort1(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int min = 0;	// 当前待排序的数据中最小值的下标 
	int max = 0; 	// 当前待排序的数据中最小值的下标 
	int j = 0;		// 内层循环（移动数据）计数变量
	int k = len;   	// 记录已排序空间中最大值的交换位 
	T temp = 0;		// 用于数据交换的临时变量 
	
	// 对未排序区间进行遍历 (每次更新头尾的位置)
	for (int i = 0; i < k; ++i,--k) {
		min = i;
		max = i; 
		// 在未排序区间中查找最小值和最小值 
		for (j = i+1; j < k; ++j) {
			if (a[j] < a[min]) {
				// 更新最小值下标
				min = j; 
			}
			if (a[j] > a[max]) {
				// 更新最大值下标 
				max = j;
			} 
		} 
		if (min != i) {
			// 数据交换-最小值 
			temp = a[i];
			a[i] = a[min];
			a[min] = temp; 
		} 
		if (max == i) {
			// 防止之前的已经被换掉
			max = min; 
		}
		if (max != k-1) {
			// 数据交换-最大值 
			temp = a[k-1];  
			a[k-1] = a[max];
			a[max] = temp;	
		} 
	} 
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
	* 测试普通插入排序
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// 记录时间 
	start = clock();
	select_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"选择排序未优化运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* 测试插入排序优化1 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// 记录时间 
	start = clock();
	select_sort1(test, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"选择排序优化1运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
}
