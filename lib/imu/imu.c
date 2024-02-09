#include "imu.h"
#include "i2c.h"

uint8_t softreset() {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_CMD, CMD_SOFTRESET};
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Softreset error: %d\n", err);
        return 1;
    }
    HAL_Delay(15);
    return err;
}

uint8_t normalmodes() {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_CMD, CMD_ACC_NORMAL}; // cmd register, acc normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Acc normal mode error: %d\n", err);
        return 1;
    }
    HAL_Delay(50);
    tx_buffer[1] = CMD_GYRO_NORMAL; // gyro normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Gyro normal mode error: %d\n", err);
        return 2;
    }
    HAL_Delay(100);
    tx_buffer[1] = CMD_MAG_NORMAL; // mag normal mode
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Mag normal mode error: %d\n", err);
        return 3;
    }
    HAL_Delay(100);
    return 0;
}

uint8_t read_acc_x(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_ACC_X_0}; // acc_x register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc x error 1: %d\n", err);
        return 1;
    }
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc x error 2: %d\n", err);
        return 2;
    }
    *value = rx_buffer[0];
    tx_buffer[0] = REG_ACC_X_1; // acc_x register part 1
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc x error 3: %d\n", err);
        return 3;
    }
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc x error 4: %d\n", err);
        return 4;
    }
    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}

uint8_t read_acc_y(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_ACC_Y_0}; // acc_y register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc y error 1: %d\n", err);
        return 1;
    }    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc y error 2: %d\n", err);
        return 2;
    }    *value = rx_buffer[0];
    tx_buffer[0] = REG_ACC_Y_1; // acc_y register part 2
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc y error 3: %d\n", err);
        return 3;
    }    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc y error 4: %d\n", err);
        return 4;
    }    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}
uint8_t read_acc_z(int16_t *value) {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_ACC_Z_0}; // acc_z register part 1
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc z error 1: %d\n", err);
        return 1;
    }    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc z error 2: %d\n", err);
        return 2;
    }    *value = rx_buffer[0];
    tx_buffer[0] = REG_ACC_Z_1; // acc_z register part 2
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read acc z error 3: %d\n", err);
        return 3;
    }    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read acc z error 4: %d\n", err);
        return 4;
    }    *value = (*value) | (rx_buffer[0] << 8);
    return 0;
}

uint8_t configure_bump_int() {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_INT_EN_1, INT_HIGH_G_EN_Z}; // int_en[1], enable high g z
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Bump interrupt init error 1: %d\n", err);
        return 1;
    }
    HAL_Delay(100);
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Bump interrupt init error: %d\n", err);
        return 2;
    }
    HAL_Delay(100);
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Bump interrupt init error: %d\n", err);
        return 3;
    }
    printf("configured bump\n");
    HAL_Delay(100);
    return 0;
}

uint8_t configure_slope_int() {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_INT_EN_0, INT_FLAT}; // int_en[0], flat detection
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Slope interrupt init error: %d\n", err);
        return 1;
    }
    HAL_Delay(100);
    printf("configured slope\n");
    return 0;
}

uint8_t configure_int() {
    uint8_t err;
    uint8_t tx_buffer[] = {REG_INT_CTRL, 0xBB}; // int_ctrl , 1011 1011 (int enabled, push-pull, active high, edge)
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Interrupt ctrl error: %d\n", err);
        return 1;
    }
    HAL_Delay(100);
    tx_buffer[0] = REG_INT_LATCH;
    tx_buffer[1] = 0x33; // 0011 0011 (enable INT 2 and INT 1, 1.25ms duration)
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Interrupt latch error: %d\n", err);
        return 2;
    }
    HAL_Delay(100);
    tx_buffer[0] = REG_INT_MAP_0;
    tx_buffer[1] = 0x80; // Flat (slope) detection to INT 1
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Interrupt 1 map error: %d\n", err);
        return 3;
    }
    HAL_Delay(100);
    tx_buffer[0] = REG_INT_MAP_2;
    tx_buffer[1] = 0x02; // High G (bump) detection to INT 2
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Interrupt 2 map error: %d\n", err);
        return 4;
    }
    HAL_Delay(100);
    printf("configured ints\n");
    return 0;
}

uint8_t read_register(uint8_t reg) {
    uint8_t err;
    uint8_t tx_buffer[] = {reg};
    uint8_t rx_buffer[1];
    // Request value
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 1, 1000);
    if (err) {
        printf("Read reg error 1: %d\n", err);
        return 1;
    }
    // Read value
    err = HAL_I2C_Master_Receive(&hi2c3, (IMU_ADDR << 1) | 1, rx_buffer, 1, 1000);
    if (err) {
        printf("Read reg error 2: %d\n", err);
        return 2;
    }
    printf("REG %x: %x\n", reg, rx_buffer[0]);
    return 0;
}
