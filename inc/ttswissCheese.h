/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

/**
 *  _____     _         _ _ _
 * |_   _|_ _| |_ _   _| (_) |__
 *   | |/ _` | __| | | | | | '_ \
 *   | | (_| | |_| |_| | | | |_) |
 *   |_|\__,_|\__|\__,_|_|_|_.__/
 *
 *
 *                  ,::////;::-.
 *                 /:'///// ``::>/|/
 *               .',  ||||    `/( e\
 *           -==~-'`-Xm````-mm-' `-_\
**/

#ifndef TATU_LIBRARY_TTSWISSCHEESE_H
#define TATU_LIBRARY_TTSWISSCHEESE_H

/***** CONFIGURATIONS *****/

/// This defines preallocated number of elements when a swiss cheese is created
#define PREALLOC_SIZE	4

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***** IMPLEMENTATION NOTES *****

    Swiss cheese is a simple fast algorithm for storing sets of pointers to variables.
    It starts as a simple stack.
    As elements are randomly eliminated, we place NULLs on the places they occupied, leaving holes.

    Whenever we add a new element, we fill these holes, and only when we are out of holes and free
    pre-allocated space at the end, we allocate additional memory.

    Elements should be allocated by the client, and swiss cheese will take care of deallocation.
    If you wish to pass a "special" deallocation function, you may do so. Check [ttSwissNew]

    Extending algorithm for variable-sized elements we'll have a naïve implementation of a heap
    memory allocator.

*/


/// Defines preallocated number of elements when a stack is created
#define PREALLOC_SIZE	4

/***** OBJECT *****/

typedef struct {
    unsigned long _logicalLen;			///< size of elements stored in number of elements
    unsigned long _allocLen;			///< allocated size (physical) in number of elements
    void** _array;				        ///< pointer to actual elements memory location. Swiss cheese array
    int _elementSize;					///< size of each element in number of bytes
    void (*_dealocFunction)(void*);		///< function called when every element has to be dealocated
} TTSwissCheese;

/***** METHODS *****/

void ttSwissNew(TTSwissCheese *s, int elementSize, void (*dealocFunction)(void *));
void ttSwissDispose(TTSwissCheese *s);
void ttSwissSaveAllocatedPtr(TTSwissCheese *s, void *elementAddress);
void ttSwissSaveCopy(TTSwissCheese *s, void *elementAddress);

/// Removes element with the same contents o [elementAddress] from [s]
/// \return 0 if success, -1 if element was not found
int ttSwissRemovePtr(TTSwissCheese *s, void *elementAddress);

/**
 * Checks if set contains whatever is pointed by elementAddress. This checks for element contents equality, not memory equality
 * @param s SwissCheese array
 * @param elmPtr
 * @param optArrayIdx
 * @return the address to the element on the swiss cheese. Zero if does not contain
 */
void *ttSwissContainsPtr(TTSwissCheese *s, void *elmPtr, unsigned long *optArrayIdx);

void* ttSwissContainsValue(TTSwissCheese *s, void *elmPtr, unsigned long *optArrayIdx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //TATU_LIBRARY_TTSWISSCHEESE_H
