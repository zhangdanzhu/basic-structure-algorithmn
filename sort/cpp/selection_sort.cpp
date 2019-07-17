/** @file selection_sort.cpp
 * @brief ѡ���������Ż��Ͳ���.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  �Ż�1��ÿ������Сֵ�����ֵ��������������
 * @history
 *	 July 17,2019 - v1.0.0 - zdz - ���� 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// ��������������δ�����ڴ�������䲻�ɹ����⣩ 


/** 
 * @brief ѡ������[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ԭ������ֱ���޸�
 * @note
 *	-ʱ�临�Ӷȣ���� - O��n^2����� - O��n^2����ƽ�� - O��n^2�� 
 *	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
 *	-�ȶ��ԣ����������ȶ������� 
 *	-�Ľ���: �Ľ�-1.ÿ������Сֵ�����ֵ������ 
 */
template<typename T> 
void select_sort0(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int min = 0;	// ��ǰ���������������Сֵ���±� 
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������   
	T temp = 0;		// �������ݽ�������ʱ���� 
	
	// ��δ����������б��� 
	for (int i = 0; i < len; ++i) {
		min = i;
		// ��δ���������в�����Сֵ 
		for (j = i+1; j < len; ++j) {
			if (a[j] < a[min]) {
				// ������Сֵ�±� 
				min = j; 
			}
		}  
		// ���ݽ��� 
		temp = a[i];
		a[i] = a[min];
		a[min] = temp; 
	} 
} 


/** 
 * @brief ѡ�������Ż�1[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ԭ������ֱ���޸�
 * @note
 *	-ʱ�临�Ӷȣ���δ�Ż���ͬ�����Ǻ�ʱ��ԭ����һ������ 
 *	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
 *	-�ȶ��ԣ����������ȶ������� 
 *	-�Ľ���: ÿ������Сֵ�����ֵ������ 
 */
template<typename T> 
void select_sort1(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int min = 0;	// ��ǰ���������������Сֵ���±� 
	int max = 0; 	// ��ǰ���������������Сֵ���±� 
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������
	int k = len;   	// ��¼������ռ������ֵ�Ľ���λ 
	T temp = 0;		// �������ݽ�������ʱ���� 
	
	// ��δ����������б��� (ÿ�θ���ͷβ��λ��)
	for (int i = 0; i < k; ++i,--k) {
		min = i;
		max = i; 
		// ��δ���������в�����Сֵ����Сֵ 
		for (j = i+1; j < k; ++j) {
			if (a[j] < a[min]) {
				// ������Сֵ�±�
				min = j; 
			}
			if (a[j] > a[max]) {
				// �������ֵ�±� 
				max = j;
			} 
		} 
		if (min != i) {
			// ���ݽ���-��Сֵ 
			temp = a[i];
			a[i] = a[min];
			a[min] = temp; 
		} 
		if (max == i) {
			// ��ֹ֮ǰ���Ѿ�������
			max = min; 
		}
		if (max != k-1) {
			// ���ݽ���-���ֵ 
			temp = a[k-1];  
			a[k-1] = a[max];
			a[max] = temp;	
		} 
	} 
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
	* ������ͨ��������
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	select_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ѡ������δ�Ż�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* ���Բ��������Ż�1 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	 
	// ��¼ʱ�� 
	start = clock();
	select_sort1(test, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ѡ�������Ż�1����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
}
