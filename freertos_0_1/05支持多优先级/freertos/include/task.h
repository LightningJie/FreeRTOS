#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
//定义任务控制块
typedef struct tskTaskControlBlock
{
	volatile StackType_t    *pxTopOfStack;    /* 栈顶 */

	ListItem_t              xStateListItem;   /* 任务节点 */
    
  StackType_t             *pxStack;         /* 任务栈起始地址 */
	                                          /* 任务名称，字符串形式 */
	char                    pcTaskName[ configMAX_TASK_NAME_LEN ];  
	
	TickType_t xTicksToDelay; /* 用于阻塞延时 */ 
	
	UBaseType_t			uxPriority; //优先级
} tskTCB;
typedef tskTCB TCB_t;

#define taskYIELD()			portYIELD()

#define taskENTER_CRITICAL()  portENTER_CRITICAL()  //关中断
#define taskEXIT_CRITICAL()  portEXIT_CRITICAL()    //开中断

#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()		  //中断中关中断
#define taskEXIT_CRITICAL_FROM_ISR(x) portCLEAR_INTERRUPT_MASK_FROM_ISR(x)		  //中断中开中断

/* 任务句柄 */
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
