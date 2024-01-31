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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "esp.h"
#include "usart.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RXBUFFERSIZE 512
#define MAINBUFFERSIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t rxbuffer[RXBUFFERSIZE];
uint8_t mainbuffer[MAINBUFFERSIZE];
uint16_t old_write_end, write_end, read_start;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for readEspUart */
osThreadId_t readEspUartHandle;
const osThreadAttr_t readEspUart_attributes = {
  .name = "readEspUart",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartReadEspUart(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of readEspUart */
  readEspUartHandle = osThreadNew(StartReadEspUart, NULL, &readEspUart_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxbuffer, RXBUFFERSIZE);

  send_message("AT+CWINIT=1\r\n");
  osDelay(2000);
  send_message("AT+CWMODE=2\r\n");
  osDelay(2000);
  send_message("AT+CIPMUX=1\r\n");
  osDelay(2000);
  send_message("AT+CWSAP=\"esp32\",\"password\",1,0,3,0\r\n");
  osDelay(2000);
  send_message("AT+CWDHCP=1,1\r\n");
  osDelay(2000);
  send_message("AT+CIPSERVER=1\r\n");
  osDelay(2000);

  /* Infinite loop */
  for(;;)
  {
    // printf("Task1\n");
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartReadEspUart */
/**
* @brief Function implementing the readEspUart thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReadEspUart */
void StartReadEspUart(void *argument)
{
  /* USER CODE BEGIN StartReadEspUart */
  /* Infinite loop */
  for(;;)
  {
    if (write_end != read_start) {
      printf("< ");
      // Read from mainbuffer
      for (; read_start!=write_end; read_start=(read_start+1) % MAINBUFFERSIZE) {
        putchar(mainbuffer[read_start]);
      }
      putchar('\n');
    }
    osDelay(100);
  }
  /* USER CODE END StartReadEspUart */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
  // Idea from https://controllerstech.com/uart-dma-with-idle-line-detection/
  if (huart->Instance == USART1) {
    old_write_end = write_end; // Write position of mainbuffer
    if (old_write_end+size >= MAINBUFFERSIZE) { // When input is too long for end of mainbuffer
      uint16_t datatocopy = MAINBUFFERSIZE - old_write_end;
      memcpy(mainbuffer + old_write_end, rxbuffer, datatocopy); // Copy first part to the end
      old_write_end = 0;
      memcpy(mainbuffer, rxbuffer + datatocopy, (size - datatocopy)); // Copy rest to the start
      write_end = (size - datatocopy);
    }
    else { // When enough space in mainbufferr
      memcpy(mainbuffer + old_write_end, rxbuffer, size);
      write_end = size + old_write_end;
    }
    // Find some string from rxbuffer
    if (strstr((char*)rxbuffer, "ERROR")) {
      printf("Error found\n");
    }
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxbuffer, RXBUFFERSIZE);
  }
}
/* USER CODE END Application */

