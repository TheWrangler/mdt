#include "mem.h"

void MEM_Init(PTR_Mem_Instance pMemInstance)
{
	pMemInstance->rIdx = 0;
	pMemInstance->wIdx = 0;
}

void MEM_PushByte(PTR_Mem_Instance pMemInstance,unsigned char var)
{
	pMemInstance->BUF[pMemInstance->wIdx] = var;
	pMemInstance->wIdx = (pMemInstance->wIdx + 1) % MEM_BUF_SIZE;
}
