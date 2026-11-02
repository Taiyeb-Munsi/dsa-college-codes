// Standard implementation of insertion sort

#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int size) {
	for (int i = 1; i < size; ++i) {
		int temp = arr[i];
		int j = i - 1;
		
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = temp;
	}
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
