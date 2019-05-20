#include "gtest/gtest.h"
#include "stack.h"

TEST(Stack, IncreasesSize) {
	Stack s;
	stackNew(&s, sizeof(int));
	ASSERT_TRUE(s._allocLen == 0);
	ASSERT_TRUE(s._logicalLen == PREALLOC_SIZE);
	int numbers[PREALLOC_SIZE*2];
	for (int i = 0; i < PREALLOC_SIZE*2; i++) {
		numbers[i] = i;
	}	
	int* numberVector = numbers;

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

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}