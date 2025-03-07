#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ThreadCnt 4 //я взял 4 потока для программы

typedef struct {
    int* subarray;
    int size;
} ThreadData;

int cmp_func(const void* a, const void* b) //функция-компаратор
{ 
    return (*(int*)a - *(int*)b);
}

void* quick_sort(void* args) //сортировка фрагментов массива с qsort
{
    ThreadData* data = (ThreadData*)args;
    qsort(data->subarray, data->size, sizeof(int), cmp_func);
    return NULL;
}

int* merge(int* left, int leftSize, int* right, int rightSize) 
{ //слияние отсортированных в потоках подмассивов
    int mergedSize = leftSize + rightSize;
    int* mergedArr = (int*) calloc(mergedSize, sizeof(int));

    for (int i = 0; i < leftSize; i++)
        mergedArr[i] = left[i];

    for (int i = 0; i < rightSize; i++)
        mergedArr[leftSize + i] = right[i];

    free(left);
    free(right);
    return mergedArr;
}

int main() 
{
    pthread_t thread[ThreadCnt];
    ThreadData threadData[ThreadCnt];
    
	//Ввод массива
    int arrSize;
    printf("Array size: ");
    scanf("%d", &arrSize);

    int* arr = (int*) calloc(arrSize, sizeof(int));
    printf("Enter %d elems: ", arrSize);
    for (int i = 0; i < arrSize; i++)
        scanf("%d", &arr[i]);

    int* threadSubArr[ThreadCnt];
    int baseSize = arrSize / ThreadCnt;
    int addSize = arrSize % ThreadCnt;

	//разделение массива между потоками
    int start = 0;
    for (int j = 0; j < ThreadCnt; j++) 
	{
        int size = baseSize + (j == ThreadCnt - 1 ? addSize : 0);
        threadSubArr[j] = (int*) calloc(size, sizeof(int));

        for (int i = 0; i < size; i++)
            threadSubArr[j][i] = arr[start + i];

        start += size;

        threadData[j].subarray = threadSubArr[j];
        threadData[j].size = size;
        pthread_create(&thread[j], NULL, quick_sort, &threadData[j]);
    }

	//возврат из потоков, объединение отсортированных подмассивов в один
    for (int j = 0; j < ThreadCnt; j++)
        pthread_join(thread[j], NULL);

    int* res = threadSubArr[0];
    int resSize = (ThreadCnt == 1) ? arrSize : baseSize;

    for (int j = 1; j < ThreadCnt; j++) 
	{
        res = merge(res, resSize, threadSubArr[j], (j == ThreadCnt - 1 ? baseSize + addSize : baseSize));
        resSize += (j == ThreadCnt - 1 ? baseSize + addSize : baseSize);
    }
	
	//сортировка массива из отсортированных частей
	qsort(res, arrSize, sizeof(int), cmp_func);
	
    printf("Sorted array: ");
    for (int i = 0; i < arrSize; i++)
        printf("%d ", res[i]);
    
    printf("\n");

	//ОСВОБОДИТЬ ПАМЯТЬ
    free(res);
    free(arr);
    return 0;
}