#include <stdio.h>
#include <string.h>
#include <conio.h>

int charstrcmp(char *s, char *t);
int initstrcmp(char *s, char *t);
void swap(char **s, char **t);
void bubble_sort(void *str[],int num, int (*compare)(char *, char *));
void get_input(char **str, int num);
void print_out(char **str, int num);
void free_pointer(char **str, int num);


/*
    function charstrcmp(): compare two strings based on ASCII
*/
int charstrcmp(char *s, char *t)
{
    int i = 0;
    while (s[i] != '\0' || t[i] != '\0')
    {
        if (s[i] > t[i]) { return 1; }
        else if (s[i] < t[i]) { return -1; }
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
    if(strlen(s) > strlen(t)) { return sign; }
	if(strlen(s) < strlen(t)) { return -sign; } 
		
	while(s[i] != '\0' || t[i] != '\0')
	{
		if(s[i] > t[i]) { return sign; }
		else if(s[i] < t[i]) { return -sign; }
		i++;
	}
	return 0;
}

/*
	funciton swap(): swap two strings
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
void bubble_sort(void *str[], int num, int(*compare)(char *, char *))
{
    int i, j;
	for(i=0;i<=num-1;i++)
	{
		for(j=0;j<num-1;j++)
		{
			// if str[j-1] > sstr[j], should swap them
            if (compare((char *)str[j],(char *)str[j+1])>0)
            {
                swap(&str[j], &str[j+1]);
            }
		}
	}
		

}


/*
	function get_input(): get the input string array
*/ 
void get_input(char **str, int num)
{
	char *tmp;
	char tmp_str[100];
	int i, j;
	for(i=0; i<num; i++)
	{
		printf("\nPlease input the Number.%d string: \n", i+1);
		scanf("%s", &tmp_str);
		str[i] = (char *)malloc((strlen(tmp_str)+1)*sizeof(char));
		strcpy(str[i], tmp_str);
	}
}

/*
	function output_strings(): output the string or the result of sorted string
*/
void print_out(char **str, int num)
{	
	int i;
	for(i=0; i<num; i++)
	{
		printf("%s  ", str[i]);
	}
 } 

/*
	function free_point(): free used string pointers
*/
void free_pointer(char **str, int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		free(str[i]);		
	}

}


int main()
{
	char **str;
	int num, method;
	// Input the number of strings and strings 
	printf("\n=================== Input Number ====================\n");
	printf("\nNumber of string:\n");
	scanf("%i",&num);
	printf("\n=================== Input Strings ===================\n");
	str=(char **)malloc(num*sizeof(char *));
	get_input(str, num);
	
	// Print out original strings 
	printf("\nOriginal strings: \n");
	print_out(str, num);

	// Chose sort method
	printf("\n=================== Chose Method ====================\n");
	printf("\nThere are two methods you can chose to sort:\n");
	printf("\n1.ASCII;\n2.Integer Value\n");
	printf("\nPlease input the method number you wanted:\n");
	scanf("%d",&method);

	
	// Sorting and show the result
	printf("\n=================== Sorted Result ====================\n");	
	(method==1)?bubble_sort(str,num,charstrcmp):bubble_sort(str,num,initstrcmp);
	printf("\nResult of %s method:\n", (method==1)?"ASCII":"Integer Value");
	print_out(str,num);
	
	// Free pointers 
	free_pointer(str,num);
	free(str);
	
    return 1;
}

