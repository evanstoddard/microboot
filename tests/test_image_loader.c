/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file test_image_loader.c
 * @author Evan Stoddard
 * @brief Test image loader interface
 */

#include "unity.h"
#include "image_loader.h"
#include "image_loader.c"
#include "mock_flash_interface.h"
#include "mock_crc32.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

void setUp(void) {

}

void tearDown(void) {

}

void test_image_loader_get_image_header(void) {
    // Setup and Expectations
    image_t image;

    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    flash_interface_flash_read_Expect(partition.addr, &image.header, sizeof(image_header_t));

    // Test
    image_loader_get_image_header(&partition, &image);

    // Assertions
}

void test_image_loader_get_image_footer(void) {
    // Setup and Expectations
    image_t image;
    image.header.image_size = 0x4200;

    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    flash_interface_flash_read_Expect(
        0xCAFED00D + sizeof(image_header_t) + 0x4200, 
        &image.footer, 
        sizeof(image_footer_t)
    );

    // Test
    image_loader_get_image_footer(&partition, &image);

    // Assertions
}

void test_image_loader_validate_image_crc_no_partition(void) {
    // Setup and Expectations
    image_t image;
    
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    // Test
    bool ret = image_loader_validate_image_crc(NULL, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_validate_image_crc_no_image(void) {
    // Setup and Expectations
    image_t image;
    
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    // Test
    bool ret = image_loader_validate_image_crc(&partition, NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_validate_image_crc_bad_crc(void) {
    // Setup and Expectations
    image_t image;
    image.image_start = (uint32_t*)0x4242;
    image.header.image_size = 0x1000;
    
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    crc32_ExpectAndReturn((void *)image.image_start, image.header.image_size, false);

    // Test
    bool ret = image_loader_validate_image_crc(&partition, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_validate_image_crc_success(void) {
    // Setup and Expectations
    image_t image;
    image.image_start = (uint32_t*)0x4242;
    image.header.image_size = 0x1000;
    
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    crc32_ExpectAndReturn((void *)image.image_start, image.header.image_size, true);

    // Test
    bool ret = image_loader_validate_image_crc(&partition, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_get_image_info_no_image(void) {
    // Setup and Expectations
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    // Test
    bool ret = image_loader_get_image_info(&partition, NULL);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_get_image_info_bad_header_magic(void) {
    // Setup and Expectations
    flash_partition_t partition = {
        .addr = 0xCAFED00D
    };

    image_t image;
    image.header.magic = 0xBADBEEF;

    flash_interface_flash_read_Expect(partition.addr, &image.header, sizeof(image_header_t));

    // Test
    bool ret = image_loader_get_image_info(&partition, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_get_image_info_bad_image_size(void) {
    // Setup and Expectations
    flash_partition_t partition = {
        .addr = 0xCAFED00D,
        .size = 0x3000
    };

    image_t image;
    image.header.magic = MICROBOOT_IMAGE_HEADER_MAGIC;
    image.header.image_size = 0x4200;

    flash_interface_flash_read_Expect(partition.addr, &image.header, sizeof(image_header_t));

    // Test
    bool ret = image_loader_get_image_info(&partition, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_get_image_info_bad_footer_magic(void) {
    // Setup and Expectations
    flash_partition_t partition = {
        .addr = 0xCAFED00D,
        .size = 0x9000
    };

    image_t image;
    image.header.magic = MICROBOOT_IMAGE_HEADER_MAGIC;
    image.header.image_size = 0x4200;

    image.footer.magic = 0xBADCAFE;

    flash_interface_flash_read_Expect(partition.addr, &image.header, sizeof(image_header_t));
    flash_interface_flash_read_Expect(
        partition.addr + 0x4200 + sizeof(image_header_t), 
        &image.footer, 
        sizeof(image_footer_t)
    );

    // Test
    bool ret = image_loader_get_image_info(&partition, &image);

    // Assertions
    TEST_ASSERT_FALSE(ret);
}

void test_image_loader_get_image_info_success(void) {
    // Setup and Expectations
    flash_partition_t partition = {
        .addr = 0xCAFED00D,
        .size = 0x9000
    };

    image_t image;
    image.header.magic = MICROBOOT_IMAGE_HEADER_MAGIC;
    image.header.image_size = 0x4200;

    image.footer.magic = MICROBOOT_IMAGE_FOOTER_MAGIC;

    flash_interface_flash_read_Expect(partition.addr, &image.header, sizeof(image_header_t));
    flash_interface_flash_read_Expect(
        partition.addr + 0x4200 + sizeof(image_header_t), 
        &image.footer, 
        sizeof(image_footer_t)
    );

    // Test
    bool ret = image_loader_get_image_info(&partition, &image);

    // Assertions
    TEST_ASSERT_TRUE(ret);
}

