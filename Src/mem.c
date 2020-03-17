#include "mem.h"

void MEM_Init(PTR_Mem_Instance pMemInstance,Mem_Buf_Size nem_buf_size)
{
	pMemInstance->rIdx = 0;
	pMemInstance->wIdx = 0;
	switch(nem_buf_size)
	{
		case Mem_Buf_Size_Little:
			pMemInstance->BUF = (unsigned char*)malloc(MEM_BUF_SIZE_LITTLE);
			pMemInstance->size = MEM_BUF_SIZE_LITTLE;
			break;
		case Mem_Buf_Size_Middle:
			pMemInstance->BUF = (unsigned char*)malloc(MEM_BUF_SIZE_MIDDLE);
			pMemInstance->size = MEM_BUF_SIZE_MIDDLE;
			break;
		case Mem_Buf_Size_Large:
			pMemInstance->BUF = (unsigned char*)malloc(MEM_BUF_SIZE_LARGE);
			pMemInstance->size = MEM_BUF_SIZE_LARGE;
			break;
	}
}

unsigned short MEM_GetUsed(PTR_Mem_Instance pMemInstance)
{
  unsigned short widx = pMemInstance->wIdx;
  unsigned short ridx = pMemInstance->rIdx;
  return widx - ridx;
}

void MEM_Drop(PTR_Mem_Instance pMemInstance,unsigned short len)
{
  unsigned short i;
	
	unsigned short used_len = MEM_GetUsed(pMemInstance);
	if(used_len < len)
        len = used_len;
			
	for(i=0;i<len;i++)
       pMemInstance->rIdx = (pMemInstance->rIdx + 1) % pMemInstance->size;
}

void MEM_PushByte(PTR_Mem_Instance pMemInstance,unsigned char var)
{
	if(pMemInstance->size - MEM_GetUsed(pMemInstance) < 2)
        MEM_Drop(pMemInstance,1);
			
	pMemInstance->BUF[pMemInstance->wIdx] = var;
	pMemInstance->wIdx = (pMemInstance->wIdx + 1) % pMemInstance->size;
}

void MEM_PushBytes(PTR_Mem_Instance pMemInstance,unsigned char* buf,unsigned short len)
{
	unsigned short i;
	unsigned short empty_size = pMemInstance->size - MEM_GetUsed(pMemInstance);
	if(empty_size < len+1)
        MEM_Drop(pMemInstance,len+1-empty_size);
	
	for(i=0;i<len;i++)
	{
		pMemInstance->BUF[pMemInstance->wIdx] = buf[i];
		pMemInstance->wIdx = (pMemInstance->wIdx + 1) % pMemInstance->size;
	}
}

unsigned char MEM_PopupBytes(PTR_Mem_Instance pMemInstance,unsigned char* content,unsigned short len)
{
    unsigned short i;

    if(MEM_GetUsed(pMemInstance) < len)
        return 0;
    
    for(i=0;i<len;i++)
    {
        content[i] = pMemInstance->BUF[pMemInstance->rIdx];
        pMemInstance->rIdx = (pMemInstance->rIdx + 1) % pMemInstance->size;
    }

    return 1;
}

unsigned char MEM_PopupBytesInTest(PTR_Mem_Instance pMemInstance,unsigned char* content,unsigned short len)
{
    unsigned short i;
    unsigned short ridx = pMemInstance->rIdx;

    if(MEM_GetUsed(pMemInstance) < len)
        return 0;

    for(i=0;i<len;i++)
    {
        content[i] = pMemInstance->BUF[ridx];
        ridx = (ridx + 1) % pMemInstance->size;
    }

    return 1;
}