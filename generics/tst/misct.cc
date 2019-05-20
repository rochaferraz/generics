#include "gtest/gtest.h"
#include "misc.h"
#include <cstring>

TEST(Swap, Int) {
	int x = 1234;
	int y = 4321;

	swap(&x, &y, sizeof(x));

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}

TEST(Swap, Long) {
	long x = 1234;
	long y = 4321;

	swap(&x, &y, sizeof(x));

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}

TEST(Swap, StringPtrs) {
	char x[] = "James";
	char y[] = "Bond";

	swap(x, y, sizeof(x));

	ASSERT_TRUE(strcmp(x,"Bond") == 0);
	ASSERT_TRUE(strcmp(y,"James") == 0);		
}