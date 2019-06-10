#include "gtest/gtest.h"
#include "ttswissCheese.h"
#include <string.h>

#define SETUPEXAMPLE(elementSize) TTSwissCheese s;		\
	ttSwissNew(&s, elementSize, NULL); 					\
	int numbers[PREALLOC_SIZE*2];   					\
	for (int i = 0; i < PREALLOC_SIZE*2; i++) {			\
		numbers[i] = i;									\
	}													\
	int* numberVector = numbers;

TEST(SwissCheese, IncreasesSizeInt) {
	SETUPEXAMPLE(sizeof(int));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSwissSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSwissSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	ttSwissDispose(&s);
}

TEST(SwissCheese, IncreasesSizeLong) {
	SETUPEXAMPLE(sizeof(long));

	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._logicalLen == 0);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
        ttSwissSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE);

	for (int i = 0; i < PREALLOC_SIZE; i++) {
		ttSwissSaveAllocatedPtr(&s, numberVector);
		numberVector++;
	}

	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE*2);
	ASSERT_TRUE(s._allocLen == PREALLOC_SIZE*2);

	ttSwissDispose(&s);
}

TEST(SwissCheese, IntElementsCorrect) {
	TTSwissCheese s;
	ttSwissNew(&s, sizeof(int), NULL);

	ASSERT_EQ(s._allocLen, PREALLOC_SIZE);
	ASSERT_EQ(s._logicalLen, 0);

    for (int i = 0; i < PREALLOC_SIZE*2; i++) {
        int* number = (int*) malloc(sizeof(int));
		*number = i;
		ASSERT_EQ(ttSwissContainsPtr(&s, number, NULL), (void*)NULL);
		ASSERT_FALSE(ttSwissContainsValue(&s, number, NULL));
        ttSwissSaveAllocatedPtr(&s, number);
		ASSERT_EQ(*(int**)ttSwissContainsPtr(&s, number, NULL), number);
		ASSERT_TRUE(ttSwissContainsValue(&s, number, NULL));
        ttSwissRemovePtr(&s, number);
        ASSERT_EQ(ttSwissContainsPtr(&s, number, NULL), (void*)NULL);
        ASSERT_FALSE(ttSwissContainsValue(&s, number, NULL));

        ttSwissSaveCopy(&s, &i);
        ASSERT_TRUE(ttSwissContainsValue(&s, &i, NULL));
	}

	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		int* number = (int*) malloc(sizeof(int));
		*number = i;
		ASSERT_TRUE(ttSwissContainsValue(&s, number, NULL));
        ttSwissRemovePtr(&s, number);
		ASSERT_EQ(ttSwissContainsPtr(&s, number, NULL), (void*)NULL);
	}

	ttSwissDispose(&s);
}