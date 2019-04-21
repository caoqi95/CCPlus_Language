#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "my_math.h"

#define Pi 3.14159265358979323846
#define DEC (Pi/180)

using std::cout;
using std::endl; 

/****************** Define Stack ************************/


// Define pNode as pointer of data type struct Node
typedef struct Node *pNode;

// Define Stack as pointer of data type struct Lklist
typedef struct LkList *Stack;

struct Node
{
	char* data;
	struct Node *pNext;
};

struct LkList
{
	pNode Head;
	pNode Tail;
};

// Check the Stack is empty or not 
int isEmpty(Stack inputStack)
{
	return inputStack->Head == NULL;
}


// Push data to the Stack
void pushData(Stack inputStack,char* data)
{
	
	if(isEmpty(inputStack))
	{
		
		inputStack->Head=(pNode)malloc(sizeof(struct Node));
		inputStack->Head->data=(char *)malloc(sizeof(char)*(strlen(data)+1));
		strcpy(inputStack->Head->data,data);
		inputStack->Tail=inputStack->Head;
		inputStack->Head->pNext=NULL;
	}
	else
	{
		
		pNode newNode=(pNode)malloc(sizeof(struct Node));
		newNode->data=(char *)malloc(sizeof(char)*(strlen(data)+1));
		strcpy(newNode->data,data);
		newNode->pNext=NULL;
		inputStack->Tail->pNext=newNode;
		inputStack->Tail=newNode;
		newNode=NULL;
	
	}
}

// Pop data from Stack
char* popData(Stack inputStack)
{
	char* getdata;
	if(!isEmpty(inputStack)) 
	{
		
		pNode freeNode=inputStack->Tail; 
		pNode tmpNode=inputStack->Head; 
		getdata=inputStack->Tail->data; 
		// if there is only one item in the list, remove it
		if(inputStack->Tail==inputStack->Head)
		{	
			inputStack->Tail=NULL;
			inputStack->Head=NULL;
			free(freeNode);
		}
		else 
		{
			// go to find the second to last node in the list
			while(tmpNode->pNext!=inputStack->Tail)
			{
				tmpNode=tmpNode->pNext;
			}
			
			inputStack->Tail=tmpNode; // let the tmpNode become the last node 
			inputStack->Tail->pNext=NULL;
			tmpNode=NULL;
			free(freeNode); // remove the original tail node 
		}		
	}
	return getdata;
}

void printStack(Stack inputStack)
{
	pNode ptmp=inputStack->Head;
	while(ptmp!=NULL)
	{
		printf("%s ",ptmp->data);
		ptmp=ptmp->pNext;
	}
}

/******************* PreProcess Input *********************/

int CheckIsNumber(char c)
{
	char numList[12] = "0123456789.";
	if  (strchr(numList,c)!= NULL )
		return 1;
	return 0;
}

void InsertZero(char s[], int Index, char c)
{ 
	int i;
	// Index is the last position
	if (Index == strlen (s))
	{
		s[Index] = c;
		return;
	}	
	// Index is in the middle
	for (i=strlen(s)+1;i>Index; i--)
	{
		s[i] = s[i-1];
	}
	s[Index] = c; 
} 

void PreProcessInput(char s[])
{
	int i;
	
	// Negative number at the beginning, like: -3+5 ---> 0-3+5 
	if (s[0] == '+' || s[0] == '-')
	{
		InsertZero(s, 0, '0');
	}
	
	// Negative number in the middle, like: 2*(-3) ---> 2*(0-3) 
	for(i=1; i<strlen(s); i++)
	{
		
		if(s[i-1] == '('&& (s[i] == '-' || s[i] == '+'))
		{
			InsertZero(s, i, '0');
		}
	 } 
}


/************************* Input Data **************************/

int checkData(char cData)
{
	if(cData=='(' || cData==')' || cData=='*' || cData=='/' || cData=='+' || cData=='-' || cData=='^' || cData=='%')
		return 0;
	if(cData=='e' || cData=='s' ||  cData=='c' ||  cData=='t')
		return 0;
	return 1;
}


void inputData(char inputString[], Stack InfixStack)
{
	int i;
	for(i=0;i<strlen(inputString);i++)
	{	
		// Confirm whether the entered character is a number or '.' 
		if(checkData(inputString[i])) 
		{
			char ctmp[100]; 
			int j;
			int contr = 0;
			for(j=i;j<strlen(inputString);j++)
			{
				if(checkData(inputString[j]))
					ctmp[contr++]=inputString[j];
				else
					break;
			 } 

			ctmp[contr]='\0';
			i=j-1;
			pushData(InfixStack,ctmp); // add the value 
		}
		// Other operations 
		else 
		{
			char ctmp[2];
			ctmp[0]=inputString[i];
			ctmp[1]='\0';
			pushData(InfixStack,ctmp); // add the vallue
		}
	}
}


/********************* Infix to Postfix *************************/

// Confirm the priority of the symbol
int checkOrder(char Op)
{
	
	if(Op=='^' || Op=='e' || Op == 's' || Op == 'c' || Op == 't')
		return 4;
	else if(Op=='*' || Op=='/' || Op=='%')
		return 3;
	else if(Op=='+' || Op=='-')
		return 2;
	else
		return 1;
}

// Convert Infix to Postfix
Stack convertInfixtoPostfix(Stack inputInfixSt)
{
	char *ctmp;
	Stack PostfixSt=(Stack)malloc(sizeof(struct LkList)); // Postfix stack
	Stack OpSt=(Stack)malloc(sizeof(struct LkList)); // Opt stack
	pNode temp=inputInfixSt->Head; 
	PostfixSt->Head=NULL;	
	OpSt->Head=NULL;
	
	while(temp!=NULL)
	{
		char *cData = temp->data;
		
		if(checkData(cData[0])){
			pushData(PostfixSt, cData); //if temp.data is a number, then put it into Postfix
		}
		else
		{
			// check special case ')'
			if (cData[0] == ')')
			{
				while(OpSt->Tail->data[0] != '(')
				{
					pushData(PostfixSt, popData(OpSt));
				}
				// pop the '(' out 
				ctmp = popData(OpSt);
			 } 
			else
			{
				if(isEmpty(OpSt) || cData[0] == '(')
				{
					pushData(OpSt, cData);
				}
				else
				{
					// check the order
					while(checkOrder(cData[0]) <= checkOrder(OpSt->Tail->data[0]))
					{
						pushData(PostfixSt, popData(OpSt));
						if(isEmpty(OpSt))
						{
							break;
						}
					}
					pushData(OpSt, cData);
				}
			}
		}
		temp = temp->pNext;
	}
	while(!isEmpty(OpSt))
	{
		pushData(PostfixSt, popData(OpSt));
	}
	return PostfixSt; 	
}

float performOp(float num1, float num2, char op)
{
	switch(op)
	{
		case '%':
			return (int)num1%(int)num2;
			break;
		case '^':
			return mypow(num2,num1);
			break;
		case '*':
			return num1*num2;
			break;
		case '/':
			return num2/num1;
			break;
		case '+':
			return num1+num2;
			break;
		case '-':
			return num2-num1;
			break;
		case 'e':
			return myexp(num1);
			break;
		case 't':
			return mytan(num1*DEC);
			break;
		case 's':
			return mysin(num1*DEC);
			break;
		case 'c':
			return mycos(num1*DEC);
			break;
	}
}

float calculatePostfix(Stack PostfixStack)
{
	pNode ptmp=PostfixStack->Head;
	Stack calStk=(Stack)malloc(sizeof(struct LkList));
	calStk->Head=NULL;
	while(ptmp!=NULL)
	{
		char * token=ptmp->data;
		// if ptmp.data is not number 
		if(!checkData(ptmp->data[0]))
		{
			char snum[50]="";
			char *c_num1,*c_num2;
			if (token[0] == 't' || token[0] == 's' || token[0] == 'c' || token[0]=='e')
			{
				c_num1=popData(calStk);
				c_num2 = c_num1;
				
				sprintf(snum,"%.2f",performOp(atof(c_num1),atof(c_num2),ptmp->data[0]));
				
				pushData(calStk,snum);
			}
			else
			{
				c_num1=popData(calStk);
				c_num2=popData(calStk);
				sprintf(snum,"%.2f",performOp(atof(c_num1),atof(c_num2),ptmp->data[0]));
				pushData(calStk,snum);
			}
			
		}
		else
			pushData(calStk,ptmp->data);
		ptmp=ptmp->pNext;
	}
	return atof(calStk->Head->data);
}


 
char printAttention()
{
	printf("\n********************** Input Attention **********************\n");
	printf("** 1. If the number is negative, must be with parentheses. **\n");
	printf("** 2. If you want to perform exp(), please enter e().      **\n");
	printf("** 3. If you want to perform sin(), please enter s().      **\n");
	printf("** 4. If you want to perform cos(), please enter c().      **\n");
	printf("** 5. If you want to perform tan(), please enter t().      **\n");
	printf("*************************** End *****************************\n");
}


int main()
{
	char inputtmp[255];

	Stack PostfixStack=(Stack)malloc(sizeof(struct LkList));
	Stack InfixStack=(Stack)malloc(sizeof(struct LkList));
	InfixStack->Head=NULL;
	PostfixStack->Head=NULL;
	
	printAttention();
	printf("\nPlease input: ");
	scanf("%s",inputtmp);
	
	
	PreProcessInput(inputtmp);

	inputData(inputtmp,InfixStack);

	printf("\nPost Infix: ");
	PostfixStack=convertInfixtoPostfix(InfixStack);
	printStack(PostfixStack);
	cout<<endl<<endl;
	
	float res = calculatePostfix(PostfixStack);
	
	cout<<"Result is: "<<res<<endl;
	
	free(PostfixStack);
	free(InfixStack);
	
	return 0;
}

