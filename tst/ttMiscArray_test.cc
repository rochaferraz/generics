#include "gtest/gtest.h"
#include "ttMiscArray.h"
#include "ttUtil.h"
#include <string.h>

TEST(SearchArray, Int) {
	int fibonacci[] = {1, 2, 3, 5, 8, 13, 21};
	int key = 5;
	int key2 = 4;

	unsigned long idx;
	void* ptr = searchArrayPtr(&key, fibonacci, ARRAY_SIZE(fibonacci), sizeof(key), &compareInt, &idx);
	ASSERT_EQ(ptr, &fibonacci[3]);
	ASSERT_EQ(idx, 3);

	ptr = searchArrayPtr(&key2, fibonacci, ARRAY_SIZE(fibonacci), sizeof(key2), &compareInt, &idx);
	ASSERT_EQ(ptr, (int*)NULL);
	ASSERT_EQ(idx, ARRAY_SIZE(fibonacci));
}

TEST(SearchArray, String) {
	const char* names[] = {"Armando", "Bonilha", "Cercei", "Dmitri", "Elnathan", "Faust"};
	const char* key = "Cercei";
	const char* key2 = "Zulmira";

	unsigned long idx;
	void* ptr = searchArrayPtr(&key, names, ARRAY_SIZE(names), sizeof(key), &compareStr, &idx);
	ASSERT_EQ(ptr, &names[2]);
	ASSERT_EQ(idx, 2);

	ptr = searchArrayPtr(&key2, names, ARRAY_SIZE(names), sizeof(key2), &compareStr, &idx);
	ASSERT_EQ(ptr, (int*)NULL);
	ASSERT_EQ(idx, ARRAY_SIZE(names));
}

TEST(SearchArray, Long) {
	long fibonacci[] = {1, 2, 3, 5, 8, 13, 21};
	long key = 5;
	long key2 = 4;

	unsigned long idx;
	void* ptr = searchArrayPtr(&key, fibonacci, ARRAY_SIZE(fibonacci), sizeof(key), &compareLong, &idx);
	ASSERT_TRUE(ptr == &fibonacci[3]);
	ASSERT_TRUE(idx == 3);

	ptr = searchArrayPtr(&key2, fibonacci, ARRAY_SIZE(fibonacci), sizeof(key2), &compareLong, &idx);
	ASSERT_TRUE(ptr == NULL);
	ASSERT_TRUE(idx == sizeof(fibonacci)/sizeof(key2));
}