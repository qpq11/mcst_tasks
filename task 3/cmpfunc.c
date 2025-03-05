#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "swap.h"
#include "cmpfunc.h"
#include "sizeoffile.h"
#include "sort.h"
#include "countlines.h"

//функции-компараторы

int CmpFunc(const void* ptr1, const void* ptr2)
{
	const char* str1 = (const char*)ptr1;
	const char* str2 = (const char*)ptr2;

	return strcmp(str1, str2);
}

int CmpFuncRev(const void* ptr1, const void* ptr2)
{
	const char* str1 = (const char*)ptr1;
	const char* str2 = (const char*)ptr2;

	int pos1 = strlen(str1);
	int pos2 = strlen(str2);

	for (; pos1!=0 && pos2!=0; pos1-- && pos2--)
	{
		if (str1[pos1]>str2[pos2]) return 1;
		if (str1[pos1]<str2[pos2]) return -1;
	}

	if (str1[pos1]>str2[pos2]) return 1;
	if (str1[pos1]<str2[pos2]) return -1;
	return 0;
}