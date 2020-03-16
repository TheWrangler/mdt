#include "uart.h"

UART_HandleTypeDef* huart1;
UART_HandleTypeDef* huart2;

Uart_TR Uart_TR1;
Uart_TR Uart_TR2;

void UART_InitTR(void)
{
	unsigned char i;
	huart1 = &(Uart_TR1.uart);
	Uart_TR1.size = 20;
	for(i=0;i<UART_TX_BUF_SIZE;i++)
		Uart_TR1.BUF[i] = i;
	MEM_Init(&(Uart_TR1.mem_instance));
	
	huart2 = &(Uart_TR2.uart);
	Uart_TR2.size = 0;
	for(i=0;i<UART_TX_BUF_SIZE;i++)
		Uart_TR2.BUF[i] = 0;
	MEM_Init(&(Uart_TR2.mem_instance));
}

void UART_TransmitDatas(UART_HandleTypeDef* uart,unsigned char* pBuf,unsigned char size)
{
	unsigned char i;
	
	if(size>UART_TX_BUF_SIZE)
		size = UART_TX_BUF_SIZE;
	
	if(uart == &(Uart_TR1.uart))
	{
		Uart_TR1.size = size;
		for(i=0;i<size;i++)
			Uart_TR1.BUF[i] = pBuf[i];
		HAL_UART_Transmit_IT(&(Uart_TR1.uart),Uart_TR1.BUF,Uart_TR1.size);
	}
	else if(uart == &(Uart_TR2.uart))
	{
		Uart_TR2.size = size;
		for(i=0;i<size;i++)
			Uart_TR2.BUF[i] = pBuf[i];
		HAL_UART_Transmit_IT(&(Uart_TR2.uart),Uart_TR2.BUF,Uart_TR2.size);
	}
}

void UART_Transmit(UART_HandleTypeDef* uart)
{
	if(uart == &(Uart_TR1.uart))
	{
		HAL_UART_Transmit_IT(&(Uart_TR1.uart),Uart_TR1.BUF,Uart_TR1.size);
	}
	else if(uart == &(Uart_TR2.uart))
	{
		HAL_UART_Transmit_IT(&(Uart_TR2.uart),Uart_TR2.BUF,Uart_TR2.size);
	}
}

unsigned char UART_IsTxIDLE(UART_HandleTypeDef* uart)
{
	if(uart->gState == HAL_UART_STATE_READY)
		return 1;
	else return 0;
}

void UART_ActiveReceive(UART_HandleTypeDef* uart)
{
	HAL_UART_Receive_IT(uart,(unsigned char *)1,1);
}

void UART_ReceiveHook(UART_HandleTypeDef* uart,unsigned char var)
{
	if(uart == &(Uart_TR1.uart))
	{
		MEM_PushByte(&(Uart_TR1.mem_instance),var);
	}
	else if(uart == &(Uart_TR2.uart))
	{
		MEM_PushByte(&(Uart_TR1.mem_instance),var);
	}
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  Uart_TR1.uart.Instance = USART1;
  Uart_TR1.uart.Init.BaudRate = 115200;
  Uart_TR1.uart.Init.WordLength = UART_WORDLENGTH_8B;
  Uart_TR1.uart.Init.StopBits = UART_STOPBITS_1;
  Uart_TR1.uart.Init.Parity = UART_PARITY_NONE;
  Uart_TR1.uart.Init.Mode = UART_MODE_TX_RX;
  Uart_TR1.uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  Uart_TR1.uart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&(Uart_TR1.uart)) != HAL_OK)
  {
    UART_Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  Uart_TR2.uart.Instance = USART2;
  Uart_TR2.uart.Init.BaudRate = 115200;
  Uart_TR2.uart.Init.WordLength = UART_WORDLENGTH_8B;
  Uart_TR2.uart.Init.StopBits = UART_STOPBITS_1;
  Uart_TR2.uart.Init.Parity = UART_PARITY_NONE;
  Uart_TR2.uart.Init.Mode = UART_MODE_TX_RX;
  Uart_TR2.uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  Uart_TR2.uart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&(Uart_TR2.uart)) != HAL_OK)
  {
    UART_Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void UART_Error_Handler(void)
{
	
}


