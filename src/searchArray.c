#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <stdio.h>

void* searchArrayPtr(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*)) {
	assert(array != NULL);
	assert(key != NULL);
	assert(nElementsOnArray > 0);
	assert(elementSize > 0);
	assert(compareFunction != NULL);

	void* elementAddr = NULL;
	for (unsigned long i = 0; i < nElementsOnArray; i++) {
		if (compareFunction(key, (char*)array + i*elementSize) == 0) {
			elementAddr = (char*)array + i*elementSize;
			break;
		}
	}
	return elementAddr;
}

unsigned long searchArrayIdx(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*)) {
	assert(array != NULL);
	assert(key != NULL);
	assert(nElementsOnArray > 0);
	assert(elementSize > 0);
	assert(compareFunction != NULL);

	void* elementAddr = NULL;
	unsigned long i = 0;
	for (; i < nElementsOnArray; i++) {
		if (compareFunction(key, (char*)array + i*elementSize) == 0) break;
	}
	return i;
}

int compareInt(void* input1, void* input2) {
	int* int1 = (int*)input1;
	int* int2 = (int*)input2;
	//printf("%d, %d\n", *int1, *int2);
	return (*int1 - *int2);
}

int compareLong(void* input1, void* input2) {
	long* int1 = (long*)input1;
	long* int2 = (long*)input2;
	//printf("%ld, %ld\n", *int1, *int2);
	return (*int1 - *int2);
}

int compareStr(void* input1, void* input2) {
	const char* str1 = *(const char**)input1;
	const char* str2 = *(const char**)input2;
	//printf("%s, %s\n", str1, str2);
	return strcmp(str1, str2);
}