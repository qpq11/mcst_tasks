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

//функции сортировок

void BubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*cmp)(const void*, const void*))
{
	for (int unsigned pass = 0; pass < sizeofarr - 1; pass++)
	{
		int scr = 0;
		for (int unsigned i = 0; i < sizeofarr - 1 -pass; i++)
		{
			if (cmp(arr[i], arr[i + 1]) > 0)
			{
				scr++;
				Swap(&arr[i], &arr[i+1], sizeoftype);
			}
		}
		if (scr == 0) break;
	}
}


void RevBubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*r_cmp)(const void*, const void*))
{
	for (int unsigned pass = 0; pass < sizeofarr - 1; pass++)
	{
		int scr = 0;
		for (int unsigned i = 0; i < sizeofarr -1 - pass; i++)
		{
			if (r_cmp(arr[i],arr[i+1])>0)
			{
				scr++;
				Swap(&arr[i], &arr[i+1], sizeoftype);
			}
		}
		if (scr == 0) break;
	}
}