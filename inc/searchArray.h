#ifndef SEARCH_ARRAY_H
#define SEARCH_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Linear Search that returns the pointer
 *  \param key what we want to find
 *  \param array where we are going to look for it
 *  \param nElementsOnArray holds the size of the [array]
 *  \param elementSize is the size in bytes for the key or any element on the array
 *  \param compareFunction is a function pointer that compares two void* arguments. It must return a 0 if the result is equal and != 0 if they are different
 *  \return pointer to the first [key] found on [array] found. NULL if no element was found
 */
void* searchArrayPtr(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*));

/** Linear Search that returns the pointer
 *  \param key what we want to find
 *  \param array where we are going to look for it
 *  \param nElementsOnArray holds the size of the [array]
 *  \param elementSize is the size in bytes for the key or any element on the array
 *  \param compareFunction is a function pointer that compares two void* arguments. It must return a 0 if the result is equal and != 0 if they are different
 *  \return index to the first [key] found on [array]. Index = nElementsOnArray if no element was found
 */
unsigned long searchArrayIdx(void* key, void* array, unsigned long nElementsOnArray, unsigned int elementSize, int (*compareFunction)(void*, void*));

/** Compares integer values
 *  \param input1 ptr to first int
 *  \param input2 ptr to second int
 *  \return value of first int - value of second int (*input1 - *input2)
 */
int compareInt(void* input1, void* input2);

/** Compares long integer values
 *  \param input1 ptr to first long
 *  \param input2 ptr to second long
 *  \return value of first long - value of second long (*input1 - *input2)
 */
int compareLong(void* input1, void* input2);

/** Compares values of strings through its second-order pointers
 *  \param input1 ptr to ptr to c-string
 *  \param input2 ptr to ptr to c-string
 *  \return returns 0 if both are equal, != 0 otherwise
 */
int compareStr(void* input1, void* input2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SEARCH_ARRAY_H */