#include "INCLUDES.H"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK_STK_SIZE 100
#define MsgTblSize 100

OS_STK TaskStk[3][TASK_STK_SIZE];

OS_EVENT *MsgQ;
void *MsgTbl[MsgTblSize];

void LogTask(void *pdata);
void Task(void *pdata);
void TaskCreate(void);

OS_MEM *PartitionPtr;
INT8U Partition[MsgTblSize];

int main(void)
{
	INT8U err;

	OSInit();

	PartitionPtr = OSMemCreate(Partition, 100, 10, &err);
	if (PartitionPtr == (void *)0)
	{
		printf("creating partition is failed.\n");
		return 0;
	}

	MsgQ = OSQCreate(MsgTbl, (INT16U)MsgTblSize);
	if (MsgQ == (void *)0)
	{
		printf("creating message Queue is failed.\n");
		return 0;
	}

	TaskCreate();

	OSStart();
	return 0;
}

void TaskCreate(void)
{
	OSTaskCreate(LogTask, (void *)0, &TaskStk[0][TASK_STK_SIZE - 1], (INT8U)0);
	OSTaskCreate(Task, (void *)0, &TaskStk[1][TASK_STK_SIZE - 1], (INT8U)10);
	OSTaskCreate(Task, (void *)0, &TaskStk[2][TASK_STK_SIZE - 1], (INT8U)20);
}

void LogTask(void *pdata)
{
	void *msg;
	INT8U sleep_count = 0, sleep_time, i, err;
	FILE *log;
	OS_Q_DATA q_data;

	srand(time((unsigned int *)0));
	log = fopen("log.txt", "w");

	while (1)
	{
		OSQQuery(MsgQ, &q_data);
		for (i = 0; i < q_data.OSNMsgs; i++)
		{
			msg = OSQPend(MsgQ, 0, &err);
			if (msg != 0)
			{
				fprintf(log, "%3u: %s", sleep_count, msg);
				fflush(log);
			}
			OSMemPut(PartitionPtr, msg);
		}
		if (sleep_count == 255)
			sleep_count = 0;
		else
			sleep_count++;
		sleep_time = (INT8U)(rand() % 300) + 1;
		OSTimeDly(sleep_time);
	}
}

void Task(void *pdata)
{
	void *msg;
	INT8U sleep, err;

	srand(time((unsigned int *)0) + (OSTCBCur->OSTCBPrio));

	while (1)
	{
		msg = OSMemGet(PartitionPtr, &err);
		sprintf(msg, "%4u %3u\n", OSTimeGet(), OSTCBCur->OSTCBPrio);

		OSQPost(MsgQ, msg);

		sleep = (INT8U)(rand() % 5 + 1);
		OSTimeDly(sleep);
	}
}