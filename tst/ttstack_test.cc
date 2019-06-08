#include "gtest/gtest.h"
#include "ttstack.h"
#include <string.h>

#define SETUPEXAMPLE(elementSize) Stack s; 				\
	stackNew(&s, elementSize, NULL);   					\
	int numbers[PREALLOC_SIZE*2];   					\
	for (int i = 0; i < PREALLOC_SIZE*2; i++) {			\
		numbers[i] = i;									\
	}													\
	int* numberVector = numbers;

TEST(Stack, IncreasesSizeInt) {
	SETUPEXAMPLE(sizeof(int));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	stackDispose(&s);
}

TEST(Stack, IncreasesSizeLong) {
	SETUPEXAMPLE(sizeof(long));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	stackDispose(&s);
}

TEST(Stack, IntElementsCorrect) {
	SETUPEXAMPLE(sizeof(int));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		stackPush(&s, numberVector);
		numberVector++;
	}

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		int popNumber;
		stackPop(&s, &popNumber);
		ASSERT_TRUE(popNumber == numbers[PREALLOC_SIZE*2-1-i]);
	}
	ASSERT_TRUE(s._logicalLen == 0);
	ASSERT_TRUE(s._allocLen == 2*PREALLOC_SIZE);

	stackDispose(&s);
}

TEST(Stack, StringElementsCorrect) {
	const char* names[] = {"Armando", "Bonilha", "Cercei", "Dmitri", "Elnathan", "Fausto Renato", "Guilherme", "Heitor", "Illich"};

	Stack s;
	stackNew(&s, sizeof(char*), &stringDispose);

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		char* duplicate = strdup(names[i]);
		// double indirection
		stackPush(&s, &duplicate);
	}

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		char* name;
		stackPop(&s, &name);
		ASSERT_TRUE(strcmp(name, names[PREALLOC_SIZE*2-1-i]) == 0);
	}

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		char* duplicate = strdup(names[i]);
		stackPush(&s, &duplicate);
	}

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);

	stackDispose(&s);

	ASSERT_TRUE(s._logicalLen == 0);
	ASSERT_TRUE(s._allocLen == 0);
}