#include "gtest/gtest.h"
#include "misc.h"
#include <cstring>

TEST(Swap, Int) {
	int x = 1234;
	int y = 4321;

	swap_int(&x, &y);

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}

TEST(Swap, Long) {
	long x = 1234;
	long y = 4321;

	swap_long(&x, &y);

	ASSERT_TRUE(x == 4321);
	ASSERT_TRUE(y == 1234);		
}

TEST(Swap, StringPtrs) {
	char x[] = "James";
	char y[] = "Bond";
	char* xl = x;
	char* yl = y;

	ASSERT_TRUE(strcmp(xl, "James") == 0);
	ASSERT_TRUE(strcmp(yl, "Bond") == 0);		

	swap_strptr(x, y);

	ASSERT_TRUE(strcmp(x, "Bond") == 0);
	ASSERT_TRUE(strcmp(y, "James") == 0);		

	swap_strptr(xl, yl);

	//ASSERT_TRUE(strcmp(xl, "Bond") == 0);
	//ASSERT_TRUE(strcmp(yl, "James") == 0);		

	swap_strptr(xl, yl);

	ASSERT_TRUE(strcmp(xl, "James") == 0);
	ASSERT_TRUE(strcmp(yl, "Bond") == 0);		
}