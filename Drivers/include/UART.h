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

#define MODE_8  (0x3<<5)
#define MODE_7  (0x2<<5)
#define MODE_6  (0x1<<5)
#define MODE_5  (0x0<<5)
#define MODE_O  (0x1<<1)        // Odd Parity
#define MODE_E  (0x3<<1)        // Even Parity
#define MODE_S2 (0x1<<3)        // 2-bits stop
#define FIFO_ON (0x1<<4)


void UART_init(const uint8_t id, const uint32_t baud, const uint8_t mode);
void UART_send(const uint8_t id, const uint8_t* buff, const uint32_t size);
int32_t UART_receive(const uint8_t id, uint8_t* buff);


#endif