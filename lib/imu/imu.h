#include <stdio.h>

#define IMU_ADDR 0x68

// Registers
#define REG_CMD 0x7E
#define REG_INT_EN_0 0x50
#define REG_INT_EN_1 0x51
#define REG_INT_EN_2 0x52
#define REG_INT_CTRL 0x53
#define REG_INT_LATCH 0x54
#define REG_INT_MAP_0 0x55
#define REG_INT_MAP_1 0x56
#define REG_INT_MAP_2 0x57
#define REG_ACC_X_0 0x12
#define REG_ACC_X_1 0x13
#define REG_ACC_Y_0 0x14
#define REG_ACC_Y_1 0x15
#define REG_ACC_Z_0 0x16
#define REG_ACC_Z_1 0x17

// CMD register commands
#define CMD_SOFTRESET 0xB6
#define CMD_ACC_NORMAL 0x11
#define CMD_GYRO_NORMAL 0x15
#define CMD_MAG_NORMAL 0x19

// Interrupt enable
#define INT_HIGH_G_EN_X 0x01
#define INT_HIGH_G_EN_Y 0x02
#define INT_HIGH_G_EN_Z 0x03
#define INT_FLAT 0x80

uint8_t softreset();
uint8_t normalmodes();
uint8_t read_acc_x(int16_t *value);
uint8_t read_acc_y(int16_t *value);
uint8_t read_acc_z(int16_t *value);
uint8_t configure_bump_int();
uint8_t configure_slope_int();
uint8_t configure_int();
uint8_t read_register(uint8_t reg);