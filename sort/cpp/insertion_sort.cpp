/** @file insertion_sort.cpp
 * @brief �����������Ż��Ͳ���.
 * @author zdz 
 * @date July 17,2019 
 * @version 1.0.0
 * @note
 *  �Ż�1��������ֲ��ң��Ż�2��ϣ������ 
 */
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>

using namespace std;

#define MAXNUM 20000	// ��������������δ�����ڴ�������䲻�ɹ����⣩ 

/** 
 * @brief ��������[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ԭ������ֱ���޸�
 * @note
 *	-ʱ�临�Ӷȣ���� - O��n����� - O��n^2����ƽ�� - O��n^2�� 
 *	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
 *	-�ȶ��ԣ��ȶ� 
 *	-�Ľ�������: �Ľ�-1.ʹ�ö��ֲ����Ҳ���λ��2.ϣ������		
 *	-���ó����ȣ� 
 */
template<typename T> 
void insert_sort0(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	int cur = 0;	// ��ǰ�����������
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������   
	
	// ��δ����������б��� 
	for (int i = 1; i < len; ++i) {
		// ��¼��ǰ����ֵ
		cur = a[i]; 
		// �������������в��Ҳ���λ��
		for (j = i-1; j >= 0; --j) {
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
 * @brief �������������Ż�1���� ���ֲ���[��С����] ����ʱ�� 
 * @param a:��������; len:�������䣨a[0]-a[len]��,tar������������	
 * @return int������λ���±� 
 * @note
 *	-�������������Ż�1�����Ҵ�����λ�� 
 *	-�����ƣ���������ν���Ժ�д�����ҵ�ʱ�����Ż�
 *  -���ҵ��ǵ�һ�����ڸ���ֵ��Ԫ�ص��±꣨ά���ȶ��ԣ� 
 *	-�������������Ѿ��ź��� 
 */
template<typename T> 
int binary_search_simple(T *a, int len, T tar) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len < 1) {
		return -1;
	}
	
	// �������� 
	if (a[0] > tar) {
		return 0;
	}
	else if (a[len-1] <= tar) {
		return len;
	} 
	
	int low = 0;	// ��������λ��
	int high = len-1;	// ��������λ��
	int mid = 0;	// �����м�λ��
	
	// ���ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
	while (low <= high) {
		// �����м�λ�á���ʹ�ã�a+b��/2�Ƿ�ֹ���;λ����ȳ���Ч�ʸߣ�λ����ȼӷ����ȼ��͡�
		mid = low+((high-low)>>1);
		if (a[mid] > tar) {
			// ���mid����Ŀ�꣬��Ҫ���Ƿ�����Ҫ��
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
 * @brief ���������Ż�1[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ԭ������ֱ���޸�
 * @note
 *	-ʱ�临�Ӷȣ���� - O��n����� - O��n^2����ƽ�� - O��n^2�� 
 *	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
 *	-�ȶ��ԣ��ȶ� 
 *	-ʹ�ö��ֲ����Ҳ���λ��
 */
template<typename T> 
void insert_sort1(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	T cur = 0;		// ��ǰ����������� 
	int index = -1;	// ���ֲ��ҵ��Ĳ���λ��
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������  
	
	// ��δ����������б��� 
	for (int i = 1; i < len; ++i) {
		// ��¼��ǰ����ֵ
		cur = a[i]; 
		// �������������в��Ҳ���λ��
		index = binary_search_simple(a, i, cur);
		// �ƶ�
		for (j = i; j > index; --j) {
			a[j] = a[j-1];	
		} 
		// ��������
		a[j] = cur; 
	}
}



/** 
 * @brief ���������Ż�2����ϣ������[��С����]��TODO �����ƣ� 
 * @param a:����������; len:������Ԫ��	
 * @return void	ԭ������ֱ���޸�
 * @note
 *	-ϣ������,������ε�˼�� 
 *	-ʱ�临�Ӷȣ���� - O��n����� - O��logn����ƽ�� - O��logn�� 
 *	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
 *	-�ȶ��ԣ����������ȶ��������� 
 */
template<typename T> 
void insert_sort2(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�.
	if (a == NULL || len <= 1) {
		return;
	}
	
	T cur = 0;		// ��ǰ����������� 
	int index = -1;	// ���ֲ��ҵ��Ĳ���λ��
	int zu = 0;		// �ڲ�ѭ�������飩��������    
	int i = 0;		// �ڲ�ѭ����ÿ��δ����ռ䣩��������
	int j = 0;		// �ڲ�ѭ�����ƶ����ݣ���������  
	
	
	// ��gap���б���
	for (int gap = len/3+1; ; gap = gap/3+1) {
		// ���� 
		for (zu = 0; zu < gap; ++zu) 
			// ��ÿ���δ����������б��� 
			for (i = gap+zu; i < len; i+=gap) {
				// ��¼��ǰ����ֵ
				cur = a[i]; 
				// �������������в��Ҳ���λ��
				for (j = i-gap; j >= 0+zu; j-=gap) {
					if (a[j] > cur) {
						// δ�ҵ�����λ�ã��������ƶ����������� 
						a[j+gap] = a[j]; 
					}
					else {
						// �ȵ�ǰֵС�����ҵ�����λ�ã�����ѭ�� 
						break;	
					}
				}  
				a[j+gap] = cur; 
			}
		
		// gap==1֮��Ϳ��Խ�����
		if (gap == 1) {
			break;
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
	insert_sort0(test, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"��������δ�Ż�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
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
	insert_sort1(test, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"���������Ż�1����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
	
	
	/************************************** 
	* ���Բ��������Ż�2 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		test[i] = rand() % 50000 + 1;
	}
	len = sizeof(test)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	insert_sort2(test, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"���������Ż�2����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == test[i]);
	}
}
