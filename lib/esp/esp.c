#include "usart.h"
#include "esp.h"

uint8_t send_message(uint8_t *msg) {
    uint8_t err;
    err = HAL_UART_Transmit(&huart1, msg, strlen(msg), 100);
    if (err) {
        printf("UART1 TX ERR=%d\n", err);
    }
    return err;
}

uint8_t read_message(uint8_t *msg, uint16_t len) {
    uint8_t err;
    for (int i=0; i<len; i++) {
        msg[i] = '\0';
    }
    err = HAL_UART_Receive(&huart1, msg, len, 5000);
    if (err) {
        printf("UART1 RX ERR=%d\n", err);
    }
    printf("%s", msg);
    return err;
}
