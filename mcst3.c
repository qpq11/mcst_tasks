#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void Swap(void* ptr1, void* ptr2, size_t sizeofelem);

int CmpFunc(const void* ptr1, const void* ptr2);

int CmpFuncRev(const void* ptr1, const void* ptr2);

void BubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*cmp)(const void*, const void*));

void RevBubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*cmp)(const void*, const void*));

size_t CountLines(char* txtarr);

void ClearBuffer(void);

size_t SizeOfFile(FILE * fileName);

const int PrintSymbolsBegin = 32; //отграничение печатных и непечатных символов- печатные начинаются с кода 32

int main(int argc, const char** argv)
{
	FILE* ReadFile      = fopen("ReadFile.txt     ",  "r");
	FILE* SortedFile	= fopen("SortedFile.txt   ", "w+"); //имеем файл под сортировку по первым символам
	FILE* RevSortedFile = fopen("RevSortedFile.txt", "w+"); //и файл под сортировку по последним символам строк
	if (argc >= 4)
	{
		FILE* ReadFile      = fopen(argv[1], "r" );
		FILE* SortedFile	= fopen(argv[2], "w+");
		FILE* RevSortedFile = fopen(argv[3], "w+");
	}
	else if (argc == 3)
	{
		FILE* ReadFile      = fopen(argv[1], "r" );
		FILE* SortedFile	= fopen(argv[2], "w+");
	}
	else if (argc == 2)
	{
		FILE* ReadFile      = fopen(argv[1], "r" );
	}

	assert(ReadFile      != NULL);
	assert(SortedFile    != NULL);
	assert(RevSortedFile != NULL);

	size_t tsize = SizeOfFile(ReadFile);

	rewind(ReadFile);

	char* Buffer = (char*)calloc(tsize+1, sizeof(char));
	fread (Buffer,  sizeof(char),   tsize,    ReadFile);


	fclose(ReadFile);

	size_t nLines = CountLines(Buffer);

	char** arrPointer = (char**) calloc(nLines, sizeof(char*));

	arrPointer[0] = &Buffer[0];
	
	for (size_t i = 1; i < nLines; i++)
	{
		arrPointer[i] = strchr(arrPointer[i-1], '\0') + 1;
		if (*arrPointer[i] == '\n')
			arrPointer[i]++;
	}

	BubbleSort(arrPointer, nLines, sizeof(char*), CmpFunc);

	for (size_t j = 0; j < nLines; j++)
	{
		printf("%d\n", arrPointer[j][0]);
		if(arrPointer[j][0] >= PrintSymbolsBegin)
		{
			fprintf(SortedFile, "%s", arrPointer[j]);
			fprintf(SortedFile, "\n");
		}
	//fputs(arrPointer[j], SortedFile);
	}

	fclose(SortedFile);
	putchar('\n');

	RevBubbleSort(arrPointer, nLines, sizeof(char*), CmpFuncRev);

	for (size_t j = 0; j < nLines; j++)
	{
		printf("%d\n", arrPointer[j][0]);
		if(arrPointer[j][0] >= 32)
		{
			fprintf(RevSortedFile, "%s", arrPointer[j]);
			fprintf(RevSortedFile, "\n");
		}
	}

	fclose(RevSortedFile);
	
	free(arrPointer);
	free(Buffer);

	return 0;
}


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


size_t SizeOfFile(FILE * fileName)
{
	fseek(fileName, 0, SEEK_END);
	size_t size = ftell(fileName);
	return size;
}


void Swap(void* ptr1, void* ptr2, size_t sizeofelem)
{
	void* temp = (void*)calloc(sizeofelem, 1);

	temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;

	free(temp);
}

