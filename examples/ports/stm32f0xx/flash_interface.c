/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flash_interface.c
 * @author Evan Stoddard
 * @brief Example flash interface for stm32f0xx
 */

#include <stdint.h>
#include <string.h>
#include "stm32f0xx.h"
#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_flash_ex.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/**
 * @brief While reads are memory mapped to 0x0, flash starts at 0x08000000
 * 
 */
#define FLASH_WRITE_OFFSET 0x08000000U

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

void flash_interface_flash_erase(uint32_t addr, uint32_t size) {
    // Unlock flash
    HAL_FLASH_Unlock();

    // Create erase structure
    FLASH_EraseInitTypeDef erase_struct;
    erase_struct.PageAddress = FLASH_WRITE_OFFSET + addr;
    erase_struct.NbPages = size;
    erase_struct.TypeErase = FLASH_TYPEERASE_PAGES;

    uint32_t page_error;

    // Erase flash
    HAL_FLASHEx_Erase(&erase_struct, &page_error);

    // Lock flash
    HAL_FLASH_Lock();
}

void flash_interface_flash_read(uint32_t addr, void *dst, uint32_t size) {
    // Since flash reads are memory mapped to 0x0 we can just
    // memcpy
    uint32_t *src = (uint32_t *)addr;
    memcpy(dst, src, size);
}

void flash_interface_flash_write(uint32_t addr, void *src, uint32_t size) {
    // Unlock flash
    HAL_FLASH_Unlock();

    uint16_t *buf = (uint16_t *)src;

    // Write bytes to flash
    for (uint32_t i = 0; i < size; i++) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FLASH_WRITE_OFFSET + addr + (i * 2) , buf[i]);
    }

    // Lock flash
    HAL_FLASH_Unlock();
}