#include "GPIO.h"
#include "utils.h"

void GPIO_init(GPIOA_AHB_Type* port, uint32_t pin, GPIO_mode mode)
{
    uint32_t uport = (uint32_t)port;
    uint32_t indice_gpio = ((uport - GPIOA_AHB_BASE) >> 12);
    SET_BIT(SYSCTL->RCGCGPIO, indice_gpio);
    while(!(GET_BIT(SYSCTL->PRGPIO, indice_gpio)));
}


void GPIO_write(GPIOA_AHB_Type* port, uint32_t pin, uint8_t val)
{
    RESET_BIT(port->DATA, pin);
    port->DATA |= (val << pin);
}