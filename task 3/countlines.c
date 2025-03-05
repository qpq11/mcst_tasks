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

//подсчет количества сортируемых строк

size_t CountLines(char* txtarr)
{
	int i = 0;
	int cnt = 0;
	while (txtarr[i]!='\0')
	{
		if (txtarr[i] == '\r')
		{
			txtarr[i] = '\0';
			cnt++;
			i+=2;
			continue;
		}
		if (txtarr[i] == '\n')
		{
			txtarr[i] = '\0';
			cnt++;
		}
		i++;
	}
	if (txtarr[i - 1] != '\0' && txtarr[i - 1] != '\n')
		cnt++;
	return cnt;
}