/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file image_loader.c
 * @author Evan Stoddard
 * @brief Handles loading and validating images
 */

#include <stdbool.h>
#include "image_loader.h"
#include "flash_interface.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Get image header from partition
 * 
 * @param partition Partition
 * @param image Image to read data into
 */
static void image_loader_get_image_header(flash_partition_t *partition, image_t *image);

/**
 * @brief Get image footer from partition
 * 
 * @param partition Partition
 * @param image Image to read data into
 */
static void image_loader_get_image_footer(flash_partition_t *partition, image_t *image);

/*****************************************************************************
 * Functions
 *****************************************************************************/

bool image_loader_get_image_info(flash_partition_t *partition, image_t *image) {    
    if (!image)
        return false;

    // Get image header
    image_loader_get_image_header(partition, image);

    // Check if magic value is correct
    if (image->header.magic != MICROBOOT_IMAGE_HEADER_MAGIC) {
        return false;
    }

    // Ensure reported image size is not larger than partition
    uint32_t total_size = image->header.image_size;
    total_size += sizeof(image_header_t);
    total_size += sizeof(image_footer_t);
    if (total_size > partition->size) {
        return false;
    }

    // Get image footer
    image_loader_get_image_footer(partition, image);

    // Check if magic value is correct
    if (image->footer.magic != MICROBOOT_IMAGE_FOOTER_MAGIC) {
        return false;
    }

    // Calculate start address of image
    image->image_start = (uint32_t *)(partition->addr + sizeof(image_header_t));

    return true;
}

void image_loader_get_image_header(flash_partition_t *partition, image_t *image) {
    flash_interface_flash_read(partition->addr, &image->header, sizeof(image_header_t));
}

void image_loader_get_image_footer(flash_partition_t *partition, image_t *image) {
    // Calculate offset to footer
    uint32_t offset = partition->addr;
    offset += sizeof(image_header_t);
    offset += image->header.image_size;

    // Get reader footer from partition
    flash_interface_flash_read(offset, &image->footer, sizeof(image_footer_t));
}