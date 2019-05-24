#include <stdlib.h>
#include <strings.h>

void* searchArrayPtr(void* key, void* array, unsigned int nElementsOnArray, unsigned int elementSize) {
	void* elementAddr = NULL;
	for (unsigned int i = 0; i < nElementsOnArray; i++) {
		elementAddr = (char*)array + i*elementSize;
		if (memcmp(elementAddr, key, elementSize) == 0) break;
	}
	return elementAddr;
}

unsigned int searchArrayIdx(void* key, void* array, unsigned int nElementsOnArray, unsigned int elementSize) {
	void* elementAddr = NULL;
	unsigned int i = 0;
	for (; i < nElementsOnArray; i++) {
		elementAddr = (char*)array + i*elementSize;
		if (memcmp(elementAddr, key, elementSize) == 0) break;
	}
	return i;
}