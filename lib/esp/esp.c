#include "usart.h"
#include "esp.h"
#include "string.h"

uint8_t send_message(char *msg) {
    uint8_t err;
    err = HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
    if (err) {
        printf("UART1 TX ERR=%d\n", err);
    }
    // printf("> %s\n", msg);
    return err;
}

uint8_t read_message(uint8_t *msg, uint16_t len) {
    uint8_t err;
    uint16_t rxlen;
    for (int i=0; i<len; i++) {
        msg[i] = '\0';
    }
    err = HAL_UARTEx_ReceiveToIdle(&huart1, msg, len, &rxlen, 3000);
    if (err) {
        printf("UART1 RX ERR=%d\n", err);
    }
    printf("< %s\n", msg);
    return err;
}
