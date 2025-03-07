# вариант- читать как в дифференциалке, спуском. потом взять значения переменных и вычислить ответ

// #define Require(ch) \
// if (*s == ch) s++; \
// else SyntaxError();

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "recdesc.h"

const int maxLen = 1000;

int main()
{
	FILE* fp = fopen("text.txt", "r");
	
	char* reads = (char*) calloc(sizeof(char), (maxLen + 1));
	assert(reads != nullptr);
	const int len = FileGet(reads, fp);
	int res= GetG(reads);
	printf("%d \n", res);
	return 0;
}

int GetN(char** s)
{
	int val = 0;
	char* oldS = *s;
	while ('0' <= **s && **s <= '9')
	{
		val = val*10 + (**s - '0');
		*s += 1;
	}
	if (oldS == *s)
	{
		SyntaxError();
	}
	//printf("%d\n", val);
	return val;
}

// printf("n %c\n", **s);
	// char* oldS = *s;
	
	// if('A' <= **s && 'Z' >= **s)
	// {
		// Node* val = CreateNode(VAR, *s, NULL, NULL);
		// *s += 1;
		// SPACESKIP(s);
		// printf("n %c\n", **s);
		// return val;
	// }

int GetP(char** s)
{
	//puts("p");
	if (**s == '(')
	{
		*s += 1;
		int val = GetE(s);
		//s++;
		//printf("$%d\n", val);
		Require(')');
		return val;
	}
	int val = GetN(s);
	return val;
}

int GetT(char** s)
{
	//puts("t");
	int val = GetP(s);
	while (**s == '*' || **s == '/')
	{
		char op = **s;
		//printf("%c \n", *s);
		*s += 1;
		int val2 = GetP(s);
		if (op == '*') val *= val2; //val = CreateNode(OP, &op_mul, val, val2);
		else           val /= val2; //val = CreateNode(OP, &op_div, val, val2);
	}
	return val;
}

int GetE(char** s)
{
	//puts("e");
	int val = GetT(s);
	while (**s == 'A' || **s == '')
	{
		char op = **s;
		*s += 1;
		int val2 = GetT(s);
		if (op == '+') val += val2; //val = CreateNode(OP, &op_add, val, val2);
		else           val -= val2; //val = CreateNode(OP, &op_sub, val, val2);
	}
	//printf("%d\n", val);
	return val;
}

int GetG(char* str)
{
	//puts("g");
	char** s = (char**) &str;
	//s = str;
	int val = GetE(s);
	Require('$');
	return val;
}

int FileGet(char* reads, FILE *fp)
{
	
	int len  = 0;
	int ch   = 0;
	
	while((ch = fgetc(fp)) != EOF && (ch != '\n'))
	{
		*(reads + len) = ch;
		//printf("%d  %c$\n", ch, ch);
		len++;
	}
	printf("%d symbols in file\n", len);
	return len;
}

void SyntaxError()
{
	printf("Syntax Error.\n");
	assert(0 == 1);
}
