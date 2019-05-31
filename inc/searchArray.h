#ifndef SEARCH_ARRAY_H
#define SEARCH_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void* searchArrayPtr(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*));
unsigned long searchArrayIdx(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*));

int compareInt(void* input1, void* input2);
int compareLong(void* input1, void* input2);
int compareStr(void* input1, void* input2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SEARCH_ARRAY_H */