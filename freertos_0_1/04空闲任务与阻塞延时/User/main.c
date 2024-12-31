#include "list.h"
#include "task.h"
/*
*************************************************************************
*                              ȫ�ֱ���
*************************************************************************
*/
portCHAR flag1;
portCHAR flag2;


//��������ջ

#define TASK1_STACK_SIZE                    128
StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE                    128
StackType_t Task2Stack[TASK2_STACK_SIZE];

//����������ƿ�
TCB_t Task1TCB;
TCB_t Task2TCB; 

//����������
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;

/*
*************************************************************************
*                               �������� 
*************************************************************************
*/
void delay (uint32_t count);
void Task1_Entry( void *p_arg );
void Task2_Entry( void *p_arg );

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

int main(void)
{
	prvInitialiseTaskLists();
	Task1_Handle=xTaskCreateStatic(Task1_Entry,
																	"Task1_Entry",
																	TASK1_STACK_SIZE,
																	NULL,
																	Task1Stack,
																	&Task1TCB);
	vListInsert(&pxReadyTasksLists[1],&Task1TCB.xStateListItem);
	
	Task2_Handle=xTaskCreateStatic(Task2_Entry,
																	"Task2_Entry",
																	TASK2_STACK_SIZE,
																	NULL,
																	Task2Stack,
																	&Task2TCB);
	
	/* ��������ӵ������б� */                                 
  vListInsertEnd( &( pxReadyTasksLists[2] ), &( ((TCB_t *)(&Task2TCB))->xStateListItem ) );
	vTaskStartScheduler();
	for(;;)
	{
	
	}

}

/*
*************************************************************************
*                               ����ʵ��
*************************************************************************
*/
/* �����ʱ */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}
/* ����1 */
void Task1_Entry( void *p_arg )
{
	for( ;; )
	{
		flag1 = 1;
		vTaskDelay(2);
		flag1 = 0;
		vTaskDelay(2);
	}
}

/* ����2 */
void Task2_Entry( void *p_arg )
{
	for( ;; )
	{
		flag2 = 1;
		vTaskDelay( 2 );		
		flag2 = 0;
		vTaskDelay( 2 );
	}
}

/* ��ȡ����������ڴ� */
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
TCB_t IdleTaskTCB;

void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}
