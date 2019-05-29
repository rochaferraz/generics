#ifndef STACK_H
#define STACK_H

// CONFIGURATIONS

/// This defines preallocated number of elements when a stack is created
#define PREALLOC_SIZE	4

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** IMPLEMENTATION NOTES

	This STACK dinamically allocates memory to fit its contents. It starts preallocating space to fit [PREALLOC_SIZE]  
	elements and doubles its allocation size every time it needs it. It only _deallocates_ memory upon calling 
	[stackDispose]. The basic usage	is shown on EXAMPLE 1.

	Whenever an element is pushed through the [stackPush] function, its memory address [elementAddress] is passed. The 
	stack will *copy* whatever this pointer points to, to its own allocated space. Thus the stack holds	the actual 
	elements, and not only pointers to them. 

	The only exception are variable-sized elements such as strings. In that case the stack holds memory addresses and 
	it's the user's responsibility of allocating dynamic memory to your elements and passing these double-reference 
	pointers. The user must also provide a method of deallocating them (as it becomes the stack's responsibility 
	to deallocate these pointers).

	EXAMPLE 1: BASIC USAGE

 	stackNew(&s, elementSize, NULL);
	int numbers[PREALLOC_SIZE*2];

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		numbers[i] = i;
	}
	int* numberVector = numbers;

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}

	stackDispose(&s);

	EXAMPLE 2: STRING USAGE -- VARIABLE-LENGTH ELEMENT SIZES

 	const char* names[] = {"Armando", "Bonilha", "Cercei", "Dmitri", "Elnathan", "Fausto Renato", "Guilherme", "Heitor", "Illich"};

	Stack s;
	stackNew(&s, sizeof(char*), &stringDispose);

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		char* duplicate = strdup(names[i]);
		// double indirection
		stackPush(&s, &duplicate);
	}

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		char* name;
		stackPop(&s, &name);
	}

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		char* duplicate = strdup(names[i]);
		stackPush(&s, &duplicate);
	}
 
	stackDispose(&s);

**/


/** Defines preallocated number of elements when a stack is created */
#define PREALLOC_SIZE	4

// OBJECT

typedef struct {
	int _logicalLen;					///< size of elements stored
	int _allocLen;						///< allocated size (physical)
	void* _elements;					///< pointer to actual elements memory location
	int _elementSize;					///< size of each element
	void (*_dealocFunction)(void*);		///< function called when every element has to be dealocated
} Stack;

// METHODS

void stackNew(Stack *s, int elementSize, void (*dealocFunction)(void*));
void stackDispose(Stack *s);
void stackPush(Stack *s, void* elementAddress);
void stackPop(Stack *s, void* elementAddress);

// Auxiliary functions

void stringDispose(void* strPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */