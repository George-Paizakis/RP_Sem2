/**
  ******************************************************************************
  * @file           : main.c
  * @author			: <George Paizakis>
  * @version		: 1.0
  * @date			: <05/02/2024>
  * @brief          : Main program body
  *
  * All additional configuration and implementation of features must be
  * implemented by the developer. Comments will need to be updated to include
  * the correct names, descriptions, and dates.
  *
  * Parameters may need to be changed for function prototypes and definitions
  * to correctly pass data for any process.
  *
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


/* Definitions ---------------------------------------------------------------*/
/* Type Definitions ----------------------------------------------------------*/
typedef enum { STATE_ANTICLOCKWISE, STATE_CLOCKWISE, STATE_RANDOM, STATE_STOPPED }
State;
typedef struct StructMachineData
{
unsigned int lastTick;
unsigned char lastBit;
} MachineData;
typedef State func_state_t(MachineData*);


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "toca.h"
#include <stdio.h>
#include <string.h>
/* Private function prototypes (code generation followed by alphabetical) ----*/
static void SystemClock_Config(void);
static State machine(State, MachineData*);
static int program_loop(void);
/* State Functions */
static State state_anticlockwise(MachineData*);
static State state_clockwise(MachineData*);
static State state_random(MachineData*);
static State state_stop(MachineData*);
/* Globals -------------------------------------------------------------------*/
static func_state_t* const stateTable [4] =
{ state_anticlockwise, state_clockwise, state_random, state_stop };
static State machine(State curState, MachineData* ptrData)
{
return stateTable[curState](ptrData);
}
/**
  * @brief  The application entry point.
  * @retval int - status code
  *
  * The developer is required to provide additional
  * configuration for the necessary features that will be enabled
  * for this application. Only the generated configuration is provided.
  */
int main(void)
{
/* Configure and Init */
HAL_Init();
SystemClock_Config();
init_serial_io();
setvbuf(stdin, NULL, _IONBF, 0);

return program_loop();;
}

static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}


/**
  * @brief  The program loop
  * @retval int - status code
  */
static int program_loop(void)
{
	/* State Machine Variables */
	MachineData data = {0, 12 };
	State curState = STATE_ANTICLOCKWISE;
	/* Local Variables */

	/* Program Loop */
	for(;;)
	{
		curState = machine(curState, &data);
		HAL_Delay(1000);
	}

	return 0;
}

/* Initialisation Functions --------------------------------------------------*/
static State state_anticlockwise(MachineData *ptrData)
{
printf("I am in state 0\r\n");
return STATE_CLOCKWISE;
}
static State state_clockwise(MachineData *ptrData)
{
printf("I am in state 1\r\n");
return STATE_RANDOM;
}
static State state_random(MachineData *ptrData)
{
printf("I am in state 2\r\n");
return STATE_STOPPED;
}
static State state_stop(MachineData *ptrData)
{
printf("I am in state 3\r\n");
return STATE_STOPPED;
}

