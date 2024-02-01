#include <stdio.h>

uint8_t send_message(char *msg);
uint8_t read_message(uint8_t *msg, uint16_t len);
uint8_t enable_wifi();
uint8_t open_socket();
uint8_t reset_esp();