/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
osThreadId taskLED1Handle;
osThreadId taskLED2Handle;
osThreadId taskKEY1Handle;
osThreadId taskKEY2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTaskLED1(void const * argument);
void StartTaskLED2(void const * argument);
void StartTaskKEY1(void const * argument);
void StartTaskKEY2(void const * argument);

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
  /* definition and creation of taskLED1 */
  osThreadDef(taskLED1, StartTaskLED1, osPriorityNormal, 0, 128);
  taskLED1Handle = osThreadCreate(osThread(taskLED1), NULL);

  /* definition and creation of taskLED2 */
  osThreadDef(taskLED2, StartTaskLED2, osPriorityNormal, 0, 128);
  taskLED2Handle = osThreadCreate(osThread(taskLED2), NULL);

  /* definition and creation of taskKEY1 */
  osThreadDef(taskKEY1, StartTaskKEY1, osPriorityNormal, 0, 128);
  taskKEY1Handle = osThreadCreate(osThread(taskKEY1), NULL);

  /* definition and creation of taskKEY2 */
  osThreadDef(taskKEY2, StartTaskKEY2, osPriorityNormal, 0, 128);
  taskKEY2Handle = osThreadCreate(osThread(taskKEY2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTaskLED1 */
/**
  * @brief  Function implementing the taskLED1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskLED1 */
void StartTaskLED1(void const * argument)
{
  /* USER CODE BEGIN StartTaskLED1 */
  /* Infinite loop */
  for(;;)
  {	
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
    osDelay(500);
  }
  /* USER CODE END StartTaskLED1 */
}

/* USER CODE BEGIN Header_StartTaskLED2 */
/**
* @brief Function implementing the t askLED2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLED2 */
void StartTaskLED2(void const * argument)
{
  /* USER CODE BEGIN StartTaskLED2 */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_9);
    osDelay(1000);
  }
  /* USER CODE END StartTaskLED2 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the taskKEY1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTaskKEY1(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
		{
			osDelay(20);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
			{
				printf("KEY1����!\r\n");
				if(taskLED1Handle==NULL)
				{
					printf("����1�����ڣ�׼����������\r\n");
					osThreadDef(taskLED1, StartTaskLED1, osPriorityNormal, 0, 128);
					taskLED1Handle = osThreadCreate(osThread(taskLED1), NULL);
					if(taskLED1Handle!=NULL)
					{
						printf("����1������ɣ�\r\n");
					}
				}
				else{
					printf("ɾ��������\r\n");
					osThreadTerminate(taskLED1Handle);
					taskLED1Handle=NULL;
				}
			}
		}
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET);
    osDelay(10);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTaskKEY2 */
/**
* @brief Function implementing the taskKEY2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskKEY2 */
void StartTaskKEY2(void const * argument)
{
		/* USER CODE BEGIN StartTaskKEY2 */
		static int flag=1;
		/* Infinite loop */
		for(;;)
		{
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET)
			{
				osDelay(20);
				if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET)
				{
					printf("KEY2����!\r\n");
					if(flag==0)
					{
						osThreadSuspend(taskLED2Handle);
						printf("����2����ͣ\r\n");
						flag=1;
					}
					else{
						osThreadResume(taskLED2Handle);
						printf("����2�ѻָ�\r\n");
						flag=0;
					}
				}
			}
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET);
    osDelay(10);
		}
  /* USER CODE END StartTaskKEY2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

