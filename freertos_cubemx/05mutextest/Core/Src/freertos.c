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
osThreadId taskHHandle;
osThreadId taskNHandle;
osThreadId taskLHandle;
osSemaphoreId myBinarySemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTaskH(void const * argument);
void StartTaskN(void const * argument);
void StartTaskL(void const * argument);

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

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem */
  osSemaphoreDef(myBinarySem);
  myBinarySemHandle = osSemaphoreCreate(osSemaphore(myBinarySem), 1);

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
  /* definition and creation of taskH */
  osThreadDef(taskH, StartTaskH, osPriorityAboveNormal, 0, 128);
  taskHHandle = osThreadCreate(osThread(taskH), NULL);

  /* definition and creation of taskN */
  osThreadDef(taskN, StartTaskN, osPriorityNormal, 0, 128);
  taskNHandle = osThreadCreate(osThread(taskN), NULL);

  /* definition and creation of taskL */
  osThreadDef(taskL, StartTaskL, osPriorityBelowNormal, 0, 128);
  taskLHandle = osThreadCreate(osThread(taskL), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTaskH */
/**
  * @brief  Function implementing the taskH thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskH */
void StartTaskH(void const * argument)
{
  /* USER CODE BEGIN StartTaskH */
  /* Infinite loop */
  for(;;)
  {
		xSemaphoreTake(myBinarySemHandle,portMAX_DELAY);
		printf("taskH:我开始进入厕所。。。。\r\n");
		HAL_Delay(1000);
		printf("taskH:我从厕所出来了。。。。\r\n");
		xSemaphoreGive(myBinarySemHandle);
    osDelay(1000);
  }
  /* USER CODE END StartTaskH */
}

/* USER CODE BEGIN Header_StartTaskN */
/**
* @brief Function implementing the taskN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskN */
void StartTaskN(void const * argument)
{
  /* USER CODE BEGIN StartTaskN */
  /* Infinite loop */
  for(;;)
  {
    printf("taskN:我就是用用cpu， 我不上厕所 \r\n");
    osDelay(1000);
  }
  /* USER CODE END StartTaskN */
}

/* USER CODE BEGIN Header_StartTaskL */
/**
* @brief Function implementing the taskL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskL */
void StartTaskL(void const * argument)
{
  /* USER CODE BEGIN StartTaskL */
  /* Infinite loop */
  for(;;)
  {
		xSemaphoreTake(myBinarySemHandle,portMAX_DELAY);
		printf("taskL:我开始进入厕所。。。。\r\n");
		HAL_Delay(3000);
		printf("taskL：我出来了。。。。\r\n");
		xSemaphoreGive(myBinarySemHandle);
    osDelay(1000);
  }
  /* USER CODE END StartTaskL */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

