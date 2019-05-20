#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first data structure to be swapped
 *  \param element2 pointer to second data structure to be swapped
 *  \param elementSize size of element. Use sizeof(<your type>)
 */
void swap(void* element1, void* element2, int elementSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */