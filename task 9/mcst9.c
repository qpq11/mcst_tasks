#include <stdio.h>
#include <malloc.h>

int main()
{
	int arrSize = 0;
	scanf("%d", &arrSize);
	
	int* arr = (int*) calloc(arrSize, sizeof(int));
    printf("Enter %d elems: ", arrSize);
    for (int i = 0; i < arrSize; i++)
        scanf("%d", &arr[i]);
	
	int* d = (int*) calloc(arrSize, sizeof(int));
	
	// int currSum  = 0;
	// int maxSum   = 0;
	
	int j = 0;
	int maxLen = 0;
	int maxStart=0;
	while (j < arrSize)
	{
		d[j] = 1;
		// currSum = arr[j];
		int k;
		for (k = j + 1; k < arrSize; k++)
		{
			if(arr[k] > arr[j])
			{
				printf("%d %d %d\n", arr[k], arr[j], d[j]);
				d[j]++;
				// currSum += arr[k];
			}
			else
			{	
				break;
			}
		}
		if(maxLen < d[j])
		{
			maxLen = d[j];
			maxStart = j;
		}
		
		j=k;
	}
	
	int maxSum = 0;
	puts("----");
	for (int i = 0; i < maxLen; i++)
	{
		printf("%d\n", arr[maxStart + i]);
		maxSum += arr[maxStart + i];
	}
	printf("\n%d\n", maxSum);
	free(arr);
	free(d);
	return 0;
}