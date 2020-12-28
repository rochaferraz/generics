/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

#ifndef TTLIB_H
#define TTLIB_H

/*
 * This file is used for including all headers from Tatulib Library
 */

typedef enum {
    ttErr_None = 0,
    ttErr_Full = -100,
    ttErr_Empty,
    ttErr_NotConfigured,
    ttErr_Unknown
} ttError_t;

#include <ttConfig.h>
#include <ttLinkedList.h>
#include <ttMemory.h>
#include <ttMiscArray.h>
#include <ttStack.h>
#include <ttUtil.h>
#include <ttFIFO.h>

#endif /* TTLIB_H */
