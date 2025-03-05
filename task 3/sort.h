#ifndef SORT
#define SORT

void BubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*cmp)(const void*, const void*));

void RevBubbleSort(char* arr[], size_t sizeofarr, size_t sizeoftype, int (*cmp)(const void*, const void*));

#endif