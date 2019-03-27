#include <stdio.h>
#include <string.h>

/*
	function ptint_out(): print out the strings 
*/

void print_out(char *str[], int num)
{
	printf("{ ");
	int i;
	for(i=0; i<num; i++)
	{
		printf("%s ", str[i]);
	}
	printf("}");
}

/*
    function charstrcmp(): compare two strings based on ASCII
*/
int charstrcmp(char *s, char *t)//
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
    function initstrcmp(): compare two strings based on integer value
*/
int initstrcmp(char *s, char *t)
{
    int i = 0, sign = 1;

    // if s or t is negative
    if (s[i] != '-' && t[i] == '-') { return 1; }
    if (s[i] == '-' && t[i] != '-') { return -1; }
	
	// if s and t are all negative
    if (s[i] == '-' && t[i] == '-' ) { sign =  -1; }
    
    // compare based on the length of  strings
    if(strlen(s) > strlen(t)) { return sign; }
	if(strlen(s) < strlen(t)) { return -sign; } 
		
	// compare based on the value of strings
	while(s[i] != '\0' || t[i] != '\0')
	{
		if(s[i] > t[i]) { return sign; }
		else if(s[i] < t[i]) { return -sign; }
		i++;
	}
	return 0;
}


/*
	funciton swap(): swap two pointers
*/
void swap(char **s, char **t)
{
	char *tmp;
	tmp = *s;
	*s = *t;
	*t = tmp;
	tmp = NULL;
}

/*
    function bubble_sort(): bubble sort for strings
*/
void bubble_sort(void *str[], int num, int(*compare)(char *, char*))
{
	int i, j;
	for(i=0; i<num-1; i++)
	{
		for(j=0; j<num-1; j++)
		{	
		    // if str[j-1] > sstr[j], should swap them
			if(compare((char *)str[j], (char *)str[j+1]) > 0)
			{
				// swap the value of [j] and [j+1] 
				swap(&str[j], &str[j+1]);
			}
		}
	}
 } 

/*
	test program for the charstrcmp() and initstrcmp()
*/

int main()
{
	// test strings 
	int num=6;
	char *str[] = {"3", "27", "123", "5", "9", "1"};


	printf("\nOriginal strings: \n");
	print_out(str, num);
	
	// Choose sort method
	int method;
	printf("\n=================== Choose Method ====================\n");
	printf("\nThere are two methods you can choose to sort:\n");
	printf("\n1.ASCII;\n2.Integer Value\n");
	printf("\nPlease input the method number you wanted:\n");
	scanf("%d",&method);

	
	// Sorting and show the result
	printf("\n=================== Sorted Result ====================\n");	
	(method==1)?bubble_sort(str,num,charstrcmp):bubble_sort(str,num,initstrcmp);
	printf("\nResult of %s method:\n", (method==1)?"ASCII":"Integer Value");
	print_out(str,num);
	

	return 1;
}











