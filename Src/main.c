
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
		// HID Media
		struct mediaHID_t {
			uint8_t id;
			uint8_t keys;
		};
		struct mediaHID_t mediaHID;
		mediaHID.id = 2;
		mediaHID.keys = 0;
		// HID Buttons
		struct keypadHID_t {
			uint8_t id;
			uint8_t keys;
		};
		struct keypadHID_t keypadHID;
		keypadHID.id = 1;
		keypadHID.keys = 0;
		
		int pinStates[11] = {0};
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    // Send HID report
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && pinStates[0] == 0) {	     //Checks if PA0 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_VOL_UP;                                     //Volume Up
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //VOL UP is pressed
			pinStates[0] = 1;                                                    //Set state to pressed
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && pinStates[0] == 1) { //Checks if PA0 is not pressed but was pressed before
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[0] = 0;                                                    //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && pinStates[1] == 0) {	     //Checks if PA1 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_VOL_DEC;                                    //Volume Down
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //VOL DOWN is pressed
			pinStates[1] = 1;                                                    //Set state to pressed
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && pinStates[1] == 1) { //Checks if PA1 is not pressed but was pressed before
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[1] = 0;                                                    //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && pinStates[2] == 0) {	     //Checks if PA2 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_MUTE;                                       //Mute
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //MUTE is pressed
			pinStates[2] = 1;                                                    //Set state to pressed
			HAL_Delay(30);
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
			HAL_Delay(100);
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && pinStates[2] == 1) { //Checks if PA2 is not pressed but was pressed before
			pinStates[2] = 0;                                                    //Set state back to not pressed
			HAL_Delay(100);
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) && pinStates[3] == 0) {	     //Checks if PA3 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_SCAN_PREV;                                  //Back One Song
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //SCAN_PREV is pressed
			pinStates[3] = 1;                                                    //Set state to pressed
			HAL_Delay(30);
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
			HAL_Delay(100);
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) && pinStates[3] == 1) { //Checks if PA3 is not pressed but was pressed before
			pinStates[3] = 0;                                                    //Set state back to not pressed
			HAL_Delay(100);
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) && pinStates[4] == 0) {	     //Checks if PA4 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_SCAN_NEXT;                                  //Skip
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //SCAN_NEXT is pressed
			pinStates[4] = 1;                                                    //Set state to pressed
			HAL_Delay(30);
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
			HAL_Delay(100);
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) && pinStates[4] == 1) { //Checks if PA4 is not pressed but was pressed before
			pinStates[4] = 0;                                                    //Set state back to not pressed
			HAL_Delay(100);
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) && pinStates[5] == 0) {	     //Checks if PA5 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);                 //Switch off LED
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = USB_HID_PAUSE;                                      //Play/Pause
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);                   //PAUSE is pressed
			pinStates[5] = 1;                                                    //Set state to pressed
			HAL_Delay(30);
			keypadHID.id = 2;                                                    //Consumer Device
			keypadHID.keys = 0;                                                  //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);               //Switch on LED
			HAL_Delay(100);
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) && pinStates[5] == 1) { //Checks if PA5 is not pressed but was pressed before
			pinStates[5] = 0;                                                    //Set state back to not pressed
			HAL_Delay(100);
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) && pinStates[6] == 0) {	// checks if PA6 is pressed and was not pressed before
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //Switch off LED
			keypadHID.id = 1; //GamePad
			keypadHID.keys = GP_HID_J1; //Button 1
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2); //Button 1 is pressed
			pinStates[6] = 1; //Set state to pressed
		} else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) && pinStates[6] == 1) { //checks if PA6 is not pressed but was pressed before
			keypadHID.id = 1; //GamePad
			keypadHID.keys = 0; //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[6] = 0; //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) && pinStates[7] == 0) {	// checks if PA7 is pressed and was not pressed before
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //Switch off LED
			keypadHID.id = 1; //GamePad
			keypadHID.keys = GP_HID_J2; //Button 2
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2); //Button 2 is pressed
			pinStates[7] = 1; //Set state to pressed
    } else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) && pinStates[7] == 1) { //checks if PA7 is not pressed but was pressed before
			keypadHID.id = 1; //GamePad
			keypadHID.keys = 0; //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[7] = 0; //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) && pinStates[8] == 0) {	// checks if PA8 is pressed and was not pressed before
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //Switch off LED
			keypadHID.id = 1; //GamePad
			keypadHID.keys = GP_HID_J3; //Button 3
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2); //Button 3 is pressed
			pinStates[8] = 1; //Set state to pressed
    } else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) && pinStates[8] == 1) { //checks if PA8 is not pressed but was pressed before
			keypadHID.id = 1; //GamePad
			keypadHID.keys = 0; //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[8] = 0; //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) && pinStates[9] == 0) {	// checks if PA9 is pressed and was not pressed before
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //Switch off LED
			keypadHID.id = 1; //GamePad
			keypadHID.keys = GP_HID_J4; //Button 4
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2); //Button 4 is pressed
			pinStates[9] = 1; //Set state to pressed
    } else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) && pinStates[9] == 1) { //checks if PA9 is not pressed but was pressed before
			keypadHID.id = 1; //GamePad
			keypadHID.keys = 0; //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[9] = 0; //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //Switch on LED
		}
		
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) && pinStates[10] == 0) {	// checks if PA10 is pressed and was not pressed before
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //Switch off LED
			keypadHID.id = 1; //GamePad
			keypadHID.keys = GP_HID_J5; //Button 5
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2); //Button 5 is pressed
			pinStates[10] = 1; //Set state to pressed
    } else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) && pinStates[10] == 1) { //checks if PA10 is not pressed but was pressed before
			keypadHID.id = 1; //GamePad
			keypadHID.keys = 0; //Not Pressed
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keypadHID, 2);
			pinStates[10] = 0; //Set state back to not pressed
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //Switch on LED
		}
		
    //keyboardHID.modifiers = USB_HID_MODIFIER_RIGHT_SHIFT;
    //keyboardHID.key1 = USB_HID_VOL_DEC;
    //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof(struct keyboardHID_t));
    //HAL_Delay(30);
    //keyboardHID.modifiers = 0;
    //keyboardHID.key1 = 0;
    //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof(struct keyboardHID_t));
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 
                           PA8 PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
