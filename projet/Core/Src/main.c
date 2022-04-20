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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>
#include "usbd_cdc_if.h"
#include "string.h"
#include "stdlib.h"
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t buf[128] = {0};
	uint8_t data[128]= {0};
	float lat;
	float lon;
	char mobile[] = "+21653071340";
	char msg[30];
	char cmd[100];
	char pkt[100];
	char latitude[15];
	char longitude[15];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(5);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {

	  if(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin)==GPIO_PIN_RESET)
		  {

		   HAL_GPIO_WritePin(GPIOC, LED1_Pin,GPIO_PIN_SET);
		   	//LoRa configuration

		 		   sprintf(cmd,"AT\r\n");
		 		   HAL_UART_Transmit(&huart2,(uint8_t *)cmd,strlen(cmd),100);
		 		   HAL_UART_Receive(&huart2, buf, 128,100);
		 		   printf("%s",buf);
		 		   memset(buf,0,sizeof(buf));

		 		   sprintf(cmd,"AT+MODE=TEST\r\n");
		 		   HAL_UART_Transmit(&huart2,(uint8_t *)cmd,strlen(cmd),100);
		 		   HAL_UART_Receive(&huart2, buf, 128,1000);
		 		   printf("%s",buf);
		 		   memset(buf,0,sizeof(buf));

		 		   sprintf(cmd,"AT+TEST=?\r\n");
		 		   HAL_UART_Transmit(&huart2,(uint8_t *)cmd,strlen(cmd),100);
		 		   HAL_UART_Receive(&huart2, buf, 128,1000);
		 		   printf("%s",buf);
		 		   memset(buf,0,sizeof(buf));

		 		   sprintf(cmd,"AT+TEST=RFCFG,868.1,SF7,125,8,8,14,ON,OFF,OFF\r\n");
		 		   HAL_UART_Transmit(&huart2,(uint8_t *)cmd,strlen(cmd),100);
		 		   HAL_UART_Receive(&huart2, buf, 128,1000);
		 		   printf("%s",buf);
		 		   memset(buf,0,sizeof(buf));
		   sprintf(msg,"Checking Module...\r\n");
		   		   	printf(msg);
		   		   	uint8_t flag=1;

		   		   	while(flag){
		   		   		sprintf(cmd,"AT\r\n");
		   		   		HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   		HAL_UART_Receive (&huart1, buf, 128,1000);
		   		   		HAL_Delay(1000);

		   		   		if(strstr((char *)buf,"OK")){
		   		   			sprintf(msg,"Module Connected\r\n");
		   		   			printf(msg);
		   		   			flag=0;
		   		   		}
		   		   		HAL_Delay(1000);
		   		   		printf("%s",buf);
		   		   		memset(buf,0,sizeof(buf));
		   		   	}
		   		   // GPS

		   		   	sprintf(msg,"GPS \r\n");
		   		   	printf(msg);
		   		   	sprintf(cmd,"AT+CGPSPWR=1\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);
		   		   	memset(buf,0,sizeof(buf));

		   		   	//Reset the GPS in autonomy mode

/*		   		   	sprintf(cmd,"AT+CGPSRST=0\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);
		   		   	memset(buf,0,sizeof(buf));
		   		   	//Wait for the GPS reset

		   		   	sprintf(cmd,"WAIT=15\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);
		   		   	memset(buf,0,sizeof(buf));*/

		   		   	sprintf(cmd,"AT+CGPSSTATUS?\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);
		   		   	memset(buf,0,sizeof(buf));


		   		   	sprintf(cmd,"AT+CGPSINF=0\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);

		   		   // extract coordinations

		   		   	strtok(data, ",");
		   		   	strcpy(longitude,strtok(NULL, ",")); // Gets longitude
		   		   	sprintf(msg,"longitude: \r\n");
		   		   	printf(msg);
		   		   	printf(longitude);
		   		   	printf("\n");

		   		   	strcpy(latitude,strtok(NULL, ",")); // Gets latitude
		   		   	sprintf(msg,"latitude: \r\n");
		   		   	printf(msg);
		   		   	printf(latitude);
		   		   	printf("\n");

		   		   	memset(buf,0,sizeof(buf));

		   		   	sprintf(cmd,"AT+CGPSPWR=0\r\n");
		   		   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		   		   	HAL_UART_Receive(&huart1, buf, 128,1000);
		   		   	HAL_Delay(1000);
		   		   	printf("%s",buf);
		   		   	memset(buf,0,sizeof(buf));

 		   sprintf(msg,"Sending Message to gateway\r\n");
 		   printf(msg);
 		   uint8_t pkt_receive=0;
 		   while (pkt_receive==0)
 		   {
 			   lat=strtold(latitude,NULL);
 			   lon=strtold(longitude,NULL);
 			   sprintf(pkt,"AT+TEST=TXLRSTR,\"1,%2.16f,%2.16f\"\r\n",lat,lon);
 			   HAL_UART_Transmit(&huart2,(uint8_t *)pkt,strlen(pkt),1000);
 			   HAL_UART_Receive(&huart2, buf, 128,1000);
 			   HAL_Delay(500);
 			   printf("%s",buf);
 			   HAL_GPIO_WritePin(GPIOC, LED2_Pin,GPIO_PIN_SET);
 			   HAL_Delay(1000);
 			   HAL_GPIO_WritePin(GPIOC, LED2_Pin,GPIO_PIN_RESET);

 			   memset(buf,0,sizeof(buf));

 			   sprintf(pkt,"AT+TEST=RXLRPKT\r\n");
 		   	   HAL_UART_Transmit(&huart2,(uint8_t *)pkt,strlen(pkt),1000);
 		   	   HAL_UART_Receive(&huart2, buf, 128,1000);
 		   	   //HAL_Delay(500);
 		   	   printf("%s",buf);
 		   	   	   if (strstr((char *)buf,"1")){
 		   	   		   pkt_receive=1;
 		   	   		   HAL_GPIO_WritePin(GPIOC, LED2_Pin,GPIO_PIN_SET);
 		   	   			   }
 		   		memset(buf,0,sizeof(buf));
 		   }
 		   sprintf(msg,"SMS with GSM Module\r\n");
 				   printf(msg);


 				   	// sending  SMS
 				   	sprintf(msg,"Sending Message\r\n");
 				   	printf(msg);
 				   	sprintf(cmd,"AT+CMGF=1\r\n");
 				   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
 				   	HAL_UART_Receive(&huart1, buf, 128,1000);
 				   	HAL_Delay(1000);
 				   	printf("%s",buf);
 				   	memset(buf,0,sizeof(buf));
 				    HAL_GPIO_WritePin(GPIOC, LED3_Pin,GPIO_PIN_SET);
 				   	sprintf(cmd,"AT+CMGS=\"%s\"\r\n",mobile);
 				   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
 				   	HAL_Delay(100);

 				   	sprintf(cmd,"ALERT!\n http://maps.google.com/maps?q=loc:%2.16f,%2.16f%c",lat,lon,0x1a);
 				   	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
 				   	HAL_UART_Receive(&huart1, buf, 128,1000);
 				   	HAL_Delay(5000);

 				   	printf("%s",buf);
 					memset(buf,0,sizeof(buf));

 				   	sprintf(msg,"Message Sent\r\n");
 				   	printf(msg);


		  }
	  	else
	   	{HAL_GPIO_WritePin(GPIOC, LED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, LED2_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, LED3_Pin,GPIO_PIN_RESET);}


    /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int _write(int file, char *data, int len)
	{
	   if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
	   {
	      errno = EBADF;
	      return -1;
	   }

	   uint8_t status = CDC_Transmit_FS((uint8_t*)data, len);
           HAL_Delay(2);
	   // return # of bytes written - as best we can tell
	   return (status == USBD_OK ? len : 0);
	}
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
