#include <ttFIFO.h>

void ttFifoInit(ttFifo_t* fifo, size_t size) {
    fifo->buffer = ttmalloc(size);
    fifo->bufferHead = fifo->buffer;
    fifo->bufferTail = fifo->buffer;
    fifo->bufferMaxSize = size;
}

void ttFifoDeinit(ttFifo_t* fifo) {
    if (fifo->buffer) {
        ttfree(fifo->buffer);
    }
}

size_t ttFifoMax(ttFifo_t* fifo) {
    // one less then max because we use ptr distance to calculate dynamic size
    return fifo->bufferMaxSize - 1;
}

size_t ttFifoFree(ttFifo_t* fifo) {
    if (fifo->bufferHead >= fifo->bufferTail) {
        return fifo->bufferMaxSize - (fifo->bufferHead - fifo->bufferTail) - 1;
    } else {
        return (fifo->bufferTail - fifo->bufferHead) - 1;
    }
}

size_t ttFifoSize(ttFifo_t* fifo) {
    return fifo->bufferMaxSize - ttFifoFree(fifo);
}

uint8_t* _ttFifoMaxPtr(ttFifo_t* fifo) {
    return fifo->buffer + fifo->bufferMaxSize - 1;
}

ttError_t ttFifoPop(ttFifo_t* fifo, uint8_t *byteOut) {
    if (ttFifoSize(fifo)) {
        *byteOut = *fifo->bufferTail;
        fifo->bufferTail++;
        if (fifo->bufferTail > _ttFifoMaxPtr(fifo)) {
            fifo->bufferTail = fifo->buffer;
        }
        return ttErr_None;
    } else {
        return ttErr_Empty;
    }
}

ttError_t ttFifoPush(ttFifo_t* fifo, uint8_t *const byteIn) {
    if (ttFifoFree(fifo)) {
        *fifo->bufferHead = *byteIn;
        fifo->bufferHead++;
        if (fifo->bufferHead > _ttFifoMaxPtr(fifo)) {
            fifo->bufferHead = fifo->buffer;
        }
        return ttErr_None;
    } else {
        return ttErr_Full;
    }
}
