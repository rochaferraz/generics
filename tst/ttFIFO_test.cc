#include "gtest/gtest.h"
#include "ttFIFO.h"
#include <cstring>

TEST(FIFO, 2Elements) {
	ttFifo_t fifo;
	ttFifoInit(&fifo, 10, 4);
	ASSERT_TRUE(ttFifoCapacity(&fifo) == 10);
	ASSERT_TRUE(ttFifoRemainingCapacity(&fifo) == 10);
	uint32_t a = 1234;
	uint32_t b = 4321;
	uint32_t c = 0;
	ttFifoPush(&fifo, &a);
	ttFifoPush(&fifo, &b);
	ASSERT_EQ(ttFifoRemainingCapacity(&fifo),8);
	ttFifoPop(&fifo, &c);
	ASSERT_EQ(c,1234);
	ttFifoPop(&fifo, &c);
	ASSERT_EQ(c,4321);
	ttFifoDeinit(&fifo);
}

TEST(FIFO, TooMany) {
	ttFifo_t fifo;
	ttFifoInit(&fifo, 10, 4);
	ASSERT_TRUE(ttFifoCapacity(&fifo) == 10);
	ASSERT_TRUE(ttFifoRemainingCapacity(&fifo) == 10);
	uint32_t a = 0;
	for (a = 1; a <= 10; a++) {
		ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 10 - a);
	}
	ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_Full);
	uint32_t b = 0;
	for (a = 1; a <= 10; a++) {
		ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), a);
		ASSERT_EQ(b, a);
	}
	ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_Empty);
	ttFifoDeinit(&fifo);
}

TEST(FIFO, Rollover) {
	ttFifo_t fifo;
	ttFifoInit(&fifo, 10, 4);
	ASSERT_TRUE(ttFifoCapacity(&fifo) == 10);
	ASSERT_TRUE(ttFifoRemainingCapacity(&fifo) == 10);
	uint32_t a = 0;
	for (a = 1; a <= 5; a++) {
		ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 10 - a);
	}
	uint32_t b = 0;
	for (a = 1; a <= 5; a++) {
		ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 5 + a);
	}
	for (a = 11; a <= 10000; a++) {
		ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_None);
		ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 10);
	}
	for (a = 11; a <= 20; a++) {
		ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 20 - a);
	}
	for (a = 11; a <= 20; a++) {
		ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), -10 + a);
	}

	ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_Empty);
	ttFifoDeinit(&fifo);
}

TEST(FIFO, Rollover2) {
	ttFifo_t fifo;
	ttFifoInit(&fifo, 10, 4);
	uint32_t a = 0;
	uint32_t b = 0;		
	for (a = 11; a <= 20; a++) {
		ASSERT_EQ(ttFifoPush(&fifo, &a), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), 20 - a);
	}
	for (a = 11; a <= 20; a++) {
		ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_None);
		ASSERT_EQ(ttFifoRemainingCapacity(&fifo), -10 + a);
	}

	ASSERT_EQ(ttFifoPop(&fifo, &b), ttErr_Empty);
	ttFifoDeinit(&fifo);
}