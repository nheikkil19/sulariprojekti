#include "uds.h"
#include "gpio.h"

uint8_t get_distance(float *value) {
    uint32_t startTick, stopTick;
    HAL_GPIO_WritePin(UDS_TRIG_GPIO_Port, UDS_TRIG_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(UDS_TRIG_GPIO_Port, UDS_TRIG_Pin, 0);
    startTick = HAL_GetTick();
    stopTick = HAL_GetTick();

    while (HAL_GPIO_ReadPin(UDS_ECHO_GPIO_Port, UDS_ECHO_Pin) == 0) {
        startTick = HAL_GetTick();
    }
    while (HAL_GPIO_ReadPin(UDS_ECHO_GPIO_Port, UDS_ECHO_Pin) == 1) {
        stopTick = HAL_GetTick();
    }
    *value = (float)(stopTick - startTick) * 343 / 20;
    return 0;
}