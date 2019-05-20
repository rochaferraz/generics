#include "gtest/gtest.h"
#include "misc.h"

TEST(Stack, Swap) {
	int x = 1234;
	int y = 4321;

	swap(&x, &y, sizeof(x));

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}