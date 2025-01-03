#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
//����������ƿ�
typedef struct tskTaskControlBlock
{
	volatile StackType_t    *pxTopOfStack;    /* ջ�� */

	ListItem_t              xStateListItem;   /* ����ڵ� */
    
  StackType_t             *pxStack;         /* ����ջ��ʼ��ַ */
	                                          /* �������ƣ��ַ�����ʽ */
	char                    pcTaskName[ configMAX_TASK_NAME_LEN ];  
	
	TickType_t xTicksToDelay; /* ����������ʱ */ 
	
	UBaseType_t			uxPriority; //���ȼ�
} tskTCB;
typedef tskTCB TCB_t;

#define taskYIELD()			portYIELD()

#define taskENTER_CRITICAL()  portENTER_CRITICAL()  //���ж�
#define taskEXIT_CRITICAL()  portEXIT_CRITICAL()    //���ж�

#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()		  //�ж��й��ж�
#define taskEXIT_CRITICAL_FROM_ISR(x) portCLEAR_INTERRUPT_MASK_FROM_ISR(x)		  //�ж��п��ж�

/* ������ */
typedef void * TaskHandle_t;


#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
					            const char * const pcName,
					            const uint32_t ulStackDepth,
					            void * const pvParameters,
											UBaseType_t uxPriority,              
					            StackType_t * const puxStackBuffer,
					            TCB_t * const pxTaskBuffer );
#endif /* configSUPPORT_STATIC_ALLOCATION */
                                
void prvInitialiseTaskLists( void );                                
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
void xTaskIncrementTick( void );         
void vTaskDelay( const TickType_t xTicksToDelay );											
#endif /* INC_TASK_H */ 
