#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "mem.h"

#define UART_TX_BUF_SIZE 20

typedef struct tagUart_TR
{
	UART_HandleTypeDef* ptr_huart;
	unsigned char BUF[UART_TX_BUF_SIZE];
	unsigned char size;
	Mem_Instance mem_instance;
}Uart_TR,*PTR_Uart_TR;

void UART_InitTR(void);
void UART_TransmitDatas(Uart_TR* uart_tr,unsigned char* pBuf,unsigned char size);
void UART_Transmit(Uart_TR* uart_tr);
void UART_ActiveReceive(Uart_TR* uart_tr);
unsigned char UART_IsTxIDLE(Uart_TR* uart_tr);
void UART_ActiveReceive(Uart_TR* uart_tr);
void UART_ReceiveHook(UART_HandleTypeDef* uart,unsigned char var);

#endif
