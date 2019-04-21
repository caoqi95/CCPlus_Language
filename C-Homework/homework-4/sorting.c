#include <stdio.h>
#include <stdlib.h>

void printArr(int arr[], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*************** Heap-based Sort *****************/

void swap(int *a, int *b)
{
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

void HeapAdjust(int arr[], int start, int end)
{
	int parent = start;
	int child = 2*parent + 1;
	
	while(child <= end)
	{
		if(child+1 <= end && arr[child] < arr[child+1])
		{
			child++;
		}
		
		if(arr[parent] > arr[child])
		{
			return;
		}
		else
		{
			swap(&arr[parent], &arr[child]);
			parent = child;
			child = 2*parent+1;
		}
	}
}

void HeapSort(int arr[], int len)
{
	int i;
	// init
	for(i=len/2-1; i>=0; i--)
	{
		HeapAdjust(arr, i, len-1);
	}
	
	printf("\nInit Max Heap: ");
	printArr(arr, len);
	// swap and adjust
	for(i=len-1; i>0; i--)
	{
		swap(&arr[0], &arr[i]);
		HeapAdjust(arr, 0, i-1);
		printf("\n");
		printArr(arr, len);
	}
	
}


/*************** Quick Sort *****************/

void QuickSort(int arr[], int left, int right, int len)
{
	int i = left;
	int j = right;
	int pivot = arr[i];
	
	if (i>j)
	{
		return;
	}
	
	while (i != j)
	{
		// find the value which is bigger than pivot
		while(arr[j] >= pivot && i<j)
		{
			j--;
		}

		// find the value which is less than pivot
		while(arr[i] <= pivot && i<j)
		{
			i++;
		}
		
		swap(&arr[i], &arr[j]);
		
		printf("\n");
		printArr(arr, len); 

	}
	arr[left] = arr[i];
	arr[i] = pivot;
	
	QuickSort(arr, left, i-1, len); // recursive
	QuickSort(arr, j+1, right, len);
}

int main()
{
	int arr[] = {5, 9, 3, 4, 2, 0, 7};
	int len = (int)sizeof(arr)/sizeof(*arr);
	int method;
	printf("\nOriginal         : ");
	printArr(arr, len);
	
	printf("\n+++++++++++++++ Method +++++++++++++++");
	printf("\n\t1. Heap-Based Sort\n\t2. Quick Sort"); 
	printf("\nPlease choose a method: ");
	scanf("%d", &method);
		/* heap-based sort */
	if(method == 1)
	{ 
		HeapSort(arr, len);
		printf("\nAfter Heap sort  : ");
		printArr(arr, len);
	} 
	else
	{ 
    	/* quick sort */
    	QuickSort(arr, 0, len-1, len);
		printf("\nAfter Quick sort : ");
		printArr(arr, len);
	} 
	return 0;
}
