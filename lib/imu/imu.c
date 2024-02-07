#include "imu.h"
#include "i2c.h"

uint8_t softreset() {
    uint8_t err;
    uint8_t tx_buffer[] = {0x7E, 0xB6};
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    HAL_Delay(15);
    return err;
}

uint8_t normalmodes() {
    uint8_t err;
    uint8_t tx_buffer[] = {0x7E, 0x11}; // cmd register, acc normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    HAL_Delay(50);
    if (err) return 1;
    tx_buffer[1] = 0x15; // gyro normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    HAL_Delay(100);
    if (err) return 2;
    tx_buffer[1] = 0x11; // mag normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    HAL_Delay(100);
    if (err) return 3;
    return 0;
}

uint8_t read_acc_x(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {0x12}; // acc_x register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 1;
    // HAL_Delay(100);
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 2;
    *value = rx_buffer[0];
    tx_buffer[0] = 0x13; // acc_x register part 1
    // HAL_Delay(100);
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 3;
    // HAL_Delay(100);
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 4;
    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}

uint8_t read_acc_y(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {0x14}; // acc_y register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 1;
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 2;
    *value = rx_buffer[0];
    tx_buffer[0] = 0x15; // acc_y register part 2
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 3;
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 4;
    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}
uint8_t read_acc_z(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {0x16}; // acc_z register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 1;
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 2;
    *value = rx_buffer[0];
    tx_buffer[0] = 0x17; // acc_z register part 2
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) return 3;
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) return 4;
    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}

uint8_t configure_acc_int() {
    uint8_t err;
    uint8_t tx_buffer[] = {0x51, 0x02}; // int_en[1], enable high g z
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
}
