/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file image_types.h
 * @author Evan Stoddard
 * @brief Typedefs for images
 */

#ifndef IMAGE_TYPES_H_
#define IMAGE_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Image header typedef
 * 
 */
typedef struct image_header_t {
    uint32_t magic;
    uint32_t image_size;
    uint16_t version_major;
    uint16_t version_minor;
    uint16_t version_patch;
} image_header_t;

/**
 * @brief Image footer typedef
 * 
 */
typedef struct image_footer_t {
    uint32_t magic;
} typedef_footer_t;

/**
 * @brief Image typedef
 * 
 */
typedef struct image_t {
    image_header_t header;
    uint32_t pc;
    uint32_t sp;
    image_footer_t footer;
} image_footer_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* IMAGE_TYPES_H_ */