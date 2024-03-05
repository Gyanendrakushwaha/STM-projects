/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
//#define LCD_RS_PINc8      GPIO_PIN_8
//#define LCD_RS_PORTc     GPIOC

#define LCD_RS_PIN      GPIO_PIN_0
#define LCD_RS_PORT     GPIOB
#define LCD_RW_PIN      GPIO_PIN_1
#define LCD_RW_PORT     GPIOB
#define LCD_EN_PIN      GPIO_PIN_2
#define LCD_EN_PORT     GPIOB

//#define LCD_DATA_PORT   GPIOB

#define LCD_D4_PIN      GPIO_PIN_3
#define LCD_D4_PORT     GPIOB
#define LCD_D5_PIN      GPIO_PIN_4
#define LCD_D5_PORT     GPIOB
#define LCD_D6_PIN      GPIO_PIN_5
#define LCD_D6_PORT     GPIOB
#define LCD_D7_PIN      GPIO_PIN_6
#define LCD_D7_PORT     GPIOB

#define LCD_D0_PIN      GPIO_PIN_0
#define LCD_D0_PORT     GPIOC
#define LCD_D1_PIN      GPIO_PIN_1
#define LCD_D1_PORT     GPIOC
#define LCD_D2_PIN      GPIO_PIN_2
#define LCD_D2_PORT     GPIOC
#define LCD_D3_PIN      GPIO_PIN_3
#define LCD_D3_PORT     GPIOC
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LCD_SendCommand(uint8_t command) {
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);   // RS = 0 (Command mode)
    HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);   // RW = 0 (Write mode)

    	//0-3 pin of port c
    	HAL_GPIO_WritePin(LCD_D0_PORT, LCD_D0_PIN, (command >> 0) & 0x01);
        HAL_GPIO_WritePin(LCD_D1_PORT, LCD_D1_PIN, (command >> 1) & 0x01);
        HAL_GPIO_WritePin(LCD_D2_PORT, LCD_D2_PIN, (command >> 2) & 0x01);
        HAL_GPIO_WritePin(LCD_D3_PORT, LCD_D3_PIN, (command >> 3) & 0x01);
    //4-7 pin of port B
    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (command >> 4) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (command >> 5) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (command >> 6) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (command >> 7) & 0x01);

    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

//    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, command & 0x01);
//    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (command >> 1) & 0x01);
//    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (command >> 2) & 0x01);
//    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (command >> 3) & 0x01);
//
//    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
//    HAL_Delay(1);
//    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(2);
}

void LCD_SendData(uint8_t data) {
	HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);     // RS = 1 (Data mode)
	HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);   // RW = 0 (Write mode)
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);

	//0-3
	    	HAL_GPIO_WritePin(LCD_D0_PORT, LCD_D0_PIN, (data >> 0) & 0x01);
	        HAL_GPIO_WritePin(LCD_D1_PORT, LCD_D1_PIN, (data >> 1) & 0x01);
	        HAL_GPIO_WritePin(LCD_D2_PORT, LCD_D2_PIN, (data >> 2) & 0x01);
	        HAL_GPIO_WritePin(LCD_D3_PORT, LCD_D3_PIN, (data >> 3) & 0x01);
	    //4-7
	    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (data >> 4) & 0x01);
	    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (data >> 5) & 0x01);
	    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (data >> 6) & 0x01);
	    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (data >> 7) & 0x01);
	HAL_Delay(10);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);


}

void LCD_Init() {
    // Initialize LCD in 4-bit mode
	HAL_Delay(20);

//		LCD_SendCommand(0x01);		//Clear Display, Cursor to Home
//				    HAL_Delay(2);

		// Function Set (8-bit mode, 2 lines, 5x8 font)
	    LCD_SendCommand(0x38);    //Display Function (2 rows for 8-bit data; small)
	    HAL_Delay(5);

	    // Display ON (Cursor and blink off)
	    LCD_SendCommand(0x0C); 		//Display on, Cursor and Cursor Blink off
	    HAL_Delay(5);

	    LCD_SendCommand(0x01);		//Clear Display, Cursor to Home
	    HAL_Delay(5);

//	    LCD_SendCommand(0x10);		//Cursor shift left
//	    HAL_Delay(5);


	    // Entry Mode Set (Increment cursor, no shift)
	    LCD_SendCommand(0x06);		//Cursor Increment, Shift off
	    HAL_Delay(5);


////    // Function Set (Interface is 8 bits long.)
////    LCD_SendCommand(0x30);
////    HAL_Delay(5);
////
////    // Function Set (Interface is 8 bits long.)
////    LCD_SendCommand(0x30);
////    HAL_Delay(1);
////
////    // Function Set (Interface is 8 bits long.)
////    LCD_SendCommand(0x30);
////    HAL_Delay(1);
//
//    // Function Set (Interface is 4 bits long.)
//    LCD_SendCommand(0x20);
//    HAL_Delay(1);
//
//    // Function Set (4-bit mode, 2 lines, 5x8 font)
//    LCD_SendCommand(0x28);
//    HAL_Delay(1);
//
//    // Display OFF
//    LCD_SendCommand(0x08);
//    HAL_Delay(1);
//
//    // Clear Display
//    LCD_SendCommand(0x01);
//    HAL_Delay(2);
//
//    // Entry Mode Set (Increment cursor, no shift)
//    LCD_SendCommand(0x06);
//    HAL_Delay(1);
//
//    // Display ON (Cursor and blink off)
//    LCD_SendCommand(0x0C);
//    HAL_Delay(1);

}

void LCD_WriteString(const char* str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	// Enable GPIOB clock
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // Configure LCD control pins as outputs
      GPIOB->MODER |= GPIO_MODER_MODER0_0;    // RS
      GPIOB->MODER |= GPIO_MODER_MODER1_0;    // RW
      GPIOB->MODER |= GPIO_MODER_MODER2_0;    // EN

      // Configure LCD data pins as outputs
      	  	GPIOC->MODER |= GPIO_MODER_MODER0_0;    // D0
            GPIOC->MODER |= GPIO_MODER_MODER1_0;    // D1
            GPIOC->MODER |= GPIO_MODER_MODER2_0;    // D2
            GPIOC->MODER |= GPIO_MODER_MODER3_0;    // D3

      GPIOB->MODER |= GPIO_MODER_MODER3_0;    // D4
      GPIOB->MODER |= GPIO_MODER_MODER4_0;    // D5
      GPIOB->MODER |= GPIO_MODER_MODER5_0;    // D6
      GPIOB->MODER |= GPIO_MODER_MODER6_0;    // D7

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  LCD_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LCD_SendData(65);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//	  LCD_SendCommand(0x80);  // Set cursor to the first line
//	          LCD_WriteString("Hello, World!");
//
//	          HAL_Delay(1000);
//
//	          LCD_SendCommand(0xC0);  // Set cursor to the second line
//	          LCD_WriteString("STM32F0Discovery");
//
//	          HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, pin0_Pin|pin1_Pin|pin2_Pin|pin3_Pin
                          |pin4_Pin|pin5_Pin|pin6_Pin|pin7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : pin0_Pin pin1_Pin pin2_Pin pin3_Pin
                           pin4_Pin pin5_Pin pin6_Pin pin7_Pin */
  GPIO_InitStruct.Pin = pin0_Pin|pin1_Pin|pin2_Pin|pin3_Pin
                          |pin4_Pin|pin5_Pin|pin6_Pin|pin7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
