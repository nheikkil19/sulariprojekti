#include "usart.h"
#include "esp.h"
#include "string.h"
#include "cmsis_os2.h"

uint8_t send_message(char *msg) {
    uint8_t err;
    err = HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
    if (err) {
        printf("UART1 TX ERR=%d\n", err);
    }
    // printf("SENT: %s\n", msg);
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

uint8_t enable_wifi() {
    // Init wifi driver
    send_message("AT+CWINIT=1\r\n");
    osDelay(1000);
    // Select softAP mode
    send_message("AT+CWMODE=2\r\n");
    osDelay(1000);
    // Set AP name, password, channel, no encryption, max connections, not hidden
    send_message("AT+CWSAP=\"esp32\",\"password\",1,0,3,0\r\n");
    osDelay(1000);
    // Use DHCP
    send_message("AT+CWDHCP=1,1\r\n");
    osDelay(1000);
    return 0;
}

uint8_t open_socket() {
    // Enable multiple connections
    send_message("AT+CIPMUX=1\r\n");
    osDelay(1000);
    // Start TCP server with default port (333)
    send_message("AT+CIPSERVER=1\r\n");
    osDelay(1000);
    return 0;
}

uint8_t reset_esp() {
    send_message("AT+RST\r\n");
    osDelay(2000);
    return 0;
}

uint8_t send_tcp_message(char * msg) {
    uint16_t len = strlen(msg);
    char cipsend[20];
    sprintf(cipsend, "AT+CIPSEND=0,%d\r\n", len);
    send_message(cipsend);
    osDelay(50);
    send_message(msg);
    return 0;
}