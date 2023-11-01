#include "../include/LED.h"
#include "../include/utils.h"
#include "TM4C129.h"

typedef struct 
{
    GPIOA_AHB_Type* port;
    uint8_t pos_port;
} LED;

const LED leds[4] = {
                {.port=GPION, .pos_port=1},
                {.port=GPION, .pos_port=0},
                {.port=GPIOF_AHB, .pos_port=4},
                {.port=GPIOF_AHB, .pos_port=0},
            };

void LED_init(const uint8_t id)
{
    uint32_t port = (uint32_t)leds[id].port;
    uint32_t indice_gpio = ((port - GPIOA_AHB_BASE) >> 12);
    SET_BIT(SYSCTL->RCGCGPIO, indice_gpio);
    SET_BIT(leds[id].port->DIR, leds[id].pos_port);
    SET_BIT(leds[id].port->DEN, leds[id].pos_port);
}

void LED_TurnOn(const uint8_t id)
{
    SET_BIT(leds[id].port->DATA, leds[id].pos_port);
}

void LED_TurnOff(const uint8_t id) 
{
    RESET_BIT(leds[id].port->DATA, leds[id].pos_port);
}