#include <stdio.h>
#include <string.h>

/*
	function print_out(): print out strings 
*/

void print_out(char *str[], int num)
{
	int i;
	for(i=0; i<num; i++)
	{
		printf("%s ", str[i]);
	}
}

/*
    function charstrcmp(): compare two strings based on ASCII
*/
int charstrcmp(char *s, char *t)
{
	int i=0;
	
	while(s[i]!='\0' || t[i]!='\0')
	{
		if(s[i] > t[i]) 
		{
			return 1;
		}
		else if(s[i] < t[i])
		{
			return -1;
		}
		i++;
	}
	return 0;
}


/*
	funciton swap(): swap two pointers
*/

void swap(char *a, char *b)
{
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

void HeapAdjust(char *arr[], int start, int end)
{
	int parent = start;
	int child = 2*parent + 1;
	
	while(child <= end)
	{
		// find the minimum item value
		if(child+1 <= end && charstrcmp(arr[child], arr[child+1]) == 1)
		{
			child++;
		}
		//charstrcmp(char *s, char *t)
	    // parent > child  
		if(charstrcmp(arr[parent], arr[child]) == 1)
		{
			swap(&arr[parent], &arr[child]);
			parent = child;
			child = 2*parent+1;
		}
		// parent < child 
		else if(charstrcmp(arr[parent], arr[child]) == -1)
		{
			return;
		}
	}
}

void HeapSort(char *arr[], int len)
{
	int i;
	// init
	for(i=len/2-1; i>=0; i--)
	{
		HeapAdjust(arr, i, len-1);
	}
	//printf("\nInit Heap: ");
	//print_out(arr, len);

	// swap and adjust
	for(i=len-1; i>0; --i)
	{
		swap(&arr[0], &arr[i]);
		HeapAdjust(arr, 0, i-1);
		//printf("\n");
		//print_out(arr, len);
	}
}




int main()
{
	// test strings 
	int num=50;
	char *str[50] = {"the", "of", "and", "a", "to", "in", "is", "you", "that", "it", "he", "was", "for", "on", "are", "as",
					"with", "his", "they", "I", "at", "be", "this", "have", "from","or", "one", "had", "by", "word",
					"but", "not", "what", "all","were", "we", "when", "your", "can", "said", "there", "use", "an", "each",
					"which", "she", "do", "how", "their", "if"};
	
	//int num=7;
	// to > the > of > is  > in > and > a
	//char *str[7] = {"the", "of", "and", "a", "to", "in", "is"};
	//char *str[7] = {"e", "f", "a", "c", "d", "b", "g"};
	printf("\nOriginal strings: \n");
	printf("\n");
	print_out(str, num);
	

	printf("\n");
	HeapSort(str,num);
	printf("\nSorted Result:\n");
	printf("\n");
	print_out(str,num);
	
	getch();

	return 0;
}











