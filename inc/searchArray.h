#ifndef SEARCH_ARRAY_H
#define SEARCH_ARRAY_H

void* searchArrayPtr(void* key, void* array, unsigned int nElementsOnArray, unsigned int elementSize);
unsigned int searchArrayIdx(void* key, void* array, unsigned int nElementsOnArray, unsigned int elementSize);

#endif /* SEARCH_ARRAY_H */