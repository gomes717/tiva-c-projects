#include "../include/UART.h"
#include "TM4C129.h"
#include "utils.h"

#define MAX_BUFF_SIZE 256

typedef struct
{
    uint16_t head;
    uint16_t tail;
    uint8_t data[MAX_BUFF_SIZE];
} Buffer_t;


void UART_init(const uint8_t id, const uint32_t baud, const uint8_t mode)
{
    //FIXME: hardcoded for clock 16MHz and cfg 16 div
    //FIXME: Configuring only UART0
    uint16_t ibrd = 120000000/(16*baud);
    uint16_t fbrd = ((120000000%(16*baud))*64)/(16*baud);
    SET_BIT(SYSCTL->RCGCUART, 0);
	while(!GET_BIT(SYSCTL->PRUART, 0));
	RESET_BIT(UART0->CTL, 0);
	UART0->FBRD = fbrd;
	UART0->IBRD = ibrd;
	UART0->LCRH = mode;
	UART0->CC &= ~(15<<0);			 //zerar os 4 bits para pegar o clock do sistema
	UART0->CTL |= (1<<0);
	SYSCTL->RCGCGPIO |= (1<<0);
	while(!(GET_BIT(SYSCTL->PRGPIO, 0)));
	GPIOA_AHB->AMSEL &= ~(3<<0);
	GPIOA_AHB->PCTL |= (1<<4)|(1<<0);
	GPIOA_AHB->AFSEL |= (3<<0);
	GPIOA_AHB->DEN |= (3<<0);
	UART0->DR = 0;
}

void UART_send(const uint8_t id, const uint8_t* buff, const uint32_t size)
{
    int i;
	for(i = 0; i < size; i++){
		while((UART0->FR&(1<<5)));
		UART0->DR = buff[i];
	}
}

int32_t UART_receive(const uint8_t id, uint8_t* buff)
{
    return 0;
}
