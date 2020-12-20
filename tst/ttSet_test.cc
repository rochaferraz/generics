#include "gtest/gtest.h"
#include "ttSet.h"
#include <string.h>

#define SETUPEXAMPLE(elementSize) TTSet s;		\
	ttSetNew(&s, elementSize, NULL); 					\
	int numbers[PREALLOC_SIZE*2];   					\
	for (int i = 0; i < PREALLOC_SIZE*2; i++) {			\
		numbers[i] = i;									\
	}													\
	int* numberVector = numbers;

TEST(Set, IncreasesSizeInt) {
	SETUPEXAMPLE(sizeof(int));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSetSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSetSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	ttSetDispose(&s);
}

TEST(Set, IncreasesSizeLong) {
	SETUPEXAMPLE(sizeof(long));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSetSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		ttSetSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	ttSetDispose(&s);
}

TEST(Set, IntElementsCorrect) {
	TTSet s;
	ttSetNew(&s, sizeof(int), NULL);

	ASSERT_EQ(s._allocLen, PREALLOC_SIZE);
	ASSERT_EQ(s._logicalLen, 0);

    for (int i = 0; i < PREALLOC_SIZE*2; i++) {
        int* number = (int*) malloc(sizeof(int));
		*number = i;
		ASSERT_EQ(ttSetContainsPtr(&s, number, NULL), (void*)NULL);
		ASSERT_FALSE(ttSetContainsValue(&s, number, NULL));
        ttSetSaveAllocatedPtr(&s, number);
		ASSERT_EQ(*(int**)ttSetContainsPtr(&s, number, NULL), number);
		ASSERT_TRUE(ttSetContainsValue(&s, number, NULL));
        ttSetRemovePtr(&s, number);
        ASSERT_EQ(ttSetContainsPtr(&s, number, NULL), (void*)NULL);
        ASSERT_FALSE(ttSetContainsValue(&s, number, NULL));

        ttSetSaveCopy(&s, &i);
        ASSERT_TRUE(ttSetContainsValue(&s, &i, NULL));
	}

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		int* number = (int*) malloc(sizeof(int));
		*number = i;
		ASSERT_TRUE(ttSetContainsValue(&s, number, NULL));
        ttSetRemovePtr(&s, number);
		ASSERT_EQ(ttSetContainsPtr(&s, number, NULL), (void*)NULL);
	}

	ttSetDispose(&s);
}