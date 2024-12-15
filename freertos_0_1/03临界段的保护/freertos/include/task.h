#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"

#define taskYIELD()			portYIELD()

#define taskENTER_CRITICAL()  portENTER_CRITICAL()  //关中断
#define taskEXTI_CRITICAL()  portEXTI_CRITICAL()    //开中断

#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()		  //中断中关中断
#define taskEXTI_CRITICAL_FROM_ISR(x) portCLEAR_INTERRUPT_MASK_FROM_ISR(x)		  //中断中开中断

/* 任务句柄 */
typedef void * TaskHandle_t;


#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
					            const char * const pcName,
					            const uint32_t ulStackDepth,
					            void * const pvParameters,
					            StackType_t * const puxStackBuffer,
					            TCB_t * const pxTaskBuffer );
#endif /* configSUPPORT_STATIC_ALLOCATION */
                                
void prvInitialiseTaskLists( void );                                
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
                                
#endif /* INC_TASK_H */ 
