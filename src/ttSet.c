#include <ttSet.h>
#include <ttMiscArray.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include "ttConfig.h"
#include "ttMemory.h"

#define PTR_SIZE    sizeof(char*)

/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

void ttSetNew(TTSet* s, int elementSize, void (*dealocFunction)(void*)) {
    assert(s != NULL);
    assert(elementSize > 0);
    s->_elementSize = elementSize;
    s->_logicalLen = 0;
    s->_allocLen = PREALLOC_SIZE;
    s->_array = ttrealloc(0, PREALLOC_SIZE * PTR_SIZE);
    ttmemset(s->_array, 0, PREALLOC_SIZE * PTR_SIZE);
    s->_dealocFunction = dealocFunction;
    assert(s->_array != NULL);
}

void ttSetDispose(TTSet *s) {
    assert(s != NULL);
//    if (s->_dealocFunction != NULL) {
//        while(s->_logicalLen > 0) {
//            void* element;
//            ttSetRemovePtr(s, element);
//        }
//    }
    s->_allocLen = 0;
    s->_logicalLen = 0;
    s->_dealocFunction = NULL;
    ttfree(s->_array);
}

void ttSetGrow(TTSet* s) {
    s->_allocLen *= 2;
    s->_array = ttrealloc(s->_array, s->_allocLen * PTR_SIZE);
    assert(s->_array != NULL);
}

void ttSetSaveCopy(TTSet *s, void *elementAddress) {
    assert(s != NULL);

    void* copy = realloc(NULL, s->_elementSize);
    ttmemcpy(copy, elementAddress, s->_elementSize);
    ttSetSaveAllocatedPtr(s, copy);
}

void ttSetSaveAllocatedPtr(TTSet *s, void *elementAddress) {
    assert(s != NULL);

    // doubles if we reach the size of the allocated stack
    if (s->_logicalLen == s->_allocLen) {
        ttSetGrow(s);
    }

    // copies the address of the allocated element to the array
    char** target = (char**) s->_array + s->_logicalLen * PTR_SIZE;
    *target = elementAddress;
    s->_logicalLen++;
}


void *ttSetContainsPtr(TTSet *s, void *elmPtr, unsigned long *optArrayIdx) {
    return searchArrayPtr(&elmPtr, s->_array, s->_allocLen, PTR_SIZE, NULL, optArrayIdx);
}

int ttSetValueCompareFcn(void* num1, void* num2, unsigned int elementSize) {
    if ((*(char**)num1 == NULL) || (*(char**)num2 == NULL)) return -1;
    char* num11 = *(char**)num1;
    char* num22 = *(char**)num2;
    return memcmp(num11, num22, elementSize);
}

void* ttSetContainsValue(TTSet *s, void *elmPtr, unsigned long *optArrayIdx) {
    return searchArrayPtr(&elmPtr, s->_array, s->_allocLen, PTR_SIZE, &ttSetValueCompareFcn, optArrayIdx);
}

int ttSetRemovePtr(TTSet *s, void *elementAddress) {
    // asserts for sanity check
    assert(s != NULL);
    assert(elementAddress != NULL);
    assert(s->_logicalLen > 0);

    s->_logicalLen--;

    // deallocates the memory the element occupies and zeros reference in swiss cheese
    void* ptr;
    unsigned long idx;
    if ((ptr = ttSetContainsPtr(s, elementAddress, &idx))) {
        if (s->_dealocFunction != NULL) {
            s->_dealocFunction(ptr);
        }
        free(ptr);
        ((char**)s->_array)[idx * PTR_SIZE] = (char*)NULL;
        return 0;
    } else {
        return -1;
    }
}

int ttSetRemoveValue(TTSet *s, void *elementAddress) {
    // asserts for sanity check
    assert(s != NULL);
    assert(elementAddress != NULL);
    assert(s->_logicalLen > 0);

    s->_logicalLen--;

    // deallocates the memory the element occupies and zeros reference in swiss cheese
    void* ptr;
    unsigned long idx;
    if ((ptr = ttSetContainsValue(s, elementAddress, &idx))) {
        if (s->_dealocFunction != NULL) {
            s->_dealocFunction(ptr);
        }
        free(ptr);
        ((char**)s->_array)[idx * PTR_SIZE] = (char*)NULL;
        return 0;
    } else {
        return -1;
    }
}