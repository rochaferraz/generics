#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdarg.h>

/** Swaps the contents of [element1] and [element2]
 *  \param element1 pointer to first data structure to be swapped
 *  \param element2 pointer to second data structure to be swapped
 *  \param elementSize size of element. Use sizeof(<your type>)
 */
void swap(void* element1, void* element2, int elementSize);

#define SAME_TYPES(T1, T2) _Generic((  (T1){0}  ), \
  T2: true, \
  default: false \
)

#define sswap(x, y) _Generic((x), \
              long double: swap,  \
              int: swap,          \
              default: swap,      \
              float: swap         \
) (x, y, sizeof(*x))


#ifdef __cplusplus
}
#endif /* __cplusplus */