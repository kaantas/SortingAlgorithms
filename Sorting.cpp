#include <stdio.h>
#include <stdlib.h>
#include "Sorting.h"

void swap(int *a, int *b){
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

/****************************************************
 * Uses bubble sort to sort A[0..N-1]
 ****************************************************/
void BubbleSort(int A[], int N){
	int temp;
	for (int i = 0; i<N; i++) {
		for (int j = 1; j<(N - i); j++) {
			if (A[j - 1] > A[j]){
				//SWAP
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
			}
		}
	}
} //end-BubbleSort

/****************************************************
 * Uses selection sort to sort A[0..N-1]
 ****************************************************/

void SelectionSort(int A[], int N){
	for (int i = 0; i<N; i++) {
		int minIndex = i;
		for (int j = i + 1; j<N; j++) {
			if (A[j] < A[minIndex]) minIndex = j;
		}
		if (i != minIndex) swap(&A[i], &A[minIndex]);
	}
} //end-SelectionSort

/****************************************************
 * Uses insertion sort to sort A[0..N-1]
 ****************************************************/

void InsertionSort(int A[], int N){
	int temp,j;
	for (int i = 1; i < N; i++) {
		temp = A[i];
		for (j = i; j > 0 && A[j - 1] > temp; j--){
			A[j] = A[j - 1];
		}
		A[j] = temp;
	}
} //end-InsertionSort

void Merge(int *A, int N, int middle) {
	int i, j, k, z;
	int *B = (int*)malloc(N * sizeof(int));

	for (i = 0, j = middle, k = 0; k < N; k++) {
		if (j == N) B[k] = A[i++]; 
		else if (i == middle || A[j]<A[i]) B[k] = A[j++];
		else B[k] = A[i++];
	}

	for (z = 0; z < N; z++) A[z] = B[z];
}
/****************************************************
 * Uses mergesort to sort A[0..N-1]
 ****************************************************/
void MergeSort(int A[], int N){
	if (N < 2) return;
	int middle = N / 2;
	
	MergeSort(A, middle);
	MergeSort(A + middle, N - middle);
	Merge(A, N, middle);
} //end-MergeSort

/****************************************************
 * Uses quicksort sort to sort A[0..N-1]
 ****************************************************/
void QuickSort(int A[], int N){
	int pivot;
	if (N < 2) return;
	
	pivot = A[N / 2];

	int i = 0;
	int j = N - 1;
	//PARTITION 
	while (1){
		while (A[i] < pivot) i++;
		while (pivot < A[j]) j--;
		if (i >= j) break;

		swap(&A[i], &A[j]);
		i++; j--;
	}
	
	QuickSort(A, i);
	QuickSort(A + i, N - i);
} //end-QuickSort

void PushDown(int *A, int N, int i) {
	int j, k, max, x;
	while (1) {	
		//find Max
		j = 2*i + 1;
		k = 2*i + 2;
		max = i;
		if (j < N && A[j] > A[max]) max = j;
		if (k < N && A[k] > A[max]) max = k;	
	    x = max;

		//push Down
		if (x == i) break;
		swap(&A[i], &A[x]);
		i = x;
	}
}
/****************************************************
 * Uses heapsort to sort A[0..N]
 * NOTICE: The first element is in A[0] not in A[1]
 ****************************************************/
void HeapSort(int A[], int N){
	for (int i = (N - 2) / 2; i >= 0; i--) {
		PushDown(A, N, i);
	}
	for (int j = 0; j < N; j++) {
		swap(&A[N - j - 1], &A[0]);
		PushDown(A, N - j - 1, 0);
	}
} //end-HeapSort

/****************************************************
 * Uses radixsort to sort A[0..N]
 ****************************************************/
void RadixSort(int A[], int N){
	int i,max;
	int digit = 1; //significant digit based on 10
	int *temp = (int*)malloc(N*sizeof(int)); //temp array is the semi sorted array

	int maxNum = -1;
	for (i = 0; i < N; i++)
		if (A[i] > maxNum) maxNum = A[i];
	
	max = maxNum; //max Number	
	while (1){ 
		int b[10] = {0}; //bucket=10sizeArray
		// num of digits in each bucket
		for (i = 0; i < N; i++) b[(A[i] / digit) % 10]++;

		// num of buckets like counting sort
		for (i = 1; i < 10; i++) b[i] += b[i - 1];

		//set buckets to temp array
		for (i = N - 1; i >= 0; i--) temp[--b[(A[i] / digit) % 10]] = A[i];

		for (i = 0; i < N; i++) A[i] = temp[i];
		if (max / digit <= 0) break; // if reach the largest digit, break
		digit *= 10; //next digit
	}
} //end-RadixSort

/****************************************************
 * Uses countingsort to sort A[0..N]
 ****************************************************/
void CountingSort(int A[], int N){	
	//find min and max values
	int min, max, a;
	min = max = A[0];
	for (int a = 1; a < N; a++) {
		if (A[a] < min) min = A[a];
		if (A[a] > max) max = A[a];
	}

	int i, j, z;
	int range = max - min + 1; //Allocate
	int *C = (int*)malloc(range * sizeof(*A)); // C = Count array
	for (i = 0; i < range; i++) C[i] = 0; //Set values in C to 0

	//How many numbers are there in array?
	for (i = 0; i < N; i++) C[A[i] - min]++;
	for (i = min, z = 0; i <= max; i++) {
		for (j = 0; j < C[i - min]; j++) {
			A[z++] = i;
		}
	}
} //end-CountingSort