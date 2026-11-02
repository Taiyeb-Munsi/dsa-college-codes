// Standard implementation of merge sort

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int right, int temp[]) {
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}
	
	while (i <= mid) temp[k++] = arr[i++];
	
	while (j <= right) temp[k++] = arr[j++];
	
	for (int i = left; i <= right; ++i) arr[i] = temp[i];
}

void mergeSort(int arr[], int left, int right, int temp[]) {
	if (left >= right) return;
	
	int mid = (left + right) / 2;
	
	mergeSort(arr, left, mid, temp); // Left side
	mergeSort(arr, mid + 1, right, temp); // Right side
	merge(arr, left, right, temp);
}

void sort(int arr[], int size) {
	int *temp = (int *)malloc(size * sizeof(int));

	mergeSort(arr, 0, size - 1, temp);
	free(temp);
}

int main() {
	int size;
	
	printf("Enter the size of the array : ");
	scanf("%d", &size);
	
	int *arr = (int *)malloc(size * sizeof(int));
	
	printf("Enter the array :\n");
	for(int i = 0; i < size; ++i) scanf("%d", &arr[i]);

	sort(arr, size);
	
	printf("\nSorted array :\n");
	for(int i = 0; i < size; ++i) printf("%d ", arr[i]);
	printf("\n");
	
	free(arr);
	return 0;
}
