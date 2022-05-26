#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

int arrSize = 1000;

int quickCount = 0;	// ���������� ���� swap Ƚ��
int mergeCount = 0; // ���������� �� ���� Ƚ��
int randQCount = 0; // ���� �Ǻ� ���������� ���� swap Ƚ��

void show(int* arr, int idx_size); // �迭 ���

int* CreateArray(int n);	// n��ŭ�� ���� �迭 ����

void bubbleSort(int* arr, int idx_size); // ��ȯ����

int partition(int* S, int low, int high);	// ���������� ����
void quickSort(int* S, int low, int high);	// ��������

void merge(int *S, int low, int mid, int high);	//	���������� conquer
void mergeSort(int *S, int low, int high);		// ���������� devide

int randomPivotPartition(int* S, int low, int high);	// ���������� ����
void randomPivotQuick(int* S, int low, int high); // �����Ǻ� ��������

int main() {
	int* arr1 = CreateArray(arrSize);
	int* arr2 = new int[arrSize];
	int* arr3 = new int[arrSize];
	int* arr4 = new int[arrSize];
	int* arr5 = new int[arrSize];
	show(arr1, arrSize);

	copy(arr1, arr1 + arrSize, arr2);
	copy(arr1, arr1 + arrSize, arr3);
	copy(arr1, arr1 + arrSize, arr4);
	copy(arr1, arr1 + arrSize, arr5);

	bubbleSort(arr2, arrSize);
	show(arr2, arrSize);

	quickSort(arr3, 0, arrSize - 1);
	printf("quickCount : %d\n", quickCount);
	show(arr3, arrSize);

	mergeSort(arr4, 0, arrSize - 1);
	printf("mergeCount : %d\n", mergeCount);
	show(arr4, arrSize);

	randomPivotQuick(arr5, 0, arrSize - 1);
	printf("randQCount : %d\n", randQCount);
	show(arr5, arrSize);

	delete[] arr5;
	delete[] arr4;
	delete[] arr3;
	delete[] arr2;
	delete[] arr1;
}

// �迭 ���
void show(int *arr, int idx_size) {
	for (int i = 0; i < idx_size; ++i) {
		printf("%4d ", arr[i]);
	}
	printf("\n\n");
}

// n��ŭ�� ���� �迭 ����
int* CreateArray(int idx_size) {
	int* arr = new int[idx_size];
	
	// ������� �迭 �ʱ�ȭ
	for (int i = 0; i < idx_size; ++i) {
		arr[i] = i;
	}

	// �迭 ����
	srand(unsigned int(time(NULL)));
	int randIdx, tmp;
	int tmpSize = idx_size;
	for (int i = 0; i < idx_size; ++i) {
		randIdx = rand() % (tmpSize); // �迭 ��ü ���� �� �� ���� ����.
		--tmpSize;
		tmp = arr[randIdx];			//  ���õ� ��ġ�� ���� �ӽ� ����
		arr[randIdx] = arr[tmpSize]; // ���õ� ��ġ�� ������ �迭 ���� �ְ�
		arr[tmpSize--] = tmp;		// ������ �迭�� �ӽ� ������ ���� �־ ��ȯ�Ѵ�.
		// �ӽ� ����� ���ҽ��� �̹� ��ȯ�� �� ������ �迭�� ���� �Ѵ�.
		if (tmpSize == 0) {
			break;
		}
	}

	return arr;
}

// ��ȯ����
void bubbleSort(int *arr, int idx_size) {
	int temp;
	int bubbleCount = 0;

	// 2���� ��� 1���� ���ϸ� ��, n���� ��� n-1���� ���ϸ� ��
	for (int i = 0; i < idx_size - 1; ++i) {	// 1ȸ �ݺ����� 1���� �� ��ġ Ȯ��
		for (int j = 0; j < idx_size - 1 - i; ++j) { // Ȯ���� ���ڸ� �����ϰ� ��
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				++bubbleCount;
			}
		}
	}
	printf("BubbleCount : %d\n", bubbleCount);
}


// ���������� ����
int partition(int* S, int low, int high) {
	// �� ���� ���Ҹ� pivot���� ����
	int pivotitem = S[low];
	int tempPivot = low;    // pivotitem���� ū ���� �����ϱ� ���� �ӽ� ��ġ
	for (int i = low + 1; i <= high; i++) { // pivotitem �������� ��
		if (S[i] < pivotitem) { // pivotitem ���� ������
			++tempPivot;    // ���� ���� �˻��� pivotitem���� ū ���� swap
			int temp = S[i];
			S[i] = S[tempPivot];
			S[tempPivot] = temp;
			++quickCount;
		}
	}

	int pivotpoint = tempPivot; // ���� �������� ��ȯ�� pivotitem���� ���� ���� pivotitem���� ����
	S[low] = S[pivotpoint]; // ������ pivotitem�� ���ο� pivotitem�� ��ȯ�Ͽ�
	S[pivotpoint] = pivotitem; //  ������ pivotitem�� �������� ���ʿ� ���� ��, �����ʿ� ū ���� ��ġ��Ŵ

	// ��ü �迭�� pivotitem�� ���ĵ� ��ġ�� ��ȯ
	return pivotpoint;
}

// ��������
void quickSort(int* S, int low, int high) {
	int pivotpoint; // index

	if (high > low) { // �������� ������ ���Ұ� 1�� == ���Ұ� 1���� ������ �ɰ���
		pivotpoint = partition(S, low, high);
		quickSort(S, low, pivotpoint - 1); // pivotitem���� ���� ������ �ٽ� ������ (���)
		quickSort(S, pivotpoint + 1, high);// pivotitem���� ū ������ �ٽ� ������ (���)
	}
}

// ���������� ����
void merge(int* S, int low, int mid, int high) {
	int* tempArr = new int[high + 1];

	int i = low;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= high) {	// �� ���� �迭�� �� �Ҹ�� ������
		if (S[i] <= S[j]) {	// ���� �迭�� �ִ� ���� ������
			tempArr[k] = S[i]; // �ӽ� �迭�� ����
			++k;
			++i;
			++mergeCount;
		}
		else {	// ������ �迭�� �ִ� ���� ������
			tempArr[k] = S[j]; // �ӽ� �迭�� ����
			++k;
			++j;
			++mergeCount;
		}
	}

	while (i <= mid) { // ���� �迭�� ���� ���� ������
		tempArr[k] = S[i];
		++k;
		++i;
	}

	while (j <= high) { // ������ �迭�� ���� ���� ������
		tempArr[k] = S[j];
		++k;
		++j;
	}
	--k; // �迭�� ���̸� �Ѿ�� ���� ����

	// �ӽ� �迭�� ������ ���� ���� �迭�� ����
	while (k >= 0) {
		S[low + k] = tempArr[k];
		--k;
	}

	delete[] tempArr;
}

// ��������
void mergeSort(int* S, int low, int high) {
	// exit condition
	if (low < high) { // ���Ұ� 1���� �� ������
		int mid = (low + high) / 2;
		mergeSort(S, low, mid);
		mergeSort(S, mid + 1, high);

		merge(S, low, mid, high);
	}
}

// ���� �Ǻ� ���������� ����
int randomPivotPartition(int* S, int low, int high) {
	srand(time(NULL));

	// low ���� ���ų� ũ�� high���� ���ų� ���� �ε���
	int rng = low + rand() % (high - low + 1);
	int temp; // swap�� ���� �ӽ� ����

	// ���� pivot�� �� �ڷ� �̵�
	temp = S[rng];
	S[rng] = S[high];
	S[high] = temp;

	// �� �ڷ� �̵��� ���� pivot�� �Ǻ����� ����
	int pivot = S[high];
	int tempPivot = low;

	// �Ǻ� ���� ���� ���Ҹ� �������� �̵�
	for (int i = low; i < high; ++i) {
		if (S[i] <= pivot) {
			temp = S[tempPivot];
			S[tempPivot] = S[i];
			S[i] = temp;
			++tempPivot;
			++randQCount;
		}
	}

	// pivot�� ���� ��ġ�� �̵�
	temp = S[tempPivot];
	S[tempPivot] = S[high];
	S[high] = temp;

	return tempPivot;
}

// ���� �Ǻ� ��������
void randomPivotQuick(int* S, int low, int high) {
	int pivotpoint; // index

	if (high > low) { // �������� ������ ���Ұ� 1�� == ���Ұ� 1���� ������ �ɰ���
		pivotpoint = randomPivotPartition(S, low, high);
		quickSort(S, low, pivotpoint - 1); // pivotitem���� ���� ������ �ٽ� ������ (���)
		quickSort(S, pivotpoint + 1, high);// pivotitem���� ū ������ �ٽ� ������ (���)
	}
}