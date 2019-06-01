#include "ttmemory.h"
#include <assert.h>

#define NULL    0

void *_memcpy (void* dest, const void *src, long len) {
    // taken from https://github.com/gcc-mirror/gcc/blob/master/libgcc/memcpy.c
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

void _swap(void* element1, void* element2, int elementSize) {
	assert(element1 != NULL);
	assert(element2 != NULL);
	assert(elementSize > 0);
	char buffer[elementSize];
	_memcpy(buffer, element1, elementSize);
	_memcpy(element1, element2, elementSize);
	_memcpy(element2, buffer, elementSize);
}
