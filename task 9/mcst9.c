#include <stdio.h>
#include <malloc.h>

int main()
{
	int arrSize = 0;
	printf("Enter the amount of sorted elems:");
	scanf("%d", &arrSize); //установить длину сортированного массива
	
	if (arrSize <= 0) //разрешить случаи, когда сортировать нечего
	{
		printf("[ 0 ]\n 0");
		return 0;
	}
	
	int* arr = (int*) calloc(arrSize, sizeof(int)); //собственно массив с элементами
    printf("Enter %d elems: ", arrSize);
    for (int i = 0; i < arrSize; i++)
        scanf("%d", &arr[i]);
	
	int* d = (int*) calloc(arrSize, sizeof(int)); //массив максимальных длин последовательностей, начинающихся в
	//каждом arr[i]
	
	int j = 0;
	int maxLen = 0; //длина искомой подпоследовательности
	int maxStart=0; //индекс начала
	while (j < arrSize)
	{
		d[j] = 1;
		int k;
		for (k = j + 1; k < arrSize; k++)
		{
			if(arr[k] > arr[k-1]) //если последовательность возрастает
			{
				//printf("%d %d %d\n", arr[k], arr[j], d[j]);
				d[j]++; //ищем ее дальше
			}
			else //конец подпоследовательности
			{	
				break; //прекращаем рассматривать этот arr[j]
			}
		}
		if(maxLen < d[j]) //если длина превысила максимальную, перезаписываем
		{
			maxLen = d[j];
			maxStart = j;
		}
		
		j=k; //если нашли конец подпоследовательности с началом в arr[j], то в элементах arr вплоть до ее конца
		//искать нам нечего
	}
	
	int maxSum = 0;
	puts("----"); //конец поиска
	printf("[ ");
	for (int i = 0; i < maxLen; i++) //вычисляем сумму по нашим индексу начала и длине; параллельно выводим
	//саму последовательность поэлементно
	{
		printf("%d ", arr[maxStart + i]);
		maxSum += arr[maxStart + i];
	}
	printf("]\n");
	printf("\n%d\n", maxSum);
	free(arr);
	free(d);
	return 0;
}