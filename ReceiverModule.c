<<<<<<< HEAD
/* USER CODE BEGIN 0 */
uint8_t receivedData[1];
/* USER CODE END 0 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_UART_Receive(&huart1, receivedData, 1, 100);
	  if (receivedData[0] == '0'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '1'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '2'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '3'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '4'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '5'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	  }
	  HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
  /*STM32CubeIDE Settings
Enable USART1 asynchronous

Parameter Settings --> Basic Parameters --> Baud rate 9600

=======
/* USER CODE BEGIN 0 */
uint8_t receivedData[1];
/* USER CODE END 0 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_UART_Receive(&huart1, receivedData, 1, 100);
	  if (receivedData[0] == '0'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '1'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '2'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '3'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '4'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	  }
	  else if (receivedData[0] == '5'){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	  }
	  HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
  /*STM32CubeIDE Settings
Enable USART1 asynchronous

Parameter Settings --> Basic Parameters --> Baud rate 9600

>>>>>>> f397956bd4886f513916eace2cae7527cd722f48
Set PA1, PA3, PA5, PA7 and PB1 to GPIO_Output */