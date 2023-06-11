#define INT8U unsigned char
#define INT16U unsigned short
#define OS_EVENT_TBL_SIZE 10

typedef struct // Event Control Block 구조체
{
	INT8U OSEventType; // Semaphore의 경우 OS_EVENT_TYPE_SEM
	INT8U OSEventGrp;
	INT16U OSEventCnt; // 세마포어 카운트 저장
	void *OSEventPtr;
	INT8U OSEventTbl[OS_EVENT_TBL_SIZE]; // Event를 위한 Waiting list
} OS_EVENT;

typedef struct
{
} OS_STK;

/* ------- */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TASK_STK_SIZE 512
#define N_TASKS 5

OS_STK TaskStk[N_TASKS][TASK_STK_SIZE];

void Task(void *data);
void CreateTask(void);

int main(void)
{
	OSInit();

	srand(time(NULL));

	CreateTask();
	OSStart();
	return 0;
}

void CreateTask(void)
{
	INT8U i;

	for (i = 0; i < N_TASKS; i++)
		OSTaskCreate(Task, (void *)0, &TaskStk[i][TASK_STK_SIZE - 1], (INT8U)(i + 1));
}

void Task(void *pdata)
{
	FILE *out;
	INT8U sleep;

	while (1)
	{
		out = fopen("result.txt", "a");

		fprintf(out, "%4u: Task %u, file open\n", OSTimeGet(), OSTCBCur->OSTCBPrio);
		fflush(out);
		Sleep(rand() % 3) + 1;
		OSTimeDly(sleep);

		fprintf(out, "%4u: Task %u, file close\n", OSTimeGet(), OSTCBCur->OSTCBPrio);
		fflush(out);
		fclose(out);
		Sleep(rand() % 3) + 1;
		OSTimeDly(sleep);
	}
}