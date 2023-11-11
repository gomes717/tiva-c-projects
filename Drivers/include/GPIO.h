#ifndef __GPIO_H__
#define __GPIO_H__

#include "TM4C129.h"

typedef enum
{
    OUTPUT = 0,
    INPUT,
    UART_MODE
} GPIO_mode;

#define HIGH 1
#define LOW 0

void GPIO_init(GPIOA_AHB_Type* port, uint32_t pin, GPIO_mode mode);
void GPIO_write(GPIOA_AHB_Type* port, uint32_t pin, uint8_t val);
uint8_t GPIO_read(GPIOA_AHB_Type* port, uint32_t pin);

#endif