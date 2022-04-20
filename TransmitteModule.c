/* USER CODE BEGIN 0 */
uint16_t readValue;
uint8_t charToTransmit[1];
/* USER CODE END 0 */

  /* USER CODE BEGIN 2 */
  HAL_ADC_Start(&hadc1);
  /* USER CODE END 2 */

 /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_ADC_PollForConversion(&hadc1,1000);
	  readValue = HAL_ADC_GetValue(&hadc1);
          // divide by 800 to convert 0~4095 to 0~5
          // Add 48 to convert number 0~5 to character '0' ~ '5'
	  charToTransmit[0] = readValue / 800 + 48;
	  HAL_UART_Transmit(&huart1, charToTransmit, 1, 100);
	  HAL_Delay(500);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
  /* STM32CubeIDE Settings
Enable USART1 asynchronous

Parameter Settings --> Basic Parameters --> Baud rate 9600

ADC1 - IN9 (tick)

Parameter Settings --> ADC Settings --> Continuous Conversion Mode (Enabled) */