#define INT8U unsigned char
#define INT16U unsigned short
#define OS_EVENT_TBL_SIZE 10

typedef struct // Event Control Block 구조체
{
	INT8U OSEventType; // Message Queue의 경우 OS_EVENT_TYPE_Q
	INT8U OSEventGrp;
	INT16U OSEventCnt;
	void *OSEventPtr;					 // 메시지 큐(OS_Q) 주소 저장
	INT8U OSEventTbl[OS_EVENT_TBL_SIZE]; // OSEventGrp와 함께 Messagq Queue 때문에 waiting하는 task를 기록
} OS_EVENT;

typedef struct
{
} OS_STK;

typedef struct os_q
{
	struct os_q *OSQPtr;
	void **OSQStart;   // 메시지 주소를 저장할 포인터 배열의 시작 주소
	void **OSQEnd;	   // 포인터 배열의 끝 주소
	void **OSQIn;	   // 메시지를 FIFO 방식으로 추가할 위치
	void **OSQOut;	   // 메시지를 꺼낼 위치
	INT16U OSQSize;	   // 포인터 배열의 크기(메시지 최대 저장 개수)
	INT16U OSQEntries; // 현재 저장된 메시지 개수

} OS_Q;

/* -------------------------------------------------------------------- */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TASK_STK_SIZE 512
#define N_TASKS 2
#define N_MSG 100

#define OS_NO_ERR 0

OS_STK TaskStk[N_TASKS][TASK_STK_SIZE];
OS_STK LogTaskStk[TASK_STK_SIZE];

OS_EVENT *msg_q;
void *msg_array[N_MSG];

void LogTask(void *data);
void Task(void *pdata);
void CreateTasks(void);

int main(void)
{
	OSInit();
	CreateTasks();
	msg_q = OSQCreate(msg_array, (INT16U)N_MSG);

	if (msg_q == 0)
	{
		printf("createing msg_q is failed\n");
		return -1;
	}

	OSStart();
	return 0;
}

void CreateTasks(void)
{
	OSTaskCreate(LogTask, (void *)0, &LogTaskStk[TASK_STK_SIZE - 1], (INT8U)0);
	OSTaskCreate(Task, (void *)0, &TaskStk[TASK_STK_SIZE - 1], (INT8U)10);
	OSTaskCreate(Task, (void *)0, &TaskStk[TASK_STK_SIZE - 1], (INT8U)20);
}

void LogTask(void *data)
{
	FILE *log;
	void *msg;
	INT8U err;

	log = fopen("log.txt", "w");

	while (1)
	{
		msg = OSQPend(msg_q, 0, &err);
		if (msg != 0)
		{
			fprintf(log, "%s", msg);
			fflush(log);
		}
	}
}

void Task(void *pdata)
{
	INT8U sleep, err;
	char msg[10];

	srand(time((unsigned int *)0) + (OSTCBCur->OSTCBPrio));

	while (1)
	{
		sprintf(msg, "%4u: Task %u schedule\n", OSTimeGet(), OSTCBCur->OSTCBPrio);
		err = OSQPost(msg_q, msg);
		while (err != OS_NO_ERR)
			err = OSQPost(msg_q, msg);
		sleep = (rand() % 5 + 1);
		OSTimeDly(sleep);
	}
}