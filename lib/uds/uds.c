#include "uds.h"
#include "gpio.h"
#include "tim.h"

uint8_t get_distance(float *value) {
    uint32_t startTick, stopTick;
    HAL_GPIO_WritePin(UDS_TRIG_GPIO_Port, UDS_TRIG_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(UDS_TRIG_GPIO_Port, UDS_TRIG_Pin, 0);
    HAL_TIM_Base_Start(&htim11);
    startTick = TIM11->CNT;
    stopTick = TIM11->CNT;

    while (HAL_GPIO_ReadPin(UDS_ECHO_GPIO_Port, UDS_ECHO_Pin) == 0) {
        startTick = TIM11->CNT;
    }
    while (HAL_GPIO_ReadPin(UDS_ECHO_GPIO_Port, UDS_ECHO_Pin) == 1) {
        stopTick = TIM11->CNT;
    }
    *value = (float)(stopTick - startTick) * 343 / 20000;
    HAL_TIM_Base_Stop(&htim11);
    return 0;
}