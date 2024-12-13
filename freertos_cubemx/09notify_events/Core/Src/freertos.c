/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId TaskSendHandle;
osThreadId TaskReceiveHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTaskSend(void const * argument);
void StartTaskReceive(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of TaskSend */
  osThreadDef(TaskSend, StartTaskSend, osPriorityNormal, 0, 128);
  TaskSendHandle = osThreadCreate(osThread(TaskSend), NULL);

  /* definition and creation of TaskReceive */
  osThreadDef(TaskReceive, StartTaskReceive, osPriorityNormal, 0, 128);
  TaskReceiveHandle = osThreadCreate(osThread(TaskReceive), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTaskSend */
/**
  * @brief  Function implementing the TaskSend thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskSend */
void StartTaskSend(void const * argument)
{
  /* USER CODE BEGIN StartTaskSend */
  /* Infinite loop */
  for(;;)
  {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
			{
				printf("将bit0位置1\r\n");
				xTaskNotify(TaskReceiveHandle,0x01,eSetBits);
				
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1 ) == GPIO_PIN_RESET)
			{
				printf("将bit1位置1\r\n");
				xTaskNotify(TaskReceiveHandle,0x02,eSetBits);
				
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
		}
    osDelay(10);
  }
  /* USER CODE END StartTaskSend */
}

/* USER CODE BEGIN Header_StartTaskReceive */
/**
* @brief Function implementing the TaskReceive thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskReceive */
void StartTaskReceive(void const * argument)
{
  /* USER CODE BEGIN StartTaskReceive */
	uint32_t notify_val  = 0, event_bit=0;
  /* Infinite loop */
  for(;;)
  {
		xTaskNotifyWait(0,0xFFFFFFFF, &notify_val,portMAX_DELAY);
		if (notify_val&0x01)
			event_bit|=0x01;
		if (notify_val&0x02)
			event_bit|=0x02;
		if (event_bit==0x03)
		{
			printf("已经同时按下\r\n");
			event_bit=0;
			
		}
			
    osDelay(1);
  }
  /* USER CODE END StartTaskReceive */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

