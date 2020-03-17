#ifndef MEM_H_
#define MEM_H_

#define MEM_BUF_SIZE_LARGE 512
#define MEM_BUF_SIZE_MIDDLE 256
#define MEM_BUF_SIZE_LITTLE 128

typedef struct tagMem_Instance
{
	unsigned char* BUF;
	unsigned short rIdx;
	unsigned short wIdx;
	unsigned short size;
}Mem_Instance,*PTR_Mem_Instance;

typedef enum tagMem_Buf_Size
{
	Mem_Buf_Size_Little,
	Mem_Buf_Size_Middle,
	Mem_Buf_Size_Large
}Mem_Buf_Size;

void MEM_Init(PTR_Mem_Instance pMemInstance,Mem_Buf_Size nem_buf_size);
unsigned short MEM_GetUsed(PTR_Mem_Instance pMemInstance);
void MEM_Drop(PTR_Mem_Instance pMemInstance,unsigned short len);
void MEM_PushByte(PTR_Mem_Instance pMemInstance,unsigned char var);
void MEM_PushBytes(PTR_Mem_Instance pMemInstance,unsigned char* buf,unsigned short len);
unsigned char MEM_PopupBytes(PTR_Mem_Instance pMemInstance,unsigned char* content,unsigned short len);
unsigned char MEM_PopupBytesInTest(PTR_Mem_Instance pMemInstance,unsigned char* content,unsigned short len);

#endif
