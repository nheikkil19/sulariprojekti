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
#define REG_GYRO_X_0 0x0C
#define REG_GYRO_X_1 0x0D
#define REG_GYRO_Y_0 0x0E
#define REG_GYRO_Y_1 0x0F
#define REG_GYRO_Z_0 0x10
#define REG_GYRO_Z_1 0x11
#define REG_MAG_X_0 0x04
#define REG_MAG_X_1 0x05
#define REG_MAG_Y_0 0x06
#define REG_MAG_Y_1 0x07
#define REG_MAG_Z_0 0x08
#define REG_MAG_Z_1 0x09
#define REG_MAG_CONF 0x44
#define REG_MAG_IF_0 0x4C
#define REG_MAG_IF_1 0x4D
#define REG_MAG_IF_2 0x4E
#define REG_MAG_IF_3 0x4F
#define REG_INT_STATUS_0 0x1C
#define REG_INT_STATUS_1 0x1D
#define REG_INT_STATUS_2 0x1E
#define REG_INT_STATUS_3 0x1F
#define REG_INT_FLAT_0 0x67
#define REG_INT_FLAT_1 0x68
#define REG_INT_LOWHIGH_0 0x5A
#define REG_INT_LOWHIGH_1 0x5B
#define REG_INT_LOWHIGH_2 0x5C
#define REG_INT_LOWHIGH_3 0x5D
#define REG_INT_LOWHIGH_4 0x5E
#define REG_FOC_CONF 0x69
#define REG_STATUS 0x1B
#define REG_OFFSET_0 0x71
#define REG_OFFSET_1 0x72
#define REG_OFFSET_2 0x73
#define REG_OFFSET_3 0x74
#define REG_OFFSET_4 0x75
#define REG_OFFSET_5 0x76
#define REG_OFFSET_6 0x77

// CMD register commands
#define CMD_SOFTRESET 0xB6
#define CMD_ACC_NORMAL 0x11
#define CMD_GYRO_NORMAL 0x15
#define CMD_MAG_NORMAL 0x19
#define CMD_START_FOC 0x03

// Interrupt enable
#define INT_FLAT (0x01 << 7)
#define INT_HIGH_G_EN_X (0x01 << 0)
#define INT_HIGH_G_EN_Y (0x01 << 1)
#define INT_HIGH_G_EN_Z (0x01 << 2)
#define INT_DATA_READY (0x01 << 4)

int16_t acc_x, acc_y, acc_z;

uint8_t softreset();
uint8_t normalmodes();
uint8_t setup_mag();
uint8_t fast_offset_compensation();
uint8_t read_acc_x(int16_t *value);
uint8_t read_acc_y(int16_t *value);
uint8_t read_acc_z(int16_t *value);
uint8_t read_gyro_x(int16_t *value);
uint8_t read_gyro_y(int16_t *value);
uint8_t read_gyro_z(int16_t *value);
uint8_t read_mag_x(int16_t *value);
uint8_t read_mag_y(int16_t *value);
uint8_t read_mag_z(int16_t *value);
uint8_t configure_bump_interrupt();
uint8_t configure_slope_interrupt();
uint8_t configure_interrupt_pins();
uint8_t configure_data_ready_interrupt();
uint8_t write_register(uint8_t reg, uint8_t value);
uint8_t read_register(uint8_t reg,  uint8_t *value);
uint8_t print_register(uint8_t reg);