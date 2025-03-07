#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ThreadCnt 4 

typedef struct {
    int* subarray;
    int size;
} ThreadData;

int cmp_func(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void* quick_sort(void* args) {
    ThreadData* data = (ThreadData*)args;
    qsort(data->subarray, data->size, sizeof(int), cmp_func);
    return NULL;
}

int* merge(int* left, int leftSize, int* right, int rightSize) {
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

int main() {
    pthread_t thread[ThreadCnt];
    ThreadData threadData[ThreadCnt];
    
    int arrSize;
    printf("Введите размер массива: ");
    scanf("%d", &arrSize);

    int* arr = (int*) calloc(arrSize, sizeof(int));
    printf("Введите %d элементов: ", arrSize);
    for (int i = 0; i < arrSize; i++)
        scanf("%d", &arr[i]);

    int* threadSubArr[ThreadCnt];
    int baseSize = arrSize / ThreadCnt;
    int addSize = arrSize % ThreadCnt;

    int start = 0;
    for (int j = 0; j < ThreadCnt; j++) {
        int size = baseSize + (j == ThreadCnt - 1 ? addSize : 0);
        threadSubArr[j] = (int*) calloc(size, sizeof(int));

        for (int i = 0; i < size; i++)
            threadSubArr[j][i] = arr[start + i];

        start += size;

        threadData[j].subarray = threadSubArr[j];
        threadData[j].size = size;
        pthread_create(&thread[j], NULL, quick_sort, &threadData[j]);
    }

    for (int j = 0; j < ThreadCnt; j++)
        pthread_join(thread[j], NULL);

    int* res = threadSubArr[0];
    int resSize = (ThreadCnt == 1) ? arrSize : baseSize;

    for (int j = 1; j < ThreadCnt; j++) {
        res = merge(res, resSize, threadSubArr[j], (j == ThreadCnt - 1 ? baseSize + addSize : baseSize));
        resSize += (j == ThreadCnt - 1 ? baseSize + addSize : baseSize);
    }
	
	qsort(res, arrSize, sizeof(int), cmp_func);
	
    printf("Отсортированный массив: ");
    for (int i = 0; i < arrSize; i++)
        printf("%d ", res[i]);
    
    printf("\n");

    free(res);
    free(arr);
    return 0;
}