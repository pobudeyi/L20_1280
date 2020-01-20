/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "bsp_uart.h"
#include "usart.h"
#include "QMA6981.h"
#include "stdio.h"
#include "string.h"
#include "2G4.h"
#include "at_cmd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
	  extern uint16_t tmp_cnt;
	__IO float tmp_vaule;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId qma6981Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void qma6981_task(void const * argument);

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of qma6981 */
  osThreadDef(qma6981, qma6981_task, osPriorityNormal, 0, 256);
  qma6981Handle = osThreadCreate(osThread(qma6981), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  //USART_RECEIVETYPE *ucQueueMsgValue;
  /* Infinite loop */
  for(;;)
  {
    // xQueueReceive(xRS232SendQueue3,(USART_RECEIVETYPE *)&ucQueueMsgValue,(TickType_t)portMAX_DELAY); //portMAX_DELAY
    // if(ucQueueMsgValue->rx_len==1)
    //     HAL_UART_Receive_DMA(&huart1,ucQueueMsgValue->usartDMA_rxBuf,RECEIVELEN);
    // ucQueueMsgValue->usartDMA_rxBuf[ucQueueMsgValue->rx_len]=0;
    //HAL_UART_Transmit_DMA(&huart1,(uint8_t *)ucQueueMsgValue->usartDMA_rxBuf,ucQueueMsgValue->rx_len);//获取gps信息
    //HAL_UART_Transmit_DMA(&huart1,(uint8_t *)&ucQueueMsgValue->receive_flag,1);//获取gps信息
    //printf("%d-%s",ucQueueMsgValue->receive_flag,ucQueueMsgValue->usartDMA_rxBuf);
    //ucQueueMsgValue->receive_flag=0;
    lorawan_at_process();
    //osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_qma6981_task */
/**
* @brief Function implementing the qma6981 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_qma6981_task */
void qma6981_task(void const * argument)
{
  /* USER CODE BEGIN qma6981_task */
  /* Infinite loop */
  char temp_data[64]={0};
  uint16_t a,b;
  QMA6981Init();
  for(;;)
  {
    osDelay(1000);
    memset(temp_data,0,sizeof(temp_data));
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
    tmp_cnt=0;
    osDelay(50);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
    tmp_vaule=(float)tmp_cnt*0.0625-50.0625;
    a=(uint16_t)tmp_vaule*1000;
    b=tmp_vaule*1000-a;
    sprintf(temp_data,"%d-%d.%d\r\n",tmp_cnt,(uint16_t)tmp_vaule,b);
    printf("%s",temp_data);
  }
  /* USER CODE END qma6981_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
