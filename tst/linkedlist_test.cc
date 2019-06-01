#include "gtest/gtest.h"
#include "linkedlist.h"
#include <string.h>

TEST(LinkedList, IncreasesSizeInt) {

    LinkedList list;
    linkListNew(&list, sizeof(int), NULL);

	ASSERT_TRUE(list._allocLen == 0);
	ASSERT_TRUE(list._logicalLen == 0);
	ASSERT_TRUE(list._firstElement == NULL);
    ASSERT_TRUE(list._elementSize == sizeof(int));

	for (int i = 0; i < 100; i++) {
	    int j = malloc(int);
		linkedListInsert(&list, &j);
	}

	ASSERT_TRUE(list._logicalLen == 100);
	ASSERT_TRUE(list._allocLen == 100);
	ASSERT_TRUE(list._firstElement != NULL);
    ASSERT_TRUE(list._firstElement->contents == 0);
//
//    for (int i = 0; i < 100; i++) {
//        linkedListErase(&list);
//    }

//	ASSERT_TRUE(list._logicalLen == 0);
//	ASSERT_TRUE(list._allocLen == 0);
//    ASSERT_TRUE(list._firstElement == NULL);
//
//	linkedListDispose(&list);
}
