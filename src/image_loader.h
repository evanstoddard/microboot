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
 * @brief Attempt to get image at partition
 * 
 * @param partition Image Partition
 * @param image Pointer to image struct to write image info to
 * @return true Able to find image at partition
 * @return false Unable to find image at partition
 */
bool image_loader_get_image_info(flash_partition_t *partition, image_t *image);

/**
 * @brief Check if image at partition is valid
 * 
 * @param partition Image partition
 * @param image Image struct
 * @return true Image is valid
 * @return false Image in not valid
 */
bool image_loader_validate_image(flash_partition_t *partition, image_t *image);

#ifdef __cplusplus
}
#endif
#endif /* IMAGE_LOADER_H_ */