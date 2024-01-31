/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define INT_ACC_Pin GPIO_PIN_0
#define INT_ACC_GPIO_Port GPIOA
#define UDS_TRIG_Pin GPIO_PIN_4
#define UDS_TRIG_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define MD_BIN1_Pin GPIO_PIN_6
#define MD_BIN1_GPIO_Port GPIOA
#define MD_STBY_Pin GPIO_PIN_7
#define MD_STBY_GPIO_Port GPIOA
#define UDS_ECHO_Pin GPIO_PIN_0
#define UDS_ECHO_GPIO_Port GPIOB
#define INT_GYR_Pin GPIO_PIN_10
#define INT_GYR_GPIO_Port GPIOB
#define MD_AIN2_Pin GPIO_PIN_7
#define MD_AIN2_GPIO_Port GPIOC
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_4
#define I2C_SDA_GPIO_Port GPIOB
#define MD_PWMA_Pin GPIO_PIN_5
#define MD_PWMA_GPIO_Port GPIOB
#define MD_AIN1_Pin GPIO_PIN_6
#define MD_AIN1_GPIO_Port GPIOB
#define MD_PWMB_Pin GPIO_PIN_8
#define MD_PWMB_GPIO_Port GPIOB
#define MD_BIN2_Pin GPIO_PIN_9
#define MD_BIN2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
