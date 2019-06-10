#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <stdio.h>
#include <ttmiscArray.h>

//void* searchArrayPtr(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*)) {
//	assert(array != NULL);
//	assert(key != NULL);
//	assert(nElementsOnArray > 0);
//	assert(elementSize > 0);
//
//	void* elementAddr = NULL;
//	for (unsigned long i = 0; i < nElementsOnArray; i++) {
//		if (compareFunction) {
//			if (compareFunction(key, (char *) array + i * elementSize) == 0) {
//				elementAddr = (char *) array + i * elementSize;
//				break;
//			}
//		} else {
//			if (memcmp(key, (char *) array + i * elementSize, elementSize) == 0) {
//				elementAddr = (char *) array + i * elementSize;
//				break;
//			}
//		}
//	}
//	return elementAddr;
//}

/**
 * Searches in an array for a pointer
 * @param key pointer to memory address containing what we want to look for
 * @param array pointer to start of array
 * @param nElmOnArray number of elements in array
 * @param elmSize size in bytes for each element
 * @param optCompareFcn optional function of equality. Should return 0 if equal. See [compareInt]
 * @param optArrayIdx if informed, gets filled with array idx when elm is found. Set to array size if not found
 * @return ptr to array if found. NULL if not found
 */
void *searchArrayPtr(void *key, void *array, unsigned long nElmOnArray, unsigned int elmSize,
					 int (*optCompareFcn)(void *, void *, unsigned int), unsigned long *optArrayIdx) {

	// sanity check
	assert(array != NULL);
	assert(key != NULL);
	assert(nElmOnArray > 0);
	assert(elmSize > 0);

	// sets "not found" return values
	void* elementAddr = NULL;
	if (optArrayIdx) {
		*optArrayIdx = nElmOnArray;
	}

	// iterates on all elements
	for (unsigned long i = 0; i < nElmOnArray; i++) {
		// updates pointer to each and every element in array
		char* elmPtr = (char*)array + i * elmSize;
		if (elmPtr) {
			// if there's a comparison fcn
			if (optCompareFcn) {
				if (optCompareFcn(key, elmPtr, elmSize) == 0) {
					elementAddr = elmPtr;
					if (optArrayIdx) {
						*optArrayIdx = i;
					}
					break;
				}
			// if there's none, perform memory comparison
			} else {
				if (memcmp(key, elmPtr, elmSize) == 0) {
					elementAddr = elmPtr;
					if (optArrayIdx) {
						*optArrayIdx = i;
					}
					break;
				}
			}
		}
	}
	return elementAddr;
}

int compareInt(void* input1, void* input2, unsigned int elmSize) {
	int* int1 = (int*)input1;
	int* int2 = (int*)input2;
	//printf("%d, %d\n", *int1, *int2);
	return (*int1 - *int2);
}

int compareLong(void* input1, void* input2, unsigned int elmSize) {
	long* int1 = (long*)input1;
	long* int2 = (long*)input2;
	//printf("%ld, %ld\n", *int1, *int2);
	return (*int1 - *int2);
}

int compareStr(void* input1, void* input2, unsigned int elmSize) {
	const char* str1 = *(const char**)input1;
	const char* str2 = *(const char**)input2;
	//printf("%s, %s\n", str1, str2);
	return strcmp(str1, str2);
}