/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file microboot.h
 * @author Evan Stoddard
 * @brief Main MicroBoot module
 */

#ifndef MICROBOOT_H_
#define MICROBOOT_H_

#include <stdint.h>
#include <stdbool.h>
#include "flash_types.h"
#include "image_types.h"

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
 * @brief Initialize MicroBoot
 * 
 */
void microboot_init(flash_partition_t *flash_parts, uint8_t num_parts);

/**
 * @brief Attempt to load image
 * 
 * @param image Pointer to load image details into
 * @return true Able to load image
 * @return false Unable to load image
 */
bool microboot_boot(image_t *image);

#ifdef __cplusplus
}
#endif
#endif /* MICROBOOT_H_ */