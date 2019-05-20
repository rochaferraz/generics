#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

void stackNew(Stack* s, int elementSize) {
	assert(s != NULL);
	assert(elementSize > 0);
	s->_elementSize = elementSize;
	s->_logicalLen = 0;
	s->_allocLen = PREALLOC_SIZE;
	s->_elements = realloc(0, PREALLOC_SIZE * elementSize);
	assert(s->_elements != NULL);
}

void stackDispose(Stack* s) {
	assert(s != NULL);
	free(s->_elements);
}

void stackGrow(Stack* s) {
	s->_allocLen *= 2;
	s->_elements = realloc(s->_elements, s->_allocLen * s->_elementSize);
	assert(s->_elements != NULL);
}

void stackPush(Stack* s, void* elementAddress) {
	assert(s != NULL);
	// doubles if we reach the size of the allocated stack
	if (s->_logicalLen == s->_allocLen) {
		stackGrow(s);
	}
	void* target = (char*) s->_elements + s->_logicalLen * s->_elementSize;
	memcpy(target, elementAddress, s->_elementSize);
	s->_logicalLen++;
}

void stackPop(Stack *s, void* elementAddress) {
	assert(s != NULL);
	assert(elementAddress != NULL);
	assert(s->_logicalLen > 0);
	s->_logicalLen--;
	void* source = (char *) s->_elements + s->_logicalLen * s->_elementSize;
	memcpy(elementAddress, source, s->_elementSize);
}