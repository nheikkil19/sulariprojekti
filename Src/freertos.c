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
#include "uds.h"
#include "atomic.h"
#include "motor.h"
#include "imu.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum State {
  INIT,
  STOP,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD
} state = INIT;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RXBUFFERSIZE 128
#define MAINBUFFERSIZE 256
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t rxbuffer[RXBUFFERSIZE];
uint8_t mainbuffer[MAINBUFFERSIZE];
uint16_t old_write_end, write_end, read_start;
uint8_t speed = 50;

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
/* Definitions for distanceSensor */
osThreadId_t distanceSensorHandle;
const osThreadAttr_t distanceSensor_attributes = {
  .name = "distanceSensor",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for sendDataTask */
osThreadId_t sendDataTaskHandle;
const osThreadAttr_t sendDataTask_attributes = {
  .name = "sendDataTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartReadEspUart(void *argument);
void StartDistanceSensor(void *argument);
void StartSendDataTask(void *argument);

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

  /* creation of distanceSensor */
  distanceSensorHandle = osThreadNew(StartDistanceSensor, NULL, &distanceSensor_attributes);

  /* creation of sendDataTask */
  sendDataTaskHandle = osThreadNew(StartSendDataTask, NULL, &sendDataTask_attributes);

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
  reset_esp();
  echo_off();
  open_socket();
  enable_wifi();
  // Set state to stop after init done
  Atomic_CompareAndSwap_u32((uint32_t*)&state, STOP, state);
  printf("ESP init done\n");
  /* Infinite loop */
  for(;;)
  {
    if (state == STOP) {
      motor_stop();
    }
    else if (state == FORWARD) {
      drive_forwards(speed);
    }
    else if (state == BACKWARD) {
      drive_backwards(speed);
    }
    else if (state == LEFT) {
      drive_left(40);
    }
    else if (state == RIGHT) {
      drive_right(40);
    }
    osDelay(100);
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

/* USER CODE BEGIN Header_StartDistanceSensor */
/**
* @brief Function implementing the distanceSensor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDistanceSensor */
void StartDistanceSensor(void *argument)
{
  /* USER CODE BEGIN StartDistanceSensor */
  float dist;
  // Wait until esp is ready
  while (state == INIT) osDelay(500);
  /* Infinite loop */
  for(;;)
  {
    get_distance(&dist);
    if (dist < 20) {
      Atomic_CompareAndSwap_u32((uint32_t*)&state, STOP, state);
    }
    osDelay(200);
  }
  /* USER CODE END StartDistanceSensor */
}

/* USER CODE BEGIN Header_StartSendDataTask */
/**
* @brief Function implementing the sendDataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendDataTask */
void StartSendDataTask(void *argument)
{
  /* USER CODE BEGIN StartSendDataTask */
  /* Infinite loop */
  char msg[64];
  int16_t mag_x, mag_y, mag_z;

  // Wait until esp is ready
  while (state == INIT) osDelay(500);
  for(;;)
  {
    read_mag_x(&mag_x);
    read_mag_y(&mag_y);
    read_mag_z(&mag_z);
    snprintf(msg, 64, "%d,%d,%d\r\n", mag_x, mag_y, mag_z);
    send_tcp_message(msg);
    osDelay(1000);
  }
  /* USER CODE END StartSendDataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
  uint8_t *start;
  uint8_t const margin = 12;
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
    // First check if string is in rxbuffer, then check it in the start of the buffer.
    // Otherwise it might find old strings from end of the buffer
    if ((start = (uint8_t*)strstr((char*)rxbuffer, "stop")) && start < rxbuffer + margin) {
      printf("1\n");
      Atomic_CompareAndSwap_u32((uint32_t*)&state, STOP, state);
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "forward")) && start < rxbuffer + margin) {
      printf("2\n");
      Atomic_CompareAndSwap_u32((uint32_t*)&state, FORWARD, state);
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "back")) && start < rxbuffer + margin) {
      printf("3\n");
      Atomic_CompareAndSwap_u32((uint32_t*)&state, BACKWARD, state);
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "left")) && start < rxbuffer + margin) {
      printf("4\n");
      Atomic_CompareAndSwap_u32((uint32_t*)&state, LEFT, state);
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "right")) && start < rxbuffer + margin) {
      printf("5\n");
      Atomic_CompareAndSwap_u32((uint32_t*)&state, RIGHT, state);
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "faster")) && start < rxbuffer + margin) {
      if (speed <= 90) {
        Atomic_Add_u32((uint32_t*)&speed, 10);
      }
    }
    else if ((start = (uint8_t*)strstr((char*)rxbuffer, "slower")) && start < rxbuffer + margin) {
      if (speed >= 20) {
        Atomic_Subtract_u32((uint32_t*)&speed, 10);
      }
    }
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxbuffer, RXBUFFERSIZE);
  }
}
/* USER CODE END Application */

