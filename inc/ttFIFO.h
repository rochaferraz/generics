/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
 **/

#ifndef TT_FIFO_H
#define TT_FIFO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
    void *buffer;
    size_t bufferMaxNumberElements;
    size_t elementSize; ///< number of bytes in element
    void *bufferHead;
    void *bufferTail;
} ttFifo_t;

/// Initializes a fifo struct with `size` elements. Allocates dynamic memory for buffer
void ttFifoInit(ttFifo_t *fifo, size_t capacity, size_t sizeElement);
/// Deinitializes a fifo struct. Clear up dynamic allocation
void ttFifoDeinit(ttFifo_t *fifo);

/// Returns maximum number of elements FIFO holds
size_t ttFifoCapacity(ttFifo_t *fifo);
/// Returns free bytes
size_t ttFifoRemainingCapacity(ttFifo_t *fifo);
/// Returns current number of elements in FIFO
size_t ttFifoSize(ttFifo_t *fifo);
/// Gets next byte from FIFO tail.
/// @param byteOut byte from FIFO
/// @return
ttError_t ttFifoPop(ttFifo_t *fifo, void *ptrOut);
/// Pushes byte to FIFO head.
/// @param byteIn byte to put on FIFO
/// @returnReturns number of bytes in Fifo after operation
ttError_t ttFifoPush(ttFifo_t *fifo, const void *const ptrIn);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //TT_FIFO_H
