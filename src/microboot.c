/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file microboot.c
 * @author Evan Stoddard
 * @brief Main MicroBoot module
 */

#include <stddef.h>
#include "microboot.h"
#include "image_loader.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief MicroBoot instance typedef
 * 
 */
typedef struct microboot_inst_t {
    flash_partition_t *flash_parts;
    uint8_t num_parts;
} microboot_inst_t;

/*****************************************************************************
 * Variables
 *****************************************************************************/

/**
 * @brief MicroBoot instance
 * 
 */
static microboot_inst_t microboot_inst;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Find and return pointer to primary partition
 * 
 * @return flash_partition_t* 
 */
static flash_partition_t* microboot_get_primary_partition(void);

/**
 * @brief Find and return pointer to secondary partition
 * 
 * @return flash_partition_t* 
 */
static flash_partition_t* microboot_get_secondary_partition(void);

/*****************************************************************************
 * Functions
 *****************************************************************************/

void microboot_init(flash_partition_t *flash_parts, uint8_t num_parts) {
    // Initialize partition information
    microboot_inst.flash_parts = flash_parts;
    microboot_inst.num_parts = num_parts;
}

bool microboot_boot(image_t *image) {
    // Get primary partition
    flash_partition_t *primary_partition = microboot_get_primary_partition();
    if (!primary_partition)
        return false;
    
    // Attempt to get primary image info
    if (!image_loader_get_image_info(primary_partition, image))
        return false;


    // Return whether primary partition has a valid image
    return image_loader_validate_image(primary_partition, image);
}

flash_partition_t* microboot_get_primary_partition(void) {
    // Iterate through partitions and return if found
    for (uint8_t i = 0; i < microboot_inst.num_parts; i++) {
        if (microboot_inst.flash_parts[i].type == FLASH_PARTITION_SLOT_PRIMARY)
            return &microboot_inst.flash_parts[i];
    }

    return NULL;
}

flash_partition_t* microboot_get_secondary_partition(void) {
    // Iterate through partitions and return if found
    for (uint8_t i = 0; i < microboot_inst.num_parts; i++) {
        if (microboot_inst.flash_parts[i].type == FLASH_PARTITION_SLOT_SECONDARY)
            return &microboot_inst.flash_parts[i];
    }

    return NULL;
}