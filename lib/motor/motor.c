#include "motor.h"
#include "gpio.h"
#include "tim.h"

void drive_forwards(uint8_t pwm) {
    // A clockwise
    HAL_GPIO_WritePin(MD_AIN1_GPIO_Port, MD_AIN1_Pin, 1);
    HAL_GPIO_WritePin(MD_AIN2_GPIO_Port, MD_AIN2_Pin, 0);
    // B counterclockwise
    HAL_GPIO_WritePin(MD_BIN1_GPIO_Port, MD_BIN1_Pin, 0);
    HAL_GPIO_WritePin(MD_BIN2_GPIO_Port, MD_BIN2_Pin, 1);
    // PWM duty cycle
    TIM3->CCR2 = (uint16_t)(pwm / 100.f * TIM3->ARR);
    TIM10->CCR1 = (uint16_t)(pwm / 100.f * TIM10->ARR);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    // Start by setting standby 1
    HAL_GPIO_WritePin(MD_STBY_GPIO_Port, MD_STBY_Pin, 1);
}

void drive_backwards(uint8_t pwm) {
    // A counterclockwise
    HAL_GPIO_WritePin(MD_AIN1_GPIO_Port, MD_AIN1_Pin, 0);
    HAL_GPIO_WritePin(MD_AIN2_GPIO_Port, MD_AIN2_Pin, 1);
    // B clockwise
    HAL_GPIO_WritePin(MD_BIN1_GPIO_Port, MD_BIN1_Pin, 1);
    HAL_GPIO_WritePin(MD_BIN2_GPIO_Port, MD_BIN2_Pin, 0);
    // PWM duty cycle
    TIM3->CCR2 = (uint16_t)(pwm / 100.f * TIM3->ARR);
    TIM10->CCR1 = (uint16_t)(pwm / 100.f * TIM10->ARR);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    // Start by setting standby 1
    HAL_GPIO_WritePin(MD_STBY_GPIO_Port, MD_STBY_Pin, 1);
}

void drive_left(uint8_t pwm) {
    // A clockwise
    HAL_GPIO_WritePin(MD_AIN1_GPIO_Port, MD_AIN1_Pin, 0);
    HAL_GPIO_WritePin(MD_AIN2_GPIO_Port, MD_AIN2_Pin, 1);
    // B clockwise
    HAL_GPIO_WritePin(MD_BIN1_GPIO_Port, MD_BIN1_Pin, 0);
    HAL_GPIO_WritePin(MD_BIN2_GPIO_Port, MD_BIN2_Pin, 1);
    // PWM duty cycle
    TIM3->CCR2 = (uint16_t)(pwm / 100.f * TIM3->ARR);
    TIM10->CCR1 = (uint16_t)(pwm / 100.f * TIM10->ARR);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    // Start by setting standby 1
    HAL_GPIO_WritePin(MD_STBY_GPIO_Port, MD_STBY_Pin, 1);
}
void drive_right(uint8_t pwm) {
    // A counterclockwise
    HAL_GPIO_WritePin(MD_AIN1_GPIO_Port, MD_AIN1_Pin, 1);
    HAL_GPIO_WritePin(MD_AIN2_GPIO_Port, MD_AIN2_Pin, 0);
    // B counterclockwise
    HAL_GPIO_WritePin(MD_BIN1_GPIO_Port, MD_BIN1_Pin, 1);
    HAL_GPIO_WritePin(MD_BIN2_GPIO_Port, MD_BIN2_Pin, 0);
    // PWM duty cycle
    TIM3->CCR2 = (uint16_t)(pwm / 100.f * TIM3->ARR);
    TIM10->CCR1 = (uint16_t)(pwm / 100.f * TIM10->ARR);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    // Start by setting standby 1
    HAL_GPIO_WritePin(MD_STBY_GPIO_Port, MD_STBY_Pin, 1);
}

void motor_stop() {
    HAL_GPIO_WritePin(MD_STBY_GPIO_Port, MD_STBY_Pin, 0);
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);
}