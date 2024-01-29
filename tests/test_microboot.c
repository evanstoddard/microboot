/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tests_microboot.c
 * @author Evan Stoddard
 * @brief Microboot module tests
 */

#include "unity.h"

// Module under test
#include "microboot.h"
#include "microboot.c"

#include "mock_image_loader.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/
#define TEST_BOOTLOADER_ADDR 0x0U
#define TEST_BOOTLOADER_SIZE 0x8000U

#define TEST_PRIMARY_SLOT_ADDR (TEST_BOOTLOADER_ADDR + TEST_BOOTLOADER_SIZE)
#define TEST_PRIMARY_SLOT_SIZE 0x16000

#define TEST_SECONDARY_SLOT_ADDR (TEST_PRIMARY_SLOT_ADDR + TEST_PRIMARY_SLOT_SIZE)
#define TEST_SECONDARY_SLOT_SIZE 0x16000

/*****************************************************************************
 * Variables
 *****************************************************************************/
static flash_partition_t partitions[] = {
    {
        .type = FLASH_PARTITION_BOOTLOADER,
        .addr = TEST_BOOTLOADER_ADDR,
        .size = TEST_BOOTLOADER_SIZE
    },
    {
        .type = FLASH_PARTITION_SLOT_PRIMARY,
        .addr = TEST_PRIMARY_SLOT_ADDR,
        .size = TEST_PRIMARY_SLOT_SIZE
    },
    {
        .type = FLASH_PARTITION_SLOT_SECONDARY,
        .addr = TEST_SECONDARY_SLOT_ADDR,
        .size = TEST_SECONDARY_SLOT_SIZE
    },
};

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief Setup tests
 * 
 */
void setUp(void) {
    // Initialize microboot
    microboot_init(partitions, sizeof(partitions)/sizeof(flash_partition_t));
}

/**
 * @brief Teardown tests
 * 
 */
void tearDown(void) {
}

/**
 * @brief Test initialization of microboot
 * 
 */
void test_microboot_init(void) {
    TEST_ASSERT_EQUAL(microboot_inst.flash_parts, &partitions);
    TEST_ASSERT_EQUAL(microboot_inst.num_parts, sizeof(partitions)/sizeof(flash_partition_t));
}

/**
 * @brief Test if no partitions are configured
 * 
 */
void test_microboot_boot_no_partitions(void) {
    // Setup and Expectations
    flash_partition_t empty_partitions[] = {};
    microboot_init(empty_partitions, 0);

    // Test
    bool ret = microboot_boot(NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

/**
 * @brief Test if no primary partitions exist
 * 
 */
void test_microboot_boot_no_primary_partition(void) {
    // Setup and Expectations
    flash_partition_t no_primary_partitions[] = {
        {
            .type = FLASH_PARTITION_BOOTLOADER,
            .addr = TEST_BOOTLOADER_ADDR,
            .size = TEST_BOOTLOADER_SIZE
        },
        {
            .type = FLASH_PARTITION_SLOT_SECONDARY,
            .addr = TEST_SECONDARY_SLOT_ADDR,
            .size = TEST_SECONDARY_SLOT_SIZE
        },
    };
    microboot_init(no_primary_partitions, 2);
    
    // Test
    bool ret = microboot_boot(NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

/**
 * @brief Test if failed to get image info
 * 
 */
void test_microboot_boot_bad_image_info(void) {
    // Setup and Expectations
    image_loader_get_image_info_IgnoreAndReturn(false);
    
    // Test
    bool ret = microboot_boot(NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

/**
 * @brief Test if image validation fails
 * 
 */
void test_microboot_boot_validation_failed(void) {
    // Setup and Expectations
    image_t image;
    image_loader_get_image_info_IgnoreAndReturn(true);
    image_loader_validate_image_IgnoreAndReturn(false);

    // Test
    bool ret = microboot_boot(NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

/**
 * @brief Test a sucessful boot
 * 
 */
void test_microboot_boot_success(void) {
    // Setup and Expectations
    image_t image;
    image_loader_get_image_info_IgnoreAndReturn(true);
    image_loader_validate_image_IgnoreAndReturn(true);

    // Test
    bool ret = microboot_boot(&image);

    // Assertions
    TEST_ASSERT_TRUE(ret);
}

/**
 * @brief Test when no partitions exist
 * 
 */
void test_microboot_get_primary_partition_no_partitions(void) {
    // Setup and Expectations
    flash_partition_t empty_partitions[] = {};
    microboot_init(empty_partitions, 0);

    // Test
    flash_partition_t *ret = microboot_get_primary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, NULL);
}

/**
 * @brief Test when no primary partitions exist.
 * 
 */
void test_microboot_get_primary_partition_no_primary_partiton(void) {
    // Setup and Expectations
    flash_partition_t no_primary_partitions[] = {
        {
            .type = FLASH_PARTITION_BOOTLOADER,
            .addr = TEST_BOOTLOADER_ADDR,
            .size = TEST_BOOTLOADER_SIZE
        },
        {
            .type = FLASH_PARTITION_SLOT_SECONDARY,
            .addr = TEST_SECONDARY_SLOT_ADDR,
            .size = TEST_SECONDARY_SLOT_SIZE
        },
    };
    microboot_init(no_primary_partitions, 2);

    // Test
    flash_partition_t *ret = microboot_get_primary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, NULL);
}

/**
 * @brief Test when successfully able to get primary partition
 * 
 */
void test_microboot_get_primary_partition_success(void) {
    // Setup and Expectations

    // Test
    flash_partition_t *ret = microboot_get_primary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, &partitions[1]);
}

/**
 * @brief Test when no partitions exist
 * 
 */
void test_microboot_get_secondary_partition_no_partitions(void) {
    // Setup and Expectations
    flash_partition_t empty_partitions[] = {};
    microboot_init(empty_partitions, 0);

    // Test
    flash_partition_t *ret = microboot_get_secondary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, NULL);
}

/**
 * @brief Test when no secondary partitions exist
 * 
 */
void test_microboot_get_secondary_partition_no_secondary_partiton(void) {
    // Setup and Expectations
    flash_partition_t no_secondary_partitions[] = {
        {
            .type = FLASH_PARTITION_BOOTLOADER,
            .addr = TEST_BOOTLOADER_ADDR,
            .size = TEST_BOOTLOADER_SIZE
        },
        {
            .type = FLASH_PARTITION_SLOT_PRIMARY,
            .addr = TEST_PRIMARY_SLOT_ADDR,
            .size = TEST_PRIMARY_SLOT_SIZE
        },
    };
    microboot_init(no_secondary_partitions, 2);

    // Test
    flash_partition_t *ret = microboot_get_secondary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, NULL);
}

/**
 * @brief Test when successfully able to get secondary partition
 * 
 */
void test_microboot_get_secondary_partition_success(void) {
    // Setup and Expectations

    // Test
    flash_partition_t *ret = microboot_get_secondary_partition();

    // Assertions
    TEST_ASSERT_EQUAL(ret, &partitions[2]);
}
