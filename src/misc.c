#include "misc.h"
#include <assert.h>
#include <memory.h>

void swap(void* element1, void* element2, int elementSize) {
	printf("Sizeof internal: %d\n", elementSize);
	assert(element1 != NULL);
	assert(element2 != NULL);
	assert(elementSize > 0);
	char buffer[elementSize];
	memcpy(buffer, element1, elementSize);
	memcpy(element1, element2, elementSize);
	memcpy(element2, buffer, elementSize);
}
