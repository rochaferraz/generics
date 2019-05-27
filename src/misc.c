#include "misc.h"
#include <assert.h>
#include <memory.h>

void _swap(void* element1, void* element2, int elementSize) {
	assert(element1 != NULL);
	assert(element2 != NULL);
	assert(elementSize > 0);
	char buffer[elementSize];
	memcpy(buffer, element1, elementSize);
	memcpy(element1, element2, elementSize);
	memcpy(element2, buffer, elementSize);
}

inline void swap_int(int* element1, int* element2) {
	assert(sizeof(*element1) == sizeof(*element2));
	_swap(element1, element2, sizeof(*element1));
}

inline void swap_uint(unsigned int* element1, unsigned int* element2) {
	assert(sizeof(*element1) == sizeof(*element2));
	_swap(element1, element2, sizeof(*element1));
}

inline void swap_long(long* element1, long* element2) {
	assert(sizeof(*element1) == sizeof(*element2));
	_swap(element1, element2, sizeof(*element1));
}

inline void swap_ulong(unsigned long* element1, unsigned long* element2) {
	assert(sizeof(*element1) == sizeof(*element2));
	_swap(element1, element2, sizeof(*element1));
}

inline void swap_strptr(char* element1, char* element2) {
	assert(sizeof(element1) == sizeof(element2));
	_swap(element1, element2, sizeof(element1));
}
