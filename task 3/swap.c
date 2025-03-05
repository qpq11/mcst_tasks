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

//поменять местами строки
void Swap(void* ptr1, void* ptr2, size_t sizeofelem)
{
	void* temp = (void*)calloc(sizeofelem, 1); //просто переприсваивание все ломало

	memcpy(temp, ptr1, sizeofelem);
	memcpy(ptr1, ptr2, sizeofelem);
	memcpy(ptr2, temp, sizeofelem);

	free(temp);
}