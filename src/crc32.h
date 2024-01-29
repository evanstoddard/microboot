/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file crc32.h
 * @author Evan Stoddard
 * @brief CRC32 Implementation (Derived from Gary S. Brown's Implementation https://web.mit.edu/freebsd/head/sys/libkern/crc32.c)
 */

#ifndef CRC32_H_
#define CRC32_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Returns CRC32 value of given buffer
 * 
 */
uint32_t crc32(const void *buf, size_t size);

#ifdef __cplusplus
}
#endif
#endif /* CRC32_H_ */