#include "imu.h"
#include "i2c.h"

uint8_t softreset() {
    uint8_t err;
    err = write_register(REG_CMD, CMD_SOFTRESET);
    if (err) {
        printf("Softreset error: %d\n", err);
        return 1;
    }
    HAL_Delay(15);
    return err;
}

uint8_t normalmodes() {
    uint8_t err;
    err = write_register(REG_CMD, CMD_ACC_NORMAL);
    if (err) {
        printf("Acc normal mode error: %d\n", err);
        return 1;
    }
    HAL_Delay(50);
    err = write_register(REG_CMD, CMD_GYRO_NORMAL);
    if (err) {
        printf("Gyro normal mode error: %d\n", err);
        return 2;
    }
    HAL_Delay(100);
    err = write_register(REG_CMD, CMD_MAG_NORMAL);
    if (err) {
        printf("Mag normal mode error: %d\n", err);
        return 3;
    }
    HAL_Delay(100);
    return 0;
}

uint8_t setup_mag() {
    uint8_t err;
    err = write_register(REG_MAG_IF_0, 0x80);
    if (err) {
        printf("Mag setup error 1: %d\n", err);
        return 1;
    }
    err = write_register(REG_MAG_IF_3, 0x01);
    if (err) {
        printf("Mag setup error 2: %d\n", err);
        return 2;
    }
    err = write_register(REG_MAG_IF_2, 0x4B);
    if (err) {
        printf("Mag setup error 3: %d\n", err);
        return 3;
    }
    err = write_register(REG_MAG_IF_3, 0x01);
    if (err) {
        printf("Mag setup error 4: %d\n", err);
        return 4;
    }
    err = write_register(REG_MAG_IF_2, 0x04);
    if (err) {
        printf("Mag setup error 5: %d\n", err);
        return 5;
    }
    err = write_register(REG_MAG_IF_3, 0x0E);
    if (err) {
        printf("Mag setup error 6: %d\n", err);
        return 6;
    }
    err = write_register(REG_MAG_IF_2, 0x0E);
    if (err) {
        printf("Mag setup error 7: %d\n", err);
        return 7;
    }
    err = write_register(REG_MAG_IF_3, 0x02);
    if (err) {
        printf("Mag setup error 8: %d\n", err);
        return 8;
    }
    err = write_register(REG_MAG_IF_2, 0x4C);
    if (err) {
        printf("Mag setup error 9: %d\n", err);
        return 9;
    }
    err = write_register(REG_MAG_IF_1, 0x42);
    if (err) {
        printf("Mag setup error 10: %d\n", err);
        return 10;
    }
    err = write_register(REG_MAG_CONF, 0x08);
    if (err) {
        printf("Mag setup error 11: %d\n", err);
        return 11;
    }
    err = write_register(REG_MAG_IF_0, 0x00);
    if (err) {
        printf("Mag setup error 12: %d\n", err);
        return 12;
    }
    err = write_register(REG_CMD, 0x1A);
    if (err) {
        printf("Mag setup error 13: %d\n", err);
        return 13;
    }
    return 0;
}

uint8_t fast_offset_compensation() {
    uint8_t err;
    err = write_register(REG_FOC_CONF, 0x7D); // set target values for gyro and acc
    if (err) {
        printf("FOC error 1: %d\n", err);
        return 1;
    }
    err = write_register(REG_CMD, CMD_START_FOC);
    if (err) {
        printf("FOC enable error 3: %d\n", err);
        return 2;
    }
    HAL_Delay(250);
    err = write_register(REG_OFFSET_6, 0xC0); // enable foc for gyro and acc
    if (err) {
        printf("FOC enable error 4: %d\n", err);
        return 3;
    }
    return 0;
}

uint8_t read_acc_x(int16_t *value) {
    uint8_t temp;
    read_register(REG_ACC_X_0, &temp); // acc_x register part 1
    *value = temp;
    read_register(REG_ACC_X_1, &temp); // acc_x register part 2
    *value = (*value) | (temp << 8);
    return 0;
}

uint8_t read_acc_y(int16_t *value) {
    uint8_t temp;
    read_register(REG_ACC_Y_0, &temp); // acc_y register part 1
    *value = temp;
    read_register(REG_ACC_Y_1, &temp); // acc_y register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_acc_z(int16_t *value) {
    uint8_t temp;
    read_register(REG_ACC_Z_0, &temp); // acc_z register part 1
    *value = temp;
    read_register(REG_ACC_Z_1, &temp); // acc_z register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_gyro_x(int16_t *value) {
    uint8_t temp;
    read_register(REG_GYRO_X_0, &temp); // gyro_x register part 1
    *value = temp;
    read_register(REG_GYRO_X_1, &temp); // gyro_x register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_gyro_y(int16_t *value) {
    uint8_t temp;
    read_register(REG_GYRO_Y_0, &temp); // gyro_y register part 1
    *value = temp;
    read_register(REG_GYRO_Y_1, &temp); // gyro_y register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_gyro_z(int16_t *value) {
    uint8_t temp;
    read_register(REG_GYRO_Z_0, &temp); // gyro_z register part 1
    *value = temp;
    read_register(REG_GYRO_Z_1, &temp); // gyro_z register part 2
    *value = (*value) | (temp << 8);
    return 0;
}

uint8_t read_mag_x(int16_t *value) {
    uint8_t temp;
    read_register(REG_MAG_X_0, &temp); // mag_x register part 1
    *value = temp;
    read_register(REG_MAG_X_1, &temp); // mag_x register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_mag_y(int16_t *value) {
    uint8_t temp;
    read_register(REG_MAG_Y_0, &temp); // mag_y register part 1
    *value = temp;
    read_register(REG_MAG_Y_1, &temp); // mag_y register part 2
    *value = (*value) | (temp << 8);
    return 0;
}
uint8_t read_mag_z(int16_t *value) {
    uint8_t temp;
    read_register(REG_MAG_Z_0, &temp); // mag_z register part 1
    *value = temp;
    read_register(REG_MAG_Z_1, &temp); // mag_z register part 2
    *value = (*value) | (temp << 8);
    return 0;
}

uint8_t configure_bump_interrupt() {
    uint8_t err;
    uint8_t prev_value;
    // Read previous value from interrupt enable register
    err = read_register(REG_INT_EN_1, &prev_value);
    if (err) {
        printf("Bump interrupt init error 1: %d\n", err);
        return 1;
    }
    // Write new value with high G interrupt enabled
    err = write_register(REG_INT_EN_1, INT_HIGH_G_EN_Z | prev_value);
    if (err) {
        printf("Bump interrupt init error 2: %d\n", err);
        return 2;
    }
    // Read previous value from interrupt map register
    err = read_register(REG_INT_MAP_2, &prev_value);
    if (err) {
        printf("Slope interrupt enable error 3: %d\n", err);
        return 1;
    }
    // High G (bump) detection to INT 2
    err = write_register(REG_INT_MAP_2, (0x01 << 1) | prev_value);
    if (err) {
        printf("Interrupt 2 map error: %d\n", err);
        return 4;
    }
    // Threshold
    err = write_register(REG_INT_LOWHIGH_4, 158);
    if (err) {
        printf("Slope interrupt enable error 5: %d\n", err);
        return 4;
    }
    // Duration
    err = write_register(REG_INT_LOWHIGH_3, 19);
    if (err) {
        printf("Slope interrupt enable error 6: %d\n", err);
        return 4;
    }
    return 0;
}

uint8_t configure_slope_interrupt() {
    uint8_t err;
    uint8_t prev_value;
    // Read previous value from interrupt enable register
    err = read_register(REG_INT_EN_0, &prev_value);
    if (err) {
        printf("Slope interrupt enable error 1: %d\n", err);
        return 1;
    }
    // Write new value with flat interrupt enabled
    err = write_register(REG_INT_EN_0, INT_FLAT | prev_value);
    if (err) {
        printf("Slope interrupt enable error 2: %d\n", err);
        return 2;
    }
    // Read previous value from interrupt map register
    err = read_register(REG_INT_MAP_2, &prev_value);
    if (err) {
        printf("Slope interrupt enable error 3: %d\n", err);
        return 2;
    }
    // Flat (slope) detection to INT 2
    err = write_register(REG_INT_MAP_2, (0x01 << 7) | prev_value);
    if (err) {
        printf("Slope interrupt enable error 4: %d\n", err);
        return 4;
    }
    // Angle
    err = write_register(REG_INT_FLAT_0, 1);
    if (err) {
        printf("Slope interrupt enable error 5: %d\n", err);
        return 5;
    }
    // // Hold time and hysteresis
    // err = write_register(REG_INT_FLAT_1, 0x21); // (3 < 4) | 
    // if (err) {
    //     printf("Slope interrupt enable error 6: %d\n", err);
    //     return 6;
    // }
    return 0;
}

uint8_t configure_data_ready_interrupt() {
    uint8_t err;
    uint8_t prev_value;
    // Read previous value from interrupt enable register
    err = read_register(REG_INT_EN_1, &prev_value);
    if (err) {
        printf("Data ready interrupt enable error 1: %d\n", err);
        return 1;
    }
    // Write new value with data ready interrupt enabled
    err = write_register(REG_INT_EN_1, INT_DATA_READY | prev_value);
    if (err) {
        printf("Data ready interrupt enable error 2: %d\n", err);
        return 2;
    }
    // Read previous value from interrupt map register
    err = read_register(REG_INT_MAP_1, &prev_value);
    if (err) {
        printf("Data ready interrupt enable error 3: %d\n", err);
        return 1;
    }
    // Data ready detection to INT 1
    err = write_register(REG_INT_MAP_1, (0x01 << 7) | prev_value);
    if (err) {
        printf("Data ready interrupt enable error 4: %d\n", err);
        return 3;
    }
    return 0;
}

uint8_t configure_interrupt_pins() {
    uint8_t err;
    err = write_register(REG_INT_CTRL, 0xBB); // 1011 (int enabled, push-pull, active high, edge) for both pins
    if (err) {
        printf("Interrupt ctrl error: %d\n", err);
        return 1;
    }
    err = write_register(REG_INT_LATCH, 0x33); // 0011 0011 (enable INT 2 and INT 1, 1.25ms duration)
    if (err) {
        printf("Interrupt latch error: %d\n", err);
        return 2;
    }
    return 0;
}

uint8_t write_register(uint8_t reg, uint8_t value) {
    uint8_t err;
    uint8_t tx_buffer[] = {reg, value};
    err = HAL_I2C_Master_Transmit(&hi2c3, IMU_ADDR << 1, tx_buffer, 2, 1000);
    if (err) {
        printf("Write reg error 1: %d\n", err);
        return 1;
    }
    return 0;
}

uint8_t read_register(uint8_t reg, uint8_t *value) {
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
    *value = rx_buffer[0];
    return 0;
}

uint8_t print_register(uint8_t reg) {
    uint8_t val;
    read_register(reg, &val);
    printf("REG %x: %x\n", reg, val);
    return 0;
}
