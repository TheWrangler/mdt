#include "uart.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

Uart_TR Uart_TR1;
Uart_TR Uart_TR2;

void UART_InitTR(void)
{
	unsigned char i;
	Uart_TR1.ptr_huart = &huart1;
	Uart_TR1.size = 0;
	for(i=0;i<UART_TX_BUF_SIZE;i++)
		Uart_TR1.BUF[i] = 0;
	MEM_Init(&(Uart_TR1.mem_instance),Mem_Buf_Size_Large);
	
	Uart_TR2.ptr_huart = &huart2;
	Uart_TR2.size = 0;
	for(i=0;i<UART_TX_BUF_SIZE;i++)
		Uart_TR2.BUF[i] = 0;
	MEM_Init(&(Uart_TR2.mem_instance),Mem_Buf_Size_Large);
}

void UART_TransmitDatas(Uart_TR* uart_tr,unsigned char* pBuf,unsigned char size)
{
	unsigned char i;
	
	if(size>UART_TX_BUF_SIZE)
		size = UART_TX_BUF_SIZE;
	
	uart_tr->size = size;
	for(i=0;i<size;i++)
		uart_tr->BUF[i] = pBuf[i];
	HAL_UART_Transmit_IT(uart_tr->ptr_huart,Uart_TR1.BUF,Uart_TR1.size);
}

void UART_Transmit(Uart_TR* uart_tr)
{
	HAL_UART_Transmit_IT(uart_tr->ptr_huart,Uart_TR1.BUF,Uart_TR1.size);
}

unsigned char UART_IsTxIDLE(Uart_TR* uart_tr)
{
	if(uart_tr->ptr_huart->gState == HAL_UART_STATE_READY)
		return 1;
	else return 0;
}

void UART_ActiveReceive(Uart_TR* uart_tr)
{
	HAL_UART_Receive_IT(uart_tr->ptr_huart,(unsigned char *)1,1);
}

void UART_ReceiveHook(UART_HandleTypeDef* uart,unsigned char var)
{
	if(uart == Uart_TR1.ptr_huart)
	{
		MEM_PushByte(&(Uart_TR1.mem_instance),var);
	}
	else if(uart == Uart_TR2.ptr_huart)
	{
		MEM_PushByte(&(Uart_TR2.mem_instance),var);
	}
}


