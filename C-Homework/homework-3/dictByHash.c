#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200 // max length of a line in the file 
#define HASH_SIZE 40

/* Define the struct WordRecord */
struct WordRecord 
{
	char *Word;
	char *Meaning;
};

typedef struct WordRecord *WordNode;
 
 /* Copy strings */
 char *copystr(char *strInput)
 {
	int i;
	char *strCpy;
	strCpy = (char *)malloc(sizeof(char)*(strlen(strInput)+1));
	for(i=0; i<strlen(strInput); i++)
	{
		strCpy[i] = strInput[i];
	}
	strCpy[i] = '\0';
	
	return strCpy;
 }


/* Check address if is available */
int CheckAddress(unsigned long addr, WordNode *HashTable)
{
	return HashTable[addr] == NULL;
}


/* Initialize Hash Table */
void InitHashTable(WordNode *HashTable)
{
	int i;
	for(i=0; i<HASH_SIZE; i++)
	{
		HashTable[i] = NULL;
	}
}


 /* BKDR Hash function */
unsigned int BKDRHash(char *str) 
{
	unsigned int seed = 131; //31, 131, 1313, 131313 etc...
	unsigned int hash = 0;

	while(*str)
	{
		hash = (hash * seed) + (*str++);
	}

	return hash;
}


/* Insert to Hash Table */
void InstHashTable(WordNode *HashTable, char *word, char *meaning)
{
	unsigned long hashkey;
	unsigned long addr;
	WordNode pNode;
	
	// get hashkey and address
	hashkey = BKDRHash(word);
	addr = hashkey % HASH_SIZE;
	
	// copy word and meaning
	pNode = (WordNode)malloc(sizeof(struct WordRecord));
	pNode->Word = (char *)malloc(sizeof(strlen(word)+1));
	pNode->Word = copystr(word);
	pNode->Meaning = (char *)malloc(sizeof(strlen(meaning)+1));
	pNode->Meaning = copystr(meaning);
	
	// check the address if is avaliable
	while(! CheckAddress(addr, HashTable))
	{
		addr++;
	}
	
	HashTable[addr] = pNode;
}

/* Make a dictionary */
void MakeDict(WordNode *HashTable)
{
	FILE *fp;
	char inputStr[MAX];
	char *word;
	char *meaning;
	char *pStr;
	char *strTmp;
	
	pStr = (char *)malloc(sizeof(char)*MAX);
	strTmp = (char *)malloc(sizeof(char)*MAX);
	
	strcpy(strTmp, "");
	
	fp = fopen("dict.txt", "r");
	
	while(fgets(inputStr, MAX, fp) != NULL)
	{
		if(inputStr[strlen(inputStr)-1] != 10)
		{
			strcat(strTmp, inputStr);
		}
		else
		{
			strcat(strTmp, inputStr);
			pStr = copystr(strTmp);
			strcpy(strTmp, "");
			word = strtok(pStr, ":");
			meaning = strtok(NULL, ":");
			InstHashTable(HashTable, word, meaning);
		}
	}
	fclose(fp);
}

/* Search Meaning */
int SearchMeaning(WordNode* HashTable, char* inputStr)
{
	unsigned long hashkey;
	WordNode currNode;
	unsigned long addr;
	// get hashkey and address
	hashkey = BKDRHash(inputStr);
	addr = hashkey % HASH_SIZE;
	
	currNode = HashTable[addr];
	
	if(currNode == NULL)
	{
		return -1; // not found 
	}
	
	// Conflict
	while(hashkey != BKDRHash(currNode->Word))
	{
		addr++; // change the address
		 
		if(addr == HASH_SIZE)
		{
			return -1; // not found
		}
		
		if(HashTable[addr])
		{
			currNode = HashTable[addr];
		}
	}
	
	return addr;
}

/* Check Result */
void CheckRes(WordNode * HashTable)
{
	char input_str[20];
	input_str[0] = "";
	unsigned long addr;
	WordNode newNode;
	
	while(input_str[0] != '#')
	{
		printf("\nPlease input word: ");
		scanf("%s", input_str);
		addr = SearchMeaning(HashTable, input_str);
		
		// find the word's meaning
		if(addr != -1)
		{
			printf("\nAddress: %d", addr);
			newNode = HashTable[addr];
			printf("\nMeaning is: %s ", newNode->Meaning);
		}
		else
		{
			if(input_str[0] != '#')
			{
				printf("\nSorry, not found!\n");	
			}
		}
	}
	
	if(input_str[0] == '#')
	{
		printf("\nExit!\n");
	}
 } 
 
 
int main()
{
	// Initialization
	WordNode * HashTable[HASH_SIZE];
	InitHashTable(HashTable);
	
	// Make a dictionary
	MakeDict(HashTable);
	
	// Check result
	CheckRes(HashTable);
	
	return 0;
}


