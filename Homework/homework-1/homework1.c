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
    function charstrcmp: comparison two strings based on ASCII
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
    function initstrcmp: comparison two strings based on int value
*/
int initstrcmp(char *s, char *t)
{
    int i = 0, sign = 1;

    // if s or t is negative
    if (s[i] != '-' && t[i] == '-') { return 1; }
    if (s[i] == '-' && t[i] != '-') { return -1; }

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

void swap(char **s, char **t)
{
    char *tmp;
    tmp = *s;
    *s = *t;
    *t = tmp;
    tmp = NULL;
}

/*
    function bubble_sort: test program for string sorting
*/
void bubble_sort(void *str[], int num, int(*compare)(char *, char *))
{
    int i, j;
	for(i=0;i<=num-2;i++)
		for(j=num-1;j>=i+1;j--)
            // str[j-1] > sstr[j], should swap them
            if (compare((char *)str[j-1],(char *)str[j])>0)
            {
                swap(&str[j-1], &str[j]);
            }
}


/*
	function get_input: get the input string array
*/ 
void get_input(char **str, int num)
{
	char *tmp;
	char tmp_str[100];
	int i, j;
	for(i=0; i<num; i++)
	{
		printf("Please input the number.%d string: \n", i+1);
		scanf("%s", &tmp_str);
		str[i] = (char *)malloc((strlen(tmp_str)+1)*sizeof(char));
		strcpy(str[i], tmp_str);
	}
}

/*
	function output_strings: output the string or the result of sorting string
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
	function free_point: free used string pointers
*/
void free_pointer(char **str, int num)
{
	int i;
	for(i=0;i<num;i++)
		free(str[i]);
}


int main()
{
	char **str;
	int num, method;
	// Input strings
	printf("Number of string: ");
	scanf("%i",&num);
	str=(char **)malloc(num*sizeof(char *));
	get_input(str, num);
	
	// Orignal strings 
	printf("\nOrignal strings: \n");
	print_out(str, num);
	printf("              \n");
	
	// Sorting 
	printf("\nThere are two methods you can chose to sort this string array\n");
	printf("\n1.ASCII;\n2.Integer Value\n");
	printf("\nPlease input method you wanted:\n");
	scanf("%d",&method);
	
	(method==1)?bubble_sort((char **)str,num,charstrcmp):bubble_sort((char **)str,num,initstrcmp);
	printf("\nResult for Method %d:\n",(method==1)?1:2);
	print_out(str,num);
	
	free_pointer(str,num);
	free(str);
	
    return 1;
}

