#include "ttconfig.h"
#include "ttmemory.h"
#include <assert.h>
#include "ttlinkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include "ttutil.h"

/***** MEMORY TRACKER *****/

/*** OBJECTS ***/

typedef struct {
    void* pointer;
    long size;
} MemoryAllocation;

typedef struct {
    char initialized;
    long memoryUse;
    MemoryAllocation* list;
    long listAllocationSize;
} MemoryTracker;
MemoryTracker memoryTracker = {0, 0, NULL, 0};

/**

+================+      +------------------------+
|                |      |                        |
| void* pointer  +----->| Target memory location |
|                |      |                        |
+----------------+      +------------------------+
|                |
| long size      |
|                |
+================+
|                |
| void* pointer  |
|     NULL       |
+----------------+
|                |
| long size      |
|                |
+================+
|                |
| void* pointer  |
|     NULL       |
+----------------+
|                |
| long size      |
|                |
+================+

 */

/*** METHODS ***/

#ifdef TRACK_MEMORY_EN

#define PRINT_MEMORY_MSG    1

long ttgetMemoryUse(void) {
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG Memory use: %ld\n", memoryTracker.memoryUse)),());
	return memoryTracker.memoryUse;
}

/// initializes the memory logger
void ttmemoryInit(void) {
	memoryTracker.initialized = 1;
	memoryTracker.list = malloc(100*sizeof(MemoryAllocation));
    memoryTracker.listAllocationSize = 100;
    ttmemset(memoryTracker.list, 0, memoryTracker.listAllocationSize*sizeof(MemoryAllocation));
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG Memory Logger initialized\n")),());
}

/// destroys the memory logger and all contents allocated
void ttmemoryDispose(void) {
    // todo: clear all items
	free(&memoryTracker.list);
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG Memory Logger disposed\n")),());
}

/// registers a memory allocation in tracker
void _ttregisterMemory(MemoryAllocation* newNode) {
	// looks for an empty space in the swiss cheese array
    MemoryAllocation* node = memoryTracker.list;
    unsigned long position = 0;
    for (; position < memoryTracker.listAllocationSize; position++) {
        if (node->pointer == NULL) {
            break;
        }
        node++;
    }

    // do we need to increase space?
    if (position == memoryTracker.listAllocationSize) {
        memoryTracker.list = realloc(memoryTracker.list, memoryTracker.listAllocationSize*2);
        ttmemset(memoryTracker.list + memoryTracker.listAllocationSize*sizeof(MemoryAllocation), 0,
                 memoryTracker.listAllocationSize*sizeof(MemoryAllocation));
        memoryTracker.listAllocationSize *= 2;
        COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG Swiss cheese array increased to: %ld\n", memoryTracker.memoryUse)),());
    }

    // now we finally place the node in the swiss cheese array
    node = newNode;
    memoryTracker.memoryUse += node->size;
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG New node stored at: %p\n", node->pointer)),());
}

void _ttunregisterMemory(void* ptr) {
    // looks for reference to this address and clears it
    MemoryAllocation* node = memoryTracker.list;
    unsigned int nodeIter = 0;
    for (; nodeIter < memoryTracker.listAllocationSize; nodeIter++) {
        if (node) {
            if (node->pointer == ptr) {
                memoryTracker.memoryUse -= node->size;
                break;
            }
        }
        node++;
    }

    // if the memory address was not found
    if (nodeIter == memoryTracker.listAllocationSize) {
        COND_CODE_1(PRINT_MEMORY_MSG, (printf("DBG Node not found on memory tracker\n")),());
        // register error
    }
}

/// same as libc realloc, but with debugging features
void* ttrealloc(void* ptr, long size) {
	void* retVal = realloc(ptr, size);
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("Node %p allocated\n", retVal)),());
	if (!memoryTracker.initialized) {
		ttmemoryInit();
	}
	if (retVal) {
        // record memory used
		MemoryAllocation newNode;
		newNode.pointer = retVal;
		newNode.size = size;
//		if (ptr) {
//            _ttunregisterMemory(ptr);
//        }
//		_ttregisterMemory(&newNode);
	}
	return retVal;
}

/// same as libc malloc, but with debugging features
void* ttmalloc(long size) {
    return ttrealloc(NULL, size);
}

void ttfree(void* ptr) {
	// release memory use from records
    COND_CODE_1(PRINT_MEMORY_MSG, (printf("Node %p free\n", ptr)),());
	free(ptr);
	//_ttunregisterMemory(ptr);
}

#elif /* TRACK_MEMORY */

/// wrapper around realloc
void* ttrealloc(void* ptr, long size) {
	return realloc(*ptr, size);
}

/// wrapper around malloc
void* ttmalloc(long size) {
    return ttrealloc(NULL, size);
}

/// wrapper around free
void ttfree(void* ptr) {
	free(ptr);
}

#endif /* TRACK_MEMORY */

/***** GENERAL MEMORY FUNCTIONS *****/

void* ttmemcpy(void* dest, const void *src, long len) {
    // taken from https://github.com/gcc-mirror/gcc/blob/master/libgcc/memcpy.c
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

void* ttmemset(void *dest, int val, long len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
        *ptr++ = val;
    return dest;
}

void _swap(void* element1, void* element2, int elementSize) {
	assert(element1 != NULL);
	assert(element2 != NULL);
	assert(elementSize > 0);
	char buffer[elementSize];
	ttmemcpy(buffer, element1, elementSize);
	ttmemcpy(element1, element2, elementSize);
	ttmemcpy(element2, buffer, elementSize);
}
