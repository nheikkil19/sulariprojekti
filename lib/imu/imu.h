#include <stdio.h>

#define IMU_ADDR 0x68

uint8_t softreset();
uint8_t normalmodes();
uint8_t read_acc_x(int16_t *value);
uint8_t read_acc_y(int16_t *value);
uint8_t read_acc_z(int16_t *value);
