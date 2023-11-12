#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "TM4C129.h"                    // Device header
#include "LED.h"
#include "UART.h"
#include "PLL.h"
#include "SPI.h"


void Led1Task(void *pvParameters)
{
	(void)pvParameters;
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(100);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		LED_TurnOn(LED1);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		LED_TurnOff(LED1);

		vTaskDelayUntil(&xLastWakeTime, xDelay);
		uint16_t data[9] = {0xFFFF, 1, 2, 3, 4, 5, 6, 7, 8};
		SPI_send(SPI_0, data, sizeof(data)/sizeof(uint16_t));
	}
}

void Led2Task(void *pvParameters)
{
	(void)pvParameters;
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(200);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		LED_TurnOn(LED2);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		LED_TurnOff(LED2);

		vTaskDelayUntil(&xLastWakeTime, xDelay);
		UART_send(UART_4, (uint8_t*)"\n\rUART4\n\r", 10);
	}
}

void Led3Task(void *pvParameters)
{
	(void)pvParameters;
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(400);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		LED_TurnOn(LED3);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		LED_TurnOff(LED3);

		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}

void Led4Task(void *pvParameters)
{
	(void)pvParameters;
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(800);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		LED_TurnOn(LED4);

		vTaskDelayUntil(&xLastWakeTime, xDelay);

		LED_TurnOff(LED4);

		vTaskDelayUntil(&xLastWakeTime, xDelay);
		UART_send(UART_0, (uint8_t*)"\n\rTeste\n\r", 7);
	}
}



int main()
{
	PLL_init(80000000, MOSCSRC);
	LED_init(LED1);
	LED_init(LED2);
	LED_init(LED3);
	LED_init(LED4);
	UART_init(UART_0, 115200, MODE_8);
	UART_init(UART_4, 115200, MODE_8);
	SPI_init(SPI_0,MASTER_MODE, 10000000);

	BaseType_t return_task;

	return_task = xTaskCreate(Led1Task, "LED 1", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		LED_TurnOn(LED1);
	}

	return_task = xTaskCreate(Led2Task, "LED 2", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		LED_TurnOn(LED2);
	}

	return_task = xTaskCreate(Led3Task, "LED 3", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		LED_TurnOn(LED3);
	}

	return_task = xTaskCreate(Led4Task, "LED 4", 256, NULL, 1, NULL);
	if(return_task == pdPASS)
	{
		LED_TurnOn(LED4);
	}

	// Startup of the FreeRTOS scheduler.  The program should block here.
	vTaskStartScheduler();
	// The following line should never be reached.  Failure to allocate enough
	//	memory from the heap would be one reason.
	for (;;);

}
