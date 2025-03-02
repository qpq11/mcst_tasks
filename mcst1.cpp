#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <malloc.h>

const int ThreadCnt = 4; // Количество потоков. Значение можно оптимизировать (4 потока на маленьком массиве разницы ощутимой не дадут )

int cmp_func (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}

void * quick_sort(void* args)
{ 
    qsort(args, (sizeof(args) / sizeof(int)), sizeof(int), cmp_func);
}

int * merge(int* left, int* right)
{
	int  leftSize       =  sizeof(left) / sizeof(int);
	int  mergedSize = (sizeof(left) + sizeof(right)) / sizeof(int);
	int* mergedArr   = (int*) calloc(mergedSize, sizeof(int));
	
	for (int i = 0; i < mergedSize; i++)
	{
		if (i < leftSize)
		{
			mergedArr[i] = left[i];
		}
		else
		{
			mergedArr[i] = right[i - leftSize];
		}
	}
	
	free(left);
	free(right);
	
	return mergedArr;
}

int main()
{
    pthread_t thread[ThreadCnt];
    int arrSize = 0;
	scanf("%d", &arrSize);
	int* arr = (int*) calloc(arrSize, sizeof(int));
	int* threadSubArr[ThreadCnt] ;
	int i = 0;
	for (i = 0; i < arrSize; i++)
	{
		scanf("%d", &arr[i]);
	}
	int j = 0;
	int baseSize = arrSize / ThreadCnt;
	int addSize   = arrSize % ThreadCnt;
    for(j = 0; j < ThreadCnt; j++)
	{
		int start = (baseSize + 1) * j ;
        int end  = ((start + baseSize) <= arrSize ? (start + baseSize) : arrSize);						//+ (j < addSize ? 1 : 0); 
		threadSubArr[j] = (int*) calloc(end - start,sizeof(int));
		for (int i = start; i < end; i++  )
		{
			threadSubArr[j][i-start] = arr[i];
		}
        //index_start = (baseSize + 1) * j ;
        //index_end  = threadSubArr[j].index_start + baseSize + (j < addSize ? 1 : 0); 
        pthread_create(&thread[j], NULL, quick_sort, &threadSubArr[j]); 
    }
    
	int* res = (int*) calloc(arrSize, sizeof(int));
    for(j = 0; j < ThreadCnt; j++)
	{
        pthread_join(thread[j], NULL); 
        res = merge(res, threadSubArr[j]);
    }
	
	for(i = 0; i < arrSize; i++)
	{
		printf("%d  ", res[i]);
	}
	free(res);
	free(arr);
}