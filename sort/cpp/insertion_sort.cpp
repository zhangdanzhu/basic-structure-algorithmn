/** @file insertion_sort.cpp
 * @brief 插入排序及其优化和测试.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  优化1：加入二分查找；优化2：希尔排序 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// 测试数据数量（未考虑内存溢出分配不成功问题） 

/** 
 * @brief 插入排序[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	原地排序，直接修改
 * @note
 *	-时间复杂度：最好 - O（n）；最坏 - O（n^2）；平均 - O（n^2） 
 *	-空间复杂度：O(1);是原地排序算法 
 *	-稳定性：稳定 
 *	-改进点或变体: 改进-1.使用二分查找找插入位置2.希尔排序		
 *	-适用场景等： 
 */
template<typename T> 
void insert_sort0(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int cur = 0;	// 当前待排序的数据
	int j = 0;		// 内层循环（移动数据）计数变量   
	
	// 对未排序区间进行遍历 
	for (int i = 1; i < len; ++i) {
		// 记录当前数据值
		cur = a[i]; 
		// 在已排序区间中查找插入位置
		for (j = i-1; j >= 0; --j) {
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
 * @brief 辅助插入排序优化1进行 二分查找[从小到大] （临时） 
 * @param a:查找数据; len:查找区间（a[0]-a[len]）,tar：待查找数据	
 * @return int：插入位置下标 
 * @note
 *	-辅助插入排序优化1，查找待插入位置 
 *	-不完善，不过无所谓，以后写道查找的时候再优化
 *  -查找的是第一个大于给定值的元素的下标（维持稳定性） 
 *	-待查数据区间已经排好序 
 */
template<typename T> 
int binary_search_simple(T *a, int len, T tar) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len < 1) {
		return -1;
	}
	
	// 特殊条件 
	if (a[0] > tar) {
		return 0;
	}
	else if (a[len-1] <= tar) {
		return len;
	} 
	
	int low = 0;	// 待查最左位置
	int high = len-1;	// 待查最右位置
	int mid = 0;	// 待查中间位置
	
	// 查找第一个大于等于给定值的元素
	while (low <= high) {
		// 待查中间位置【不使用（a+b）/2是防止溢出;位运算比除法效率高；位运算比加法优先级低】
		mid = low+((high-low)>>1);
		if (a[mid] > tar) {
			// 如果mid大于目标，就要看是否是需要的
			if (a[mid-1] <= tar) {
				return mid;
			}
			high = mid - 1;
		}
		else {
			low = mid + 1; 
		}	
	}
	return -1;	
}
/** 
 * @brief 插入排序优化1[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	原地排序，直接修改
 * @note
 *	-时间复杂度：最好 - O（n）；最坏 - O（n^2）；平均 - O（n^2） 
 *	-空间复杂度：O(1);是原地排序算法 
 *	-稳定性：稳定 
 *	-使用二分查找找插入位置
 */
template<typename T> 
void insert_sort1(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	T cur = 0;		// 当前待排序的数据 
	int index = -1;	// 二分查找到的插入位置
	int j = 0;		// 内层循环（移动数据）计数变量  
	
	// 对未排序区间进行遍历 
	for (int i = 1; i < len; ++i) {
		// 记录当前数据值
		cur = a[i]; 
		// 在已排序区间中查找插入位置
		index = binary_search_simple(a, i, cur);
		// 移动
		for (j = i; j > index; --j) {
			a[j] = a[j-1];	
		} 
		// 插入数据
		a[j] = cur; 
	}
}



/** 
 * @brief 插入排序优化2——希尔排序[从小到大]（TODO 不完善） 
 * @param a:待排序数组; len:待排序元素	
 * @return void	原地排序，直接修改
 * @note
 *	-希尔排序,引入分治的思想 
 *	-时间复杂度：最好 - O（n）；最坏 - O（logn）；平均 - O（logn） 
 *	-空间复杂度：O(1);是原地排序算法 
 *	-稳定性：！！！不稳定！！！！ 
 */
template<typename T> 
void insert_sort2(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）.
	if (a == NULL || len <= 1) {
		return;
	}
	
	T cur = 0;		// 当前待排序的数据 
	int index = -1;	// 二分查找到的插入位置
	int zu = 0;		// 内层循环（分组）计数变量    
	int i = 0;		// 内层循环（每组未排序空间）计数变量
	int j = 0;		// 内层循环（移动数据）计数变量  
	
	
	// 对gap进行遍历
	for (int gap = len/3+1; ; gap = gap/3+1) {
		// 分组 
		for (zu = 0; zu < gap; ++zu) 
			// 对每组的未排序区间进行遍历 
			for (i = gap+zu; i < len; i+=gap) {
				// 记录当前数据值
				cur = a[i]; 
				// 在已排序区间中查找插入位置
				for (j = i-gap; j >= 0+zu; j-=gap) {
					if (a[j] > cur) {
						// 未找到插入位置，则往后移动已排序数据 
						a[j+gap] = a[j]; 
					}
					else {
						// 比当前值小，则找到插入位置，结束循环 
						break;	
					}
				}  
				a[j+gap] = cur; 
			}
		
		// gap==1之后就可以结束了
		if (gap == 1) {
			break;
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
	insert_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"插入排序未优化运行时间为"<<totaltime<<"秒！"<<endl;
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
	insert_sort1(test, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"插入排序优化1运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* 测试插入排序优化2 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// 记录时间 
	start = clock();
	insert_sort2(test, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"插入排序优化2运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
}
