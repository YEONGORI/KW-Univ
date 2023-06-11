#define INT32U unsigned long
#define INT16U unsigned short
#define INT8U unsigned char
#define OS_EVENT_TBL_SIZE 100

typedef struct
{
} OS_STK;

typedef struct
{
	void *OSMemAddr;	 // 파티션의 시작주소
	void *OSMemFreeList; // 파티션 내의 free block list 관리
	INT32U OSMemBlkSize; // 파티션 내의 block 크기 (파티션 초기화 시 인자로 전달)
	INT32U OSMemNBlks;	 // 파티션 내의 block 개수 (파티션 초기화 시 인자로 전달)
	INT32U OSMemNFree;	 // 파티션 내의 free block 개수
} OS_MEM;

typedef struct
{
	INT8U OSEventType;
	INT8U OSEventGrp;
	INT16U OSEventCnt;
	void *OSEventPtr;
	INT8U OSEventTbl[OS_EVENT_TBL_SIZE];
} OS_EVENT;

OS_EVENT *SemaphorePtr;
OS_MEM *PartitionPtr;
INT8U Partition[100][32];
OS_STK TaskStk[1000];

void Task(void *pdata);

void main(void)
{
	INT8U err;

	OSInit();

	SemaphorePtr = OSSemCreate(100);
	PartitionPtr = OSMemCreate(Partition, 100, 32, &err);

	OSTaskCreate(Task, (void *)0, &TaskStk[999], &err);

	OSStart();
}

void Task(void *pdata)
{
	INT8U err;
	INT8U *pblock;

	while (1)
	{
		OSSemPend(SemaphorePtr, 0, &err);
		pblock = OSMemGet(PartitionPtr, &err);

		/* Use the memory block */

		OSMemPut(PartitionPtr, pblock);
		OSSemPost(SemaphorePtr);
	}
}