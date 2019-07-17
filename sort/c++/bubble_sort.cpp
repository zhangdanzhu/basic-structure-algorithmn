#include <iostream>
#include <ctime>
#include <algorithm> 
#include <cassert>
#include <vector> 

using namespace std;

#define MAXNUM 20000

/** 
* @brief ð������[��С����]��TODO �����ƣ� 
*	-ʱ�临�Ӷȣ���� - O��n����� - O��n^2����ƽ�� - O��n^2�� 
*	-�ռ临�Ӷȣ�O(1);��ԭ�������㷨 
*	-�ȶ��ԣ��ȶ� 
*	-��ȱ��: ȱ��-���ݽ����������ƶ�Ҫ���ӣ���Ҫ3�θ�ֵ������Ӱ��Ч�� 
*	-�Ľ�������: �Ľ�-1.�����Ƿ��н����ı�ǣ���ǰ����2.���Ӽ�¼��һ�ν���λ��3.˫��ð��		
*	-���ó����ȣ�
* @param a:����������; len:������Ԫ��	
* @return void	ԭ������ֱ���޸� 
*/
template<typename T> 
void bubble_sort0(T *a, int len) {
	// ���ȼ�����ݵĺϷ��ԣ�TODO �����ƣ�
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;	// ��ʱ���������ڽ������ݽ���������ֵ����ϰ������?��ֹ�����ֵ�� 
	 
	// ����ѭ��������ͨ��ð������ 
	// ȷ���������� 
	for (int i = 0; i < len; ++i) {	// ++i����ඨ����������i++ʡ�ռ�  
		// ȷ�����˵ıȽϴ��� 
		for (int j = 0; j < len - i - 1; ++j) {	 
			// ��ǰ�Ⱥ����ֵ����ð�ݵ�����ȥ 
			if (a[j] > a[j+1]) {
				// �������ݽ���
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
			} 
		} 
	} 
} 

/** 
* @brief ð�������Ż�1[��С����]��TODO �����ƣ� 
*	-���ӱ������¼һ��ð���Ƿ��н���,����ǰ����ð�� 
*	-���÷�Χ������������Ƭ�����������������ݣ����Ƕ���ǰ��󲿷�����������С�벿�����������(1��2��5��7��4��3��6��8��9��10)����Ч��Ҳ���ɹ� 
* @param a:����������; len:������Ԫ��	
* @return void	ԭ������ֱ���޸� 
*/
template<typename T> 
void bubble_sort1(T *a, int len) {
	// ���ȼ���������ݵĺϷ��ԣ�TODO �����ƣ�
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;		// ��ʱ���������ڽ������ݽ��� 
	int flag = 0;	// ��Ǳ�������¼���������Ƿ��н��� 
	 
	// ����ѭ��������ͨ��ð������ 
	// ȷ���������� 
	for (int i = 0; i < len; ++i) {	// ++i����ඨ����������i++ʡ�ռ�  
		// ÿ������֮ǰ��0
		flag = 0; 
		// ȷ�����˵ıȽϴ��� 
		for (int j = 0; j < len - i - 1; ++j) {	 
			// ��ǰ�Ⱥ����ֵ����ð�ݵ�����ȥ 
			if (a[j] > a[j+1]) {
				// �������ݽ���
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				flag = 1;	// ��¼���� 
			} 
		}
		// ������Ϊ1��˵����������δ�������Ѿ��ź��򣬿���ǰ���� 
		if (flag == 0) {
			break; 
		} 
	} 
}

/** 
* @brief ð�������Ż�2[��С����]��TODO �����ƣ� 
*	-��1�Ļ����ϣ���¼��һ��ð�����һ�ν�����λ�ã�����ð��ֻ�赽�ǽ������� 
*	-���÷�Χ������ǰ��󲿷�����������С�벿����������ݿ��������Ч��,��������ʵ���Ż�1Ҫ�����о��Ǹ�ֵ̫���� 
* @param a:����������; len:������Ԫ��	
* @return void	ԭ������ֱ���޸� 
*/
template<typename T> 
void bubble_sort2(T *a, int len) {
	// ���ȼ���������ݵĺϷ��ԣ�TODO �����ƣ�
	if (a == NULL || len <= 1) {
		return;
	}
	
	T temp = 0;		// ��ʱ���������ڽ������ݽ��� 
	int flag = 0;	// ��Ǳ�������¼���������Ƿ��н��� 
	int pos_temp = 0;		// ��¼���һ�ν�����λ�� 
	int pos_cur = len-1;	// ��ǰ��Ҫð�ݵĽ�ֹλ�� 
	
	// ����ѭ��������ͨ��ð������ 
	// ȷ���������� 
	for (int i = 0; i < len; ++i) {	// ++i����ඨ����������i++ʡ�ռ�  
		// ÿ������֮ǰ��0
		flag = 0; 
		// ȷ�����˵ıȽϴ��� 
		for (int j = 0; j < pos_cur; ++j) {	 
			// ��ǰ�Ⱥ����ֵ����ð�ݵ�����ȥ 
			if (a[j] > a[j+1]) {
				// �������ݽ���
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				pos_temp = j;	// ��¼���һ�ν�����λ�� 
				flag = 1;		// ��¼���� 
			} 
		}
		// ������Ϊ1��˵����������δ�������Ѿ��ź��򣬿���ǰ���� 
		if (flag == 0) {
			break; 
		}
		pos_cur = pos_temp;
	} 
}

/** 
* @brief ð�������Ż�3[��С����]��TODO �����ƣ� 
*	-��1��2�Ļ����ϣ�����˫��ð������ 
* @param a:����������; len:������Ԫ��	
* @return void	ԭ������ֱ���޸� 
*/
template<typename T> 
void bubble_sort3(T *a, int len) {
	// ���ȼ���������ݵĺϷ��ԣ�TODO �����ƣ�
	if (a == NULL || len <= 1) {
		return;
	}
	 
	T temp = 0;		// ��ʱ���������ڽ������ݽ���
	int flag = 0;	// ��Ǳ�������¼���������Ƿ��н���
	int forward_pos_temp = 0;		// ��¼ǰ�����һ�ν�����λ��
	int forward_pos_cur = len-1;	// ��ǰ��Ҫð�ݵ�ǰ���ֹλ��
	int reverse_pos_temp = 0;		// ��¼ǰ�����һ�ν�����λ��
	int reverse_pos_cur = 0;		// ��ǰ��Ҫð�ݵĺ����ֹλ�� 
	int j = 0;		// �ڲ�ѭ���������� 
	
	// ȷ���������� 
	for (int i = 0; i < len; ++i) {	// ++i����ඨ����������i++ʡ�ռ�  
		// ÿ������֮ǰ��0
		flag = 0; 
		
		// ����ð��Ѱ�����ֵ
		for (j = 0; j < forward_pos_cur; ++j) {
			// ��ǰ�Ⱥ����ֵ����ð�ݵ�����ȥ 
			if (a[j] > a[j+1]) {
				// �������ݽ���
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp; 
				forward_pos_temp = j;	// ��¼���һ�ν�����λ�� 
				flag = 1;		// ��¼���� 
			} 
		} 
		// ������Ϊ1��˵����������δ�������Ѿ��ź��򣬿���ǰ���� 
		if (flag == 0) {
			break; 
		}
		forward_pos_cur = forward_pos_temp;
		
		// ����ð��Ѱ����Сֵ 
		for (j = forward_pos_cur; j > reverse_pos_cur; --j) {	 
			// ��ǰ��ǰ���ֵС����ð�ݵ�ǰ��ȥ 
			if (a[j] < a[j-1]) {
				// �������ݽ���
				temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp; 
				reverse_pos_temp = j;	// ��¼���һ�ν�����λ�� 
				flag = 1;		// ��¼���� 
			} 
		}
		// ������Ϊ1��˵����������δ�������Ѿ��ź��򣬿���ǰ���� 
		if (flag == 0) {
			break; 
		}
		reverse_pos_cur = reverse_pos_temp;
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
	int a[MAXNUM];			// ���������� 
	
	vector<int> vector_standard;	// ��׼
	vector<int> vector_a;			// ������vector 
 
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
	* ������ͨð������
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	bubble_sort0(a, len);
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ð������δ�Ż�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* ����ð�������Ż�1 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	bubble_sort1(a, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ð�������Ż�1����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* ����ð�������Ż�2 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	bubble_sort2(a, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ð�������Ż�2����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
	
	
	/************************************** 
	* ����ð�������Ż�3 
	**************************************/ 
	// ������ͨ��int��������򣬼�¼ʱ�� 
	srand(0);
	for(int i = 0; i < MAXNUM; ++i) { 
		a[i] = rand() % 50000 + 1;
	}
	len = sizeof(a)/sizeof(int);
	// ��¼ʱ�� 
	start = clock();
	bubble_sort3(a, len);	// �������� 
	finish = clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"ð�������Ż�3����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
	// ��������Ľ�� 
	for (int i = 0;i < len; ++i) {
		assert(standard[i] == a[i]);
	}
}


