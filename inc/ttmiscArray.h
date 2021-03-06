/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

#ifndef SEARCH_ARRAY_H
#define SEARCH_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//void* searchArrayPtr(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*));
void *searchArrayPtr(void *key, void *array, unsigned long nElmOnArray, unsigned int elmSize,
                     int (*optCompareFcn)(void *, void *, unsigned int), unsigned long *optArrayIdx);

int compareInt(void* input1, void* input2, unsigned int elmSize);
int compareLong(void* input1, void* input2, unsigned int elmSize);
int compareStr(void* input1, void* input2, unsigned int elmSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SEARCH_ARRAY_H */
