/** @file merge_sort.cpp
 * @brief �鲢�������Ż��Ͳ���.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  �Ż���1������arr[mid] <= arr[mid+1]�����,������merge 2������С����, ʹ�ò�������
 * @history
 *	 July 18,2019 - v1.0.0 - zdz - ����-���ݹ�汾���޵����汾 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// ��������������δ�����ڴ�������䲻�ɹ����⣩ 
#define MAX 100000		// �������ֵ�������������50000�� ���������ڱ� 
#define MIN 50			// ������������Ԫ�ظ���С��MINʱʹ�ò������� 


/*********************************************************** 
* δ�Ż��鲢 
************************************************************/ 
/** 
 * @brief δ�Ż��鲢����ʹ�õĺϲ�����[��С����]��TODO �����ƣ� 
 * @param a:����������; start��mid:��һ���ź���Ĵ��ϲ�Ԫ�ط�Χ����Ӧ[mid+1, end]Ϊ�ڶ��� 
 * @return void	 
 * @note
 */
template<typename T>
void merge0(T *a, int start, int mid, int end) {
	// һ����Կ��ǿ���һ���µ������ܳ������飬Ȼ���������µ������ϣ�����ƻ�ԭ���� 
	// ���￪����������������ԭ���ݣ�ֱ����ԭ�����ϴ��������򣬲������ڱ�ʹ������
	
	int size_left = mid - start + 1;	// �������� 
	int size_right = end - mid;			// �Ұ������ 
	T* left = new T[size_left + 1];		// ��1��Ϊ�˶��һ���ڱ�λ 
	T* right = new T[size_right + 1];
	int i = 0, j = 0, k = 0;			// ѭ���������� 
	
	// ���� 
	for (i = 0; i < size_left; ++i) {
		left[i] = a[start+i];
	}
	for (i = 0; i < size_right; ++i) {
		right[i] = a[mid+1+i];
	}
	// ���ڱ�
	left[size_left] = MAX;
	right[size_right] = MAX; 
	
	// ���������µ�����
	for (k = start, i = 0, j = 0; k <= end; ++k) {
		if (left[i] <= right[j]) {
			// ��<=�� ��֤�ȶ���
			a[k] = left[i];
			++i; 
		}
		else {
			a[k] = right[j];
			++j;
		}
	}
	// �ͷŶ�̬�ڴ� 
	delete [] left;
	delete [] right; 
}
/** 
 * @brief δ�Ż��鲢����ʹ�õĵݹ麯��[��С����]��TODO �����ƣ� 
 * @param a:����������; start��end:���ϲ�Ԫ�ط�Χ	
 * @return void	 
 * @note
 *	-�ɸĽ���: 1.����������ȿ��Ƿ���Ҫ����2.����С����ʹ�ò�������
 */
template<typename T>
void merge_sort0_r(T *a, int start, int end) {
	// ���ݹ飬�ȿ��ǵݹ���ֹ����
	if (start >= end) {
		return ;
	} 
	
	int mid = start+((end-start)>>1);	// �м�Ԫ���±�
	// �������ݷֿ���������
	merge_sort0_r(a, start, mid);
	merge_sort0_r(a, mid+1, end);
	// �ϲ� 
	merge0(a, start, mid, end);
}
/** 
 * @brief δ�Ż��鲢���򣨵ݹ�棩[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ֱ���޸�ԭ 
 * @note
 *	-ʱ�临�Ӷȣ���� - O��nlog����� - O��nlogn����ƽ�� - O��nlogn��  ������������ݵ�������޹ء� 
 *	-�ռ临�Ӷȣ�O(n);  ����������ԭ�������㷨������ 
 *	-�ȶ��ԣ��ȶ���ȡ����merge�� 
 *	-�Ľ���: 1������arr[mid] <= arr[mid+1]�����,������merge 2������С����, ʹ�ò�������
 */
template<typename T> 
void merge_sort0(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	// �ݹ���й鲢����
	merge_sort0_r(a, 0, len-1); 
} 




/*********************************************************** 
* �鲢�Ż�1 
************************************************************/ 
/** 
 * @brief �鲢�����Ż�1ʹ�õĵݹ麯��[��С����]��TODO �����ƣ� 
 * @param a:����������; start��end:���ϲ�Ԫ�ط�Χ	
 * @return void	 
 * @note
 *	-�Ľ���: ����������ȿ��Ƿ���Ҫ����
 */
template<typename T>
void merge_sort1_r(T *a, int start, int end) {
	// ���ݹ飬�ȿ��ǵݹ���ֹ����
	if (start >= end) {
		return ;
	} 
	
	int mid = start+((end-start)>>1);	// �м�Ԫ���±�
	// �������ݷֿ���������
	merge_sort1_r(a, start, mid);
	merge_sort1_r(a, mid+1, end);
	// ��������ϲ�
	if (a[mid] > a[mid+1]) {
		merge0(a, start, mid, end);
	} 
}
/** 
 * @brief �鲢�����Ż�1���ݹ�棩[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ֱ���޸�ԭ 
 * @note
 *	-�Ľ��㣺merge֮ǰ���ж� 
 */
template<typename T> 
void merge_sort1(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	// �ݹ���й鲢����
	merge_sort1_r(a, 0, len-1); 
} 


/*********************************************************** 
* �鲢�Ż�2 
************************************************************/ 
template<typename T> 
void insert_sort(T *a, int start, int end) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || (end-start) <= 0) {
		return;
	}
	
	int cur = 0;	// ��ǰ�����������
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������   
	
	// ��δ����������б��� 
	for (int i = start; i <= end; ++i) {
		// ��¼��ǰ����ֵ
		cur = a[i]; 
		// �������������в��Ҳ���λ��
		for (j = i-1; j >= start; --j) {
			if (a[j] > cur) {
				// δ�ҵ�����λ�ã��������ƶ����������� 
				a[j+1] = a[j]; 
			}
			else {
				// �ȵ�ǰֵС�����ҵ�����λ�ã�����ѭ�� 
				break;	
			}
		}  
		a[j+1] = cur; 
	} 
} 
/** 
 * @brief �鲢�����Ż�2ʹ�õĵݹ麯��[��С����]��TODO �����ƣ� 
 * @param a:����������; start��end:���ϲ�Ԫ�ط�Χ	
 * @return void	 
 * @note
 *	-�Ľ���: �����ٵ�ʱ��ʹ�ò�������
 */
template<typename T>
void merge_sort2_r(T *a, int start, int end) {
	// ���ݹ飬�ȿ��ǵݹ���ֹ����
	if (start >= end) {
		return ;
	} 
	// ��������С��ֱ��ʹ�ò������� 
	if (end - start < MIN) {
		insert_sort(a, start, end);
	}
	else {
		int mid = start+((end-start)>>1);	// �м�Ԫ���±�
		// �������ݷֿ���������
		merge_sort2_r(a, start, mid);
		merge_sort2_r(a, mid+1, end);
		// ��������ϲ�
		if (a[mid] > a[mid+1]) {
			merge0(a, start, mid, end);
		} 
	}
}
/** 
 * @brief �鲢�����Ż�2���ݹ�棩[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ֱ���޸�ԭ 
 * @note
 *	-�Ľ���: �鲢֮ǰ�ж�+�����ٵ�ʱ��ʹ�ò�������
 */
template<typename T> 
void merge_sort2(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	// �ݹ���й鲢����
	merge_sort2_r(a, 0, len-1); 
} 



/******************************************* 
* �򵥲���
*******************************************/ 
int main(int argc, char** argv) {
	// ��ʱ�ñ��� 
	clock_t start,finish;
	double totaltime;
 
	int standard[MAXNUM];	// ��׼
	int test[MAXNUM];			// ���������� 
 
	/************************************** 
	* �����Դ����򣬸�����׼�� 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ��
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) {
		standard[i] = rand() % 50000 + 1;
	}

	int len = sizeof(standard)/sizeof(int);
	// ��ʱ 
	start = clock();
	sort(standard, standard+len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"algorithm������������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;	
	
	
	/************************************** 
	* ������ͨ�鲢����
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	merge_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"�鲢����δ�Ż�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* ���Թ鲢�����Ż�1 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// ��¼ʱ�� 
	start = clock();
	merge_sort1(test, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"�鲢�����Ż�1����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	/************************************** 
	* ���Թ鲢�����Ż�2 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// ��¼ʱ�� 
	start = clock();
	merge_sort2(test, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"�鲢�����Ż�2����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
}
