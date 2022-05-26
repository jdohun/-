#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

int arrSize = 1000;

int quickCount = 0;	// 빠른정렬의 정렬 swap 횟수
int mergeCount = 0; // 병합정렬의 비교 연산 횟수
int randQCount = 0; // 랜덤 피봇 빠른정렬의 정렬 swap 횟수

void show(int* arr, int idx_size); // 배열 출력

int* CreateArray(int n);	// n만큼의 랜덤 배열 생성

void bubbleSort(int* arr, int idx_size); // 교환정렬

int partition(int* S, int low, int high);	// 빠른정렬의 분할
void quickSort(int* S, int low, int high);	// 빠른정렬

void merge(int *S, int low, int mid, int high);	//	병합정렬의 conquer
void mergeSort(int *S, int low, int high);		// 병합정렬의 devide

int randomPivotPartition(int* S, int low, int high);	// 빠른정렬의 분할
void randomPivotQuick(int* S, int low, int high); // 랜덤피봇 빠른정렬

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

// 배열 출력
void show(int *arr, int idx_size) {
	for (int i = 0; i < idx_size; ++i) {
		printf("%4d ", arr[i]);
	}
	printf("\n\n");
}

// n만큼의 랜덤 배열 생성
int* CreateArray(int idx_size) {
	int* arr = new int[idx_size];
	
	// 순서대로 배열 초기화
	for (int i = 0; i < idx_size; ++i) {
		arr[i] = i;
	}

	// 배열 셔플
	srand(unsigned int(time(NULL)));
	int randIdx, tmp;
	int tmpSize = idx_size;
	for (int i = 0; i < idx_size; ++i) {
		randIdx = rand() % (tmpSize); // 배열 전체 길이 중 한 곳을 고른다.
		--tmpSize;
		tmp = arr[randIdx];			//  선택된 위치의 값을 임시 저장
		arr[randIdx] = arr[tmpSize]; // 선택된 위치에 마지막 배열 값을 넣고
		arr[tmpSize--] = tmp;		// 마지막 배열에 임시 저장한 값을 넣어서 교환한다.
		// 임시 사이즈를 감소시켜 이미 교환된 맨 마지막 배열을 제외 한다.
		if (tmpSize == 0) {
			break;
		}
	}

	return arr;
}

// 교환정렬
void bubbleSort(int *arr, int idx_size) {
	int temp;
	int bubbleCount = 0;

	// 2개일 경우 1번만 비교하면 됨, n개일 경우 n-1번만 비교하면 됨
	for (int i = 0; i < idx_size - 1; ++i) {	// 1회 반복마다 1개의 값 위치 확정
		for (int j = 0; j < idx_size - 1 - i; ++j) { // 확정된 숫자를 제외하고 비교
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


// 빠른정렬의 분할
int partition(int* S, int low, int high) {
	// 맨 앞의 원소를 pivot으로 설정
	int pivotitem = S[low];
	int tempPivot = low;    // pivotitem보다 큰 값을 지정하기 위한 임시 위치
	for (int i = low + 1; i <= high; i++) { // pivotitem 다음부터 비교
		if (S[i] < pivotitem) { // pivotitem 보다 작으면
			++tempPivot;    // 가장 먼저 검사한 pivotitem보다 큰 값과 swap
			int temp = S[i];
			S[i] = S[tempPivot];
			S[tempPivot] = temp;
			++quickCount;
		}
	}

	int pivotpoint = tempPivot; // 가장 마지막에 교환한 pivotitem보다 작은 값을 pivotitem으로 지정
	S[low] = S[pivotpoint]; // 기존의 pivotitem과 새로운 pivotitem을 교환하여
	S[pivotpoint] = pivotitem; //  기존의 pivotitem을 기준으로 왼쪽에 작은 값, 오른쪽에 큰 값을 위치시킴

	// 전체 배열의 pivotitem의 정렬된 위치를 반환
	return pivotpoint;
}

// 빠른정렬
void quickSort(int* S, int low, int high) {
	int pivotpoint; // index

	if (high > low) { // 성립하지 않으면 원소가 1개 == 원소가 1개일 때까지 쪼갠다
		pivotpoint = partition(S, low, high);
		quickSort(S, low, pivotpoint - 1); // pivotitem보다 작은 값들을 다시 정렬함 (재귀)
		quickSort(S, pivotpoint + 1, high);// pivotitem보다 큰 값들을 다시 정렬함 (재귀)
	}
}

// 병합정렬의 병합
void merge(int* S, int low, int mid, int high) {
	int* tempArr = new int[high + 1];

	int i = low;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= high) {	// 한 쪽의 배열이 다 소모될 때까지
		if (S[i] <= S[j]) {	// 왼쪽 배열에 있는 값이 작으면
			tempArr[k] = S[i]; // 임시 배열에 삽입
			++k;
			++i;
			++mergeCount;
		}
		else {	// 오른쪽 배열에 있는 값이 작으면
			tempArr[k] = S[j]; // 임시 배열에 삽입
			++k;
			++j;
			++mergeCount;
		}
	}

	while (i <= mid) { // 왼쪽 배열에 남은 값이 있으면
		tempArr[k] = S[i];
		++k;
		++i;
	}

	while (j <= high) { // 오른쪽 배열에 남은 값이 있으면
		tempArr[k] = S[j];
		++k;
		++j;
	}
	--k; // 배열의 길이를 넘어가는 것을 방지

	// 임시 배열에 저장한 값을 원래 배열에 복사
	while (k >= 0) {
		S[low + k] = tempArr[k];
		--k;
	}

	delete[] tempArr;
}

// 병합정렬
void mergeSort(int* S, int low, int high) {
	// exit condition
	if (low < high) { // 원소가 1개가 될 때까지
		int mid = (low + high) / 2;
		mergeSort(S, low, mid);
		mergeSort(S, mid + 1, high);

		merge(S, low, mid, high);
	}
}

// 랜덤 피봇 빠른정렬의 분할
int randomPivotPartition(int* S, int low, int high) {
	srand(time(NULL));

	// low 보다 같거나 크고 high보다 같거나 작은 인덱스
	int rng = low + rand() % (high - low + 1);
	int temp; // swap을 위한 임시 공간

	// 랜덤 pivot을 맨 뒤로 이동
	temp = S[rng];
	S[rng] = S[high];
	S[high] = temp;

	// 맨 뒤로 이동한 랜덤 pivot을 피봇으로 설정
	int pivot = S[high];
	int tempPivot = low;

	// 피봇 보다 작은 원소를 왼쪽으로 이동
	for (int i = low; i < high; ++i) {
		if (S[i] <= pivot) {
			temp = S[tempPivot];
			S[tempPivot] = S[i];
			S[i] = temp;
			++tempPivot;
			++randQCount;
		}
	}

	// pivot을 본인 위치로 이동
	temp = S[tempPivot];
	S[tempPivot] = S[high];
	S[high] = temp;

	return tempPivot;
}

// 랜덤 피봇 빠른정렬
void randomPivotQuick(int* S, int low, int high) {
	int pivotpoint; // index

	if (high > low) { // 성립하지 않으면 원소가 1개 == 원소가 1개일 때까지 쪼갠다
		pivotpoint = randomPivotPartition(S, low, high);
		quickSort(S, low, pivotpoint - 1); // pivotitem보다 작은 값들을 다시 정렬함 (재귀)
		quickSort(S, pivotpoint + 1, high);// pivotitem보다 큰 값들을 다시 정렬함 (재귀)
	}
}