/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file start_app.h
 * @author Evan Stoddard
 * @brief 
 */

#ifndef START_APP_H_
#define START_APP_H_

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

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Function to kick into loaded application
 * 
 * @param pc Program Counter
 * @param sp Stack Pointer
 */
void start_app(uint32_t pc, uint32_t sp);

#ifdef __cplusplus
}
#endif
#endif /* START_APP_H_ */