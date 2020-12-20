#include "gtest/gtest.h"
#include "ttLinkedList.h"
#include "ttMemory.h"
#include <string.h>
#include <stdio.h>

TEST(LinkedList, IncreasesSizeInt) {

//    LinkedList list;
//    linkedListNew(&list, sizeof(int), NULL);
//
//	ASSERT_TRUE(list._allocLen == 0);
//	ASSERT_TRUE(list._logicalLen == 0);
//	ASSERT_TRUE(list._firstElement == NULL);
//    ASSERT_TRUE(list._elementSize == sizeof(int));
//
//	for (int i = 0; i < 10; i++) {
//	    int* j = (int*)malloc(sizeof(int));
//	    *j = i;
//		linkedListInsert(&list, j);
//	}
//
//	ASSERT_TRUE(list._logicalLen == 10);
//	ASSERT_TRUE(list._allocLen == 10);
//	ASSERT_TRUE(list._firstElement != NULL);

//	LinkedListNode* node = list._firstElement;
//	for (int i = 0; i < 10; i++) {
//		ASSERT_TRUE(*(int*)node->contents == i);
//		node = (LinkedListNode*)node->_next;
//	}
//	printf("Memory use: %ld\n", ttgetMemoryUse());
//    ASSERT_TRUE(ttgetMemoryUse() == 10*(3*sizeof(char*) + sizeof(int))); // next ptr, previous ptr, contents ptr, contents
//
//    for (int i = 0; i < 10; i++) {
//        linkedListErase(&list);
//    }
//
//	printf("Memory use: %ld\n", ttgetMemoryUse());

//	ASSERT_TRUE(list._logicalLen == 0);
//	ASSERT_TRUE(list._allocLen == 0);
//	ASSERT_TRUE(ttgetMemoryUse() == false);

//    ASSERT_TRUE(list._firstElement == NULL);
//
//	linkedListDispose(&list);

//	ttmemoryDispose();
}
