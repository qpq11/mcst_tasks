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

//определение размера файла

size_t SizeOfFile(FILE * fileName)
{
	fseek(fileName, 0, SEEK_END);
	size_t size = ftell(fileName);
	return size;
}