// Configurations
/// This defines preallocated number of elements when a stack is created
#define PREALLOC_SIZE	4

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Object
typedef struct {
	int _logicalLen;
	int _allocLen;
	void* _elements;
	int _elementSize;
} Stack;

// Methods
void stackNew(Stack *s, int elementSize);
void stackDispose(Stack *s);
void stackPush(Stack *s, void* elementAddress);
void stackPop(Stack *s, void* elementAddress);

#ifdef __cplusplus
}
#endif /* __cplusplus */