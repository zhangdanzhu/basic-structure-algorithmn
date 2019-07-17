#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>
#include <vector> 

using namespace std;

#define MAXNUM 20000

/** 
* @brief 冒泡排序[从小到大]（TODO 不完善） 
*	-时间复杂度：最好 - O（n）；最坏 - O（n^2）；平均 - O（n^2） 
*	-空间复杂度：O(1);是原地排序算法 
*	-稳定性：稳定 
*	-优缺点: 缺点-数据交换比数据移动要复杂，需要3次赋值操作，影响效率 
*	-改进点或变体: 改进-1.增加是否有交换的标记，提前结束2.增加记录上一次交换位置3.双向冒泡		
*	-适用场景等：
* @param a:待排序数组; len:待排序元素	
* @return void	原地排序，直接修改 
*/
template<typename T> 
void bubble_sort0(T *a, int len) {
	// 首先检查数据的合法性（TODO 不完善）
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;	// 临时变量，用于进行数据交换，赋初值仅是习惯问题?防止随机初值？ 
	 
	// 两重循环，最普通的冒泡排序 
	// 确定排序趟数 
	for (int i = 0; i < len; ++i) {	// ++i不会多定义变量，相比i++省空间  
		// 确定单趟的比较次数 
		for (int j = 0; j < len - i - 1; ++j) {	 
			// 当前比后面的值大，则冒泡到后面去 
			if (a[j] > a[j+1]) {
				// 进行数据交换
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
			} 
		} 
	} 
} 

/** 
* @brief 冒泡排序优化1[从小到大]（TODO 不完善） 
*	-增加标记来记录一趟冒泡是否有交换,以提前结束冒泡 
*	-适用范围：仅适用于连片有序而整体无序的数据，但是对于前面大部分是无序而后边小半部分有序的数据(1，2，5，7，4，3，6，8，9，10)排序效率也不可观 
* @param a:待排序数组; len:待排序元素	
* @return void	原地排序，直接修改 
*/
template<typename T> 
void bubble_sort1(T *a, int len) {
	// 首先检查输入数据的合法性（TODO 不完善）
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;		// 临时变量，用于进行数据交换 
	int flag = 0;	// 标记变量，记录单趟排序是否有交换 
	 
	// 两重循环，最普通的冒泡排序 
	// 确定排序趟数 
	for (int i = 0; i < len; ++i) {	// ++i不会多定义变量，相比i++省空间  
		// 每趟排序之前置0
		flag = 0; 
		// 确定单趟的比较次数 
		for (int j = 0; j < len - i - 1; ++j) {	 
			// 当前比后面的值大，则冒泡到后面去 
			if (a[j] > a[j+1]) {
				// 进行数据交换
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				flag = 1;	// 记录交换 
			} 
		}
		// 如果标记为1，说明这趟排序未交换，已经排好序，可提前结束 
		if (flag == 0) {
			break; 
		} 
	} 
}

/** 
* @brief 冒泡排序优化2[从小到大]（TODO 不完善） 
*	-在1的基础上，记录上一趟冒泡最后一次交换的位置，本次冒泡只需到那结束即可 
*	-适用范围：对于前面大部分是无序而后边小半部分有序的数据可提高排序效率,其他的其实比优化1要慢，感觉是赋值太多了 
* @param a:待排序数组; len:待排序元素	
* @return void	原地排序，直接修改 
*/
template<typename T> 
void bubble_sort2(T *a, int len) {
	// 首先检查输入数据的合法性（TODO 不完善）
	if (a == NULL || len <= 1) {
		return;
	}
	
	T temp = 0;		// 临时变量，用于进行数据交换 
	int flag = 0;	// 标记变量，记录单趟排序是否有交换 
	int pos_temp = 0;		// 记录最后一次交换的位置 
	int pos_cur = len-1;	// 当前需要冒泡的截止位置 
	
	// 两重循环，最普通的冒泡排序 
	// 确定排序趟数 
	for (int i = 0; i < len; ++i) {	// ++i不会多定义变量，相比i++省空间  
		// 每趟排序之前置0
		flag = 0; 
		// 确定单趟的比较次数 
		for (int j = 0; j < pos_cur; ++j) {	 
			// 当前比后面的值大，则冒泡到后面去 
			if (a[j] > a[j+1]) {
				// 进行数据交换
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				pos_temp = j;	// 记录最后一次交换的位置 
				flag = 1;		// 记录交换 
			} 
		}
		// 如果标记为1，说明这趟排序未交换，已经排好序，可提前结束 
		if (flag == 0) {
			break; 
		}
		pos_cur = pos_temp;
	} 
}

/** 
* @brief 冒泡排序优化3[从小到大]（TODO 不完善） 
*	-在1、2的基础上，进行双向冒泡排序 
* @param a:待排序数组; len:待排序元素	
* @return void	原地排序，直接修改 
*/
template<typename T> 
void bubble_sort3(T *a, int len) {
	// 首先检查输入数据的合法性（TODO 不完善）
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;		// 临时变量，用于进行数据交换
	int flag = 0;	// 标记变量，记录单趟排序是否有交换
	int forward_pos_temp = 0;		// 记录前向最后一次交换的位置
	int forward_pos_cur = len-1;	// 当前需要冒泡的前向截止位置
	int reverse_pos_temp = 0;		// 记录前向最后一次交换的位置
	int reverse_pos_cur = 0;		// 当前需要冒泡的后向截止位置 
	int j = 0;		// 内层循环计数变量 
	
	// 确定排序趟数 
	for (int i = 0; i < len; ++i) {	// ++i不会多定义变量，相比i++省空间  
		// 每趟排序之前置0
		flag = 0; 
		
		// 正向冒泡寻找最大值
		for (j = 0; j < forward_pos_cur; ++j) {
			// 当前比后面的值大，则冒泡到后面去 
			if (a[j] > a[j+1]) {
				// 进行数据交换
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				forward_pos_temp = j;	// 记录最后一次交换的位置 
				flag = 1;		// 记录交换 
			} 
		} 
		// 如果标记为1，说明这趟排序未交换，已经排好序，可提前结束 
		if (flag == 0) {
			break; 
		}
		forward_pos_cur = forward_pos_temp;
		
		// 反向冒泡寻找最小值 
		for (j = forward_pos_cur; j > reverse_pos_cur; --j) {	 
			// 当前比前面的值小，则冒泡到前面去 
			if (a[j] < a[j-1]) {
				// 进行数据交换
				temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp; 
				reverse_pos_temp = j;	// 记录最后一次交换的位置 
				flag = 1;		// 记录交换 
			} 
		}
		// 如果标记为1，说明这趟排序未交换，已经排好序，可提前结束 
		if (flag == 0) {
			break; 
		}
		reverse_pos_cur = reverse_pos_temp;
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
	int a[MAXNUM];			// 测试用数组 
	
	vector<int> vector_standard;	// 标准
	vector<int> vector_a;			// 测试用vector 
 
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
	* 测试普通冒泡排序
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// 记录时间 
	start = clock();
	bubble_sort0(a, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"冒泡排序未优化运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* 测试冒泡排序优化1 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// 记录时间 
	start = clock();
	bubble_sort1(a, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"冒泡排序优化1运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* 测试冒泡排序优化2 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// 记录时间 
	start = clock();
	bubble_sort2(a, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"冒泡排序优化2运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* 测试冒泡排序优化3 
	**************************************/ 
	// 测试普通的int数组的排序，记录时间 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// 记录时间 
	start = clock();
	bubble_sort3(a, len);	// 调用排序 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"冒泡排序优化3运行时间为"<<totaltime<<"秒！"<<endl;
	// 检查排序后的结果 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
}


