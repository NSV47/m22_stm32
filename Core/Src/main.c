/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define LED4_ON() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0)
#define LED4_OFF() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0)
#define LED3_ON() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1)
#define LED3_OFF() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1)
#define LED2_ON() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_10)
#define LED2_OFF() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10)
#define LED1_ON() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_11)
#define LED1_OFF() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_11)
char rx_str[30], tx_str[30], tmp_str[10];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//--------------------------------------------------------
void USART_TX (uint8_t* dt, uint16_t sz)
{
	uint16_t ind = 0;
	while (ind<sz)
  {
		while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
		LL_USART_TransmitData8(USART1,*(uint8_t*)(dt+ind));
    ind++;
  }
}
//--------------------------------------------------------
void controlUSART(uint8_t* rx_dt){
	char cmd[30];
	sprintf(cmd, "%s",(uint8_t*)rx_dt);
	//USART_TX(cmd, strlen(cmd));
	if(strcmp(cmd, "led1_on")==0){
		//USART_TX(cmd, strlen(cmd));
		LED1_ON();
	}else if(strcmp(cmd, "led1_off")==0){
		LED1_OFF();
	}
}
//--------------------------------------------------------
uint16_t USART_RX_TX_Str (uint8_t* tx_dt, uint8_t* rx_dt)
{
  uint16_t ind = 0;
	while (!LL_USART_IsActiveFlag_RXNE(USART1)) {}
  rx_dt[ind] = (uint8_t)(USART1->DR & 0x00FF);
	while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
  LL_USART_TransmitData8(USART1,*(uint8_t*)(tx_dt+ind));
	while(rx_dt[ind])
  {
		ind++;
		while (!LL_USART_IsActiveFlag_RXNE(USART1)) {}
		rx_dt[ind] = (uint8_t)(USART1->DR & 0x00FF);
		while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
		LL_USART_TransmitData8(USART1,*(uint8_t*)(tx_dt+ind));
  }
	return ind;
}
//--------------------------------------------------------
uint16_t USART_RX_Str (uint8_t* rx_dt)
{
  uint16_t ind = 0;
	//if(LL_USART_IsActiveFlag_RXNE(USART1)){
		while (!LL_USART_IsActiveFlag_RXNE(USART1)) {}
		rx_dt[ind] = (uint8_t)(USART1->DR & 0x00FF);
		while(rx_dt[ind])
		{
			ind++;
			while (!LL_USART_IsActiveFlag_RXNE(USART1)) {}
			rx_dt[ind] = (uint8_t)(USART1->DR & 0x00FF);
		}
	//}
	return ind;
}
//--------------------------------------------------------
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t i=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/*
		LED1_ON();
    LL_mDelay(100);
    LED1_OFF();
		LL_mDelay(100);
		*/
    LED2_ON();
    LL_mDelay(100);
    LED2_OFF();
    LED3_ON();
    LL_mDelay(100);
    LED3_OFF();
    LED4_ON();
    LL_mDelay(100);
    LED4_OFF();
		
		//sprintf(tx_str,"String  %04d\r\n",1023-i);
		sprintf(tx_str, "%s",(uint8_t*)rx_str);
		//USART_RX_TX_Str((uint8_t*)tx_str,(uint8_t*)rx_str);
		USART_RX_Str((uint8_t*)rx_str);
		USART_TX((uint8_t*)tx_str, strlen(tx_str));
		char cmd[30];
		sprintf(cmd, "%s",(uint8_t*)rx_str);
		if(strncmp(cmd, "led1_on", 7)==0){
			LED1_ON();
		}
		if(strncmp(cmd, "led1_off", 8)==0){
			LED1_OFF();
		}
		
		//controlUSART((uint8_t*)rx_str);
		//strncpy(tmp_str,rx_str+7,4);
		//i=atoi (tmp_str);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
  {
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(36000000);
  LL_SetSystemCoreClock(36000000);
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_10|LL_GPIO_PIN_11);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_10|LL_GPIO_PIN_11;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
