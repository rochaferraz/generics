#include <ttStack.h>
#include <assert.h>
#include <stdlib.h>
#include "ttConfig.h"
#include "ttMemory.h"

void stackNew(Stack* s, int elementSize, void (*dealocFunction)(void*)) {
	assert(s != NULL);
	assert(elementSize > 0);
	s->_elementSize = elementSize;
	s->_logicalLen = 0;
	s->_allocLen = PREALLOC_SIZE;
	s->_elements = ttrealloc(0, PREALLOC_SIZE * elementSize);
	s->_dealocFunction = dealocFunction;
	assert(s->_elements != NULL);
}

void stackDispose(Stack* s) {
	assert(s != NULL);
	if (s->_dealocFunction != NULL) {
		while(s->_logicalLen > 0) {
			void* element;
			stackPop(s, element);
		}
	}
	s->_allocLen = 0;
	s->_logicalLen = 0;
	s->_dealocFunction = NULL;
	ttfree(s->_elements);
}

void stackGrow(Stack* s) {
	s->_allocLen *= 2;
	s->_elements = ttrealloc(s->_elements, s->_allocLen * s->_elementSize);
	assert(s->_elements != NULL);
}

void stackPush(Stack* s, void* elementAddress) {
	assert(s != NULL);
	// doubles if we reach the size of the allocated stack
	if (s->_logicalLen == s->_allocLen) {
		stackGrow(s);
	}
	void* target = (char*) s->_elements + s->_logicalLen * s->_elementSize;
	ttmemcpy(target, elementAddress, s->_elementSize);
	s->_logicalLen++;
}

void stackPop(Stack *s, void* elementAddress) {
	assert(s != NULL);
	assert(elementAddress != NULL);
	assert(s->_logicalLen > 0);
	s->_logicalLen--;
	void* source = (char *) s->_elements + s->_logicalLen * s->_elementSize;
	ttmemcpy(elementAddress, source, s->_elementSize);
	if (s->_dealocFunction != NULL) {
		s->_dealocFunction(source);
	}
}

void stringDispose(void* strPtr) {
	// we store double indirection pointers on the stack
	ttfree(*(char**)strPtr);
}