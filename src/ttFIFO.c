#include <ttFIFO.h>
#include <string.h>
#include <stdio.h>

void ttFifoInit(ttFifo_t* fifo, size_t capacity, size_t sizeElement) {
    fifo->buffer = ttmalloc((capacity + 1)*sizeElement);
    fifo->bufferHead = fifo->buffer;
    fifo->bufferTail = fifo->buffer;
    fifo->elementSize = sizeElement;
    fifo->bufferMaxNumberElements = capacity;
}

void ttFifoDeinit(ttFifo_t* fifo) {
    if (fifo->buffer) {
        ttfree(fifo->buffer);
    }
}

size_t ttFifoCapacity(ttFifo_t* fifo) {
    // one less then max because we use ptr distance to calculate dynamic size
    return fifo->bufferMaxNumberElements;
}

size_t ttFifoRemainingCapacity(ttFifo_t* fifo) {
    return fifo->bufferMaxNumberElements - ttFifoSize(fifo);
}

size_t ttFifoSize(ttFifo_t* fifo) {
    if (fifo->bufferHead >= fifo->bufferTail) {
        return (fifo->bufferHead - fifo->bufferTail)/fifo->elementSize;
    } else {
        return fifo->bufferMaxNumberElements + 1 - (fifo->bufferTail - fifo->bufferHead)/fifo->elementSize;
    }
}

void* _ttFifoMaxPtr(ttFifo_t* fifo) {
    return fifo->buffer + fifo->bufferMaxNumberElements*fifo->elementSize;
}

ttError_t ttFifoPop(ttFifo_t* fifo, void *ptrOut) {
    if (ttFifoSize(fifo)) {
        memcpy(ptrOut, fifo->bufferTail, fifo->elementSize);
        fifo->bufferTail += fifo->elementSize;
        if (fifo->bufferTail > _ttFifoMaxPtr(fifo)) {
            fifo->bufferTail = fifo->buffer;
        }
        return ttErr_None;
    } else {
        return ttErr_Empty;
    }
}

ttError_t ttFifoPush(ttFifo_t* fifo, const void *const ptrIn) {
    if (ttFifoRemainingCapacity(fifo)) {
        memcpy(fifo->bufferHead, ptrIn, fifo->elementSize);
        fifo->bufferHead += fifo->elementSize;
        if (fifo->bufferHead > _ttFifoMaxPtr(fifo)) {
            fifo->bufferHead = fifo->buffer;
        }
        return ttErr_None;
    } else {
        return ttErr_Full;
    }
}
