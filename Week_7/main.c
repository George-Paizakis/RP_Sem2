/**
  ******************************************************************************
  * @file           : main.c
  * @author			: <your_name>
  * @version		: 1.0
  * @date			: <project_date>
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


/* Includes (Vendor Libraries, Standard Libraries, Personal Libraries) -------*/
#include "main.h"
#include "toca.h"
#include <stdio.h>

/* Type Definitions ----------------------------------------------------------*/


/* Extern Function Prototypes ------------------------------------------------*/


/* Static Function Prototypes (Generated, Initialisation, Logic) -------------*/
static void SystemClock_Config(void);

static void init_tim3(void);
static int program_loop(void);


/* Global Variables (Extern, Static) -----------------------------------------*/
static TIM_HandleTypeDef gTIM3;

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
	/* Local Variables */

	/* Configure and Init */
	HAL_Init();
	SystemClock_Config();
	/* Enable PORTD Clock */
			 __HAL_RCC_GPIOD_CLK_ENABLE();
	init_serial_io();
	init_tim3();
	setvbuf(stdin, NULL, _IONBF, 0);

	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_TIM_Base_Start_IT(&gTIM3);

	printf("Hello World\r\n");


	return program_loop();
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
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
  RCC_OscInitStruct.OscillatorType = 		RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = 				RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = 			RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = 		RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 				4;
  RCC_OscInitStruct.PLL.PLLN = 				128;
  RCC_OscInitStruct.PLL.PLLP = 				RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 				6;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = 			RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = 			RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = 		RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = 		RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = 		RCC_HCLK_DIV8;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
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

static void init_tim3(void)
{
/* Local Variables */
TIM_ClockConfigTypeDef clkSrcCfg = {0};
TIM_MasterConfigTypeDef timMstrCfg = {0};
gTIM3.Instance = TIM3;
gTIM3.Init.Prescaler = (0);
gTIM3.Init.CounterMode = TIM_COUNTERMODE_UP;
gTIM3.Init.Period = (40 - 1);
gTIM3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
gTIM3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
HAL_TIM_Base_Init(&gTIM3);
clkSrcCfg.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
clkSrcCfg.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
clkSrcCfg.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
clkSrcCfg.ClockFilter = 15;
HAL_TIM_ConfigClockSource(&gTIM3, &clkSrcCfg);
timMstrCfg.MasterOutputTrigger = TIM_TRGO_RESET;
timMstrCfg.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
HAL_TIMEx_MasterConfigSynchronization(&gTIM3, &timMstrCfg);
}
/**
  * @brief  The program loop
  * @retval int - status code
  */
static int program_loop(void)
{
	/* INTERRUPTS */
	void TIM3_IRQHandler(void)
	{
	HAL_TIM_IRQHandler(&gTIM3);
	}

	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
	{
	printf("Counted...\r\n");
	}
	/* Local Variables */

	/* Program Loop */
	for(;;)
	{

	}

	return 0;
}
