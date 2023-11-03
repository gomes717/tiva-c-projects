#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>

// #define UART0 0
// #define UART1 1
// #define UART2 2
// #define UART3 3
// #define UART4 4
// #define UART5 5
// #define UART6 6
// #define UART7 7

void UART_init(const uint8_t id, const uint32_t baud, const uint8_t mode);
void UART_send(const uint8_t id, const uint8_t* buff, const uint32_t size);
int32_t UART_receive(const uint8_t id, uint8_t* buff);


#endif