#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "mem.h"

#define UART_TX_BUF_SIZE 20

typedef struct tagUart_TR
{
	UART_HandleTypeDef uart;
	unsigned char BUF[UART_TX_BUF_SIZE];
	unsigned char size;
	Mem_Instance mem_instance;
}Uart_TR,*PTR_Uart_TR;

void UART_InitTR(void);
void UART_TransmitDatas(UART_HandleTypeDef* uart,unsigned char* pBuf,unsigned char size);
void UART_Transmit(UART_HandleTypeDef* uart);
unsigned char UART_IsTxIDLE(UART_HandleTypeDef* uart);
void UART_ActiveReceive(UART_HandleTypeDef* uart);
void UART_ReceiveHook(UART_HandleTypeDef* uart,unsigned char var);

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void UART_Error_Handler(void);

#endif
