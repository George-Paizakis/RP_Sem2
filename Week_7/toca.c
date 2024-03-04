/**
******************************************************************************
 * @file: toca.c
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

/* Includes ------------------------------------------------------------------*/
#include "toca.h"

/* Global variables ----------------------------------------------------------*/
static UART_HandleTypeDef serialIO;

/**
 * @brief Initialise UART6 (PC6/7 TX/RX) for RS232 on Expansion Board
 * @param None
 * @retval None
 */

void init_serial_io()
{
/* Local Variables */
GPIO_InitTypeDef gpioInit;
/* Initialise Clocks */
__HAL_RCC_GPIOC_CLK_ENABLE();
__HAL_RCC_USART6_CLK_ENABLE();
/* Configure Pin Functionality */
gpioInit.Pin = GPIO_PIN_6 | GPIO_PIN_7;
gpioInit.Mode = GPIO_MODE_AF_PP;
gpioInit.Pull = GPIO_PULLUP;
gpioInit.Speed = GPIO_SPEED_FAST;
gpioInit.Alternate = GPIO_AF8_USART6;
HAL_GPIO_Init(GPIOC, &gpioInit);
/* Configure UART Functionality */
serialIO.Instance = USART6;
serialIO.Init.BaudRate = 115200;
serialIO.Init.WordLength = UART_WORDLENGTH_8B;
serialIO.Init.StopBits = UART_STOPBITS_1;
serialIO.Init.Parity = UART_PARITY_NONE;
serialIO.Init.Mode = UART_MODE_TX_RX;
serialIO.Init.HwFlowCtl = UART_HWCONTROL_NONE;
serialIO.Init.OverSampling = UART_OVERSAMPLING_16;
HAL_UART_Init(&serialIO);
}

int __io_getchar(void)
{
/* Local Variable */
int ch = 0;
/* Clear the Overrun flag just before receiving the first character */
__HAL_UART_CLEAR_OREFLAG(&serialIO);
/* Wait for reception of a character on the USART RX line and echo this
* character on console */
HAL_UART_Receive(&serialIO, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
if(ch == '\r')
{
HAL_UART_Transmit(&serialIO, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
ch = '\n';
}
HAL_UART_Transmit(&serialIO, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
return ch;
}

int __io_putchar(int ch)
{
HAL_UART_Transmit(&serialIO, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
return ch;
}
