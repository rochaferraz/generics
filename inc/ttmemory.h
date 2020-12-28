/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <assert.h>

/**
 * Does the same as memcpy: copies a memory location. Locations cannot overlap
 * @param dest pointer to destination
 * @param src pointer to source
 * @param len number of bytes to copy
 * @return original value of destination
 */
void* ttmemcpy(void* dest, const void *src, long len);

void* ttmemset(void *dest, int val, long len);

/** Generic Swap function swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first data structure to be swapped
 *  \param element2 pointer to second data structure to be swapped
 *  \param elementSize size of element. Use sizeof(<your type>)

    EXAMPLE
 
    int x = 0;
    int y = 1;
    printf("x is %d and y is %d\n", x, y);
    _swap(&x, &y, sizeof(int));
    printf("x is %d and y is %d\n", x, y);
    swap_int(&x, &y); // safer version!
    printf("x is %d and y is %d\n", x, y);

    RESULT

    x is 0 and y is 1
    x is 1 and y is 0
    x is 0 and y is 1
    
 */
void _swap(void* element1, void* element2, int elementSize);

/** Swap for <int> swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first <int> to be swapped
 *  \param element2 pointer to second <int> to be swapped
 */
static inline void swap_int(int* element1, int* element2) {
    assert(sizeof(*element1) == sizeof(*element2));
    _swap(element1, element2, sizeof(*element1));
}

/** Swap for <uint> swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first <uint> to be swapped
 *  \param element2 pointer to second <uint> to be swapped
 */
static inline void swap_uint(unsigned int* element1, unsigned int* element2) {
    assert(sizeof(*element1) == sizeof(*element2));
    _swap(element1, element2, sizeof(*element1));
}

/** Swap for <long> swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first <long> to be swapped
 *  \param element2 pointer to second <long> to be swapped
 */
static inline void swap_long(long* element1, long* element2) {
    assert(sizeof(*element1) == sizeof(*element2));
    _swap(element1, element2, sizeof(*element1));
}

/** Swap for <ulong> swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first <ulong> to be swapped
 *  \param element2 pointer to second <ulong> to be swapped
 */
static inline void swap_ulong(unsigned long* element1, unsigned long* element2) {
    assert(sizeof(*element1) == sizeof(*element2));
    _swap(element1, element2, sizeof(*element1));
}

/** Swap for <char*> strings swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first <char*> null-terminated string to be swapped
 *  \param element2 pointer to second <char*> null-terminated string to be swapped
 */
static inline void swap_strptr(char* element1, char* element2) {
    assert(sizeof(element1) == sizeof(element2));
    _swap(element1, element2, sizeof(element1));
}

#ifdef TRACK_MEMORY_EN
long ttgetMemoryUse(void);
#endif /* TRACK_MEMORY */

void* ttrealloc(void* ptr, long size);
void* ttmalloc(long size);
/// same as libc free, but with debugging features
void ttfree(void* ptr);
void ttmemoryInit(void);
void ttmemoryDispose(void);
long ttgetMemoryUse(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MISC_H */
