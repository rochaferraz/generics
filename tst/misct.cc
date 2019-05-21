#include "gtest/gtest.h"
#include "misc.h"
#include <cstring>
#include <stdio.h>

TEST(Swap, Int) {
	int x = 1234;
	int y = 4321;

	printf("Sizeof: %d\n", sizeof(x));
	printf("Sizeof: %d\n", sizeof(y));

	//printf("%d\n", SAME_TYPES(long, long long));

	sswap(&x, &y);

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}

TEST(Swap, Long) {
	long x = 1234;
	long y = 4321;

	//swap(&x, &y, sizeof(x));

	//ASSERT_TRUE(x == 4321);
	//ASSERT_TRUE(y == 1234);		
}

TEST(Swap, StringPtrs) {
	char x[] = "James";
	char y[] = "Bond";

	//swap(x, y, sizeof(x));

	//ASSERT_TRUE(strcmp(x,"Bond") == 0);
	//ASSERT_TRUE(strcmp(y,"James") == 0);		
}