#ifndef MEM_H_
#define MEM_H_

#define MEM_BUF_SIZE 512

typedef struct tagMem_Instance
{
	unsigned char BUF[MEM_BUF_SIZE];
	unsigned short rIdx;
	unsigned short wIdx;
}Mem_Instance,*PTR_Mem_Instance;

void MEM_Init(PTR_Mem_Instance pMemInstance);
void MEM_PushByte(PTR_Mem_Instance pMemInstance,unsigned char var);

#endif
