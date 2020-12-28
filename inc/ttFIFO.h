/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
 **/

#ifndef TT_FIFO_H
#define TT_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tt.h"

typedef struct {
    uint8_t *buffer;
    size_t bufferMaxSize;
    uint8_t *bufferHead;
    uint8_t *bufferTail;
} ttFifo_t;

/// Initializes a fifo struct. Allocates dynamic memory for buffer
void ttFifoInit(ttFifo_t *fifo, size_t size);
/// Deinitializes a fifo struct. Clear up dynamic allocation
void ttFifoDeinit(ttFifo_t *fifo);

/// Returns maximum number of bytes FIFO holds
size_t ttFifoMax(ttFifo_t *fifo);
/// Returns free bytes
size_t ttFifoFree(ttFifo_t *fifo);
/// Returns current number of bytes in FIFO
size_t ttFifoSize(ttFifo_t *fifo);
/// Gets next byte from FIFO tail.
/// @param byteOut byte from FIFO
/// @return
ttError_t ttFifoPop(ttFifo_t *fifo, uint8_t *byteOut);
/// Pushes byte to FIFO head.
/// @param byteIn byte to put on FIFO
/// @returnReturns number of bytes in Fifo after operation
ttError_t ttFifoPush(ttFifo_t *fifo, uint8_t *const byteIn);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //TT_FIFO_H
