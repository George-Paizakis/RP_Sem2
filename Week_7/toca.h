/**
******************************************************************************
 * @file: toca.h
 * @author: George Paizakis
 * @version: 1.0
 * @date: 05/02/2024
 * @brief: Initialise and implement functions for IO over UART
 *
 * using the RS232 serial port on the DM-STF-4BB
 * expansion board.
 *
 * A source file using these utilities to support stdio must also include:
 * @code <stdio.h>
 * in addition to this header.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Staffordshire University
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#ifndef SRC_TOCA_H_
#define SRC_TOCA_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Function prototypes (code generation followed by alphabetical) ------------*/
extern void init_serial_io(void);


#endif /* SRC_TOCA_H_ */
