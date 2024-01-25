/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file image_loader.h
 * @author Evan Stoddard
 * @brief Handles loading and validating images
 */

#ifndef IMAGE_LOADER_H_
#define IMAGE_LOADER_H_

#include <stdbool.h>
#include "image_types.h"
#include "flash_types.h"

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
 * @brief Attempt to load image info from partition
 * 
 */
bool image_loader_get_image_info(flash_partition_t *partition, image_t *image);

#ifdef __cplusplus
}
#endif
#endif /* IMAGE_LOADER_H_ */