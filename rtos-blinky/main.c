#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "TM4C129.h"                    // Device header



void vPeriodicTask(void *pvParameters)
{
	//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
		// Establish the task's period.
		const TickType_t xDelay = pdMS_TO_TICKS(100);
		TickType_t xLastWakeTime = xTaskGetTickCount();

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Turn on the LED.
        //
        GPION->DATA |= 0x03;
        GPIOF_AHB->DATA |= (1 << 4) | (1 << 0);

        //
        // Delay for a bit.
        //
				vTaskDelayUntil(&xLastWakeTime, xDelay);
        //
        // Turn off the LED.
        //
        GPION->DATA &= ~(0x03);
        GPIOF_AHB->DATA &= ~((1 << 4) | (1 << 0));

        //
        // Delay for a bit.
        //
				vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}



int main()
{
	   //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL->RCGCGPIO = (1<<12) | (1<<5);

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPION->DIR = 0x03;
    GPION->DEN = 0x03;

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOF_AHB->DIR = (1 << 4) | (1 << 0);
    GPIOF_AHB->DEN = (1 << 4) | (1 << 0);
	GPION->DATA |= 0x03;
	xTaskCreate(vPeriodicTask, "My Task", 256, NULL, 1, NULL);

	// Startup of the FreeRTOS scheduler.  The program should block here.  
	vTaskStartScheduler();
	
	// The following line should never be reached.  Failure to allocate enough
	//	memory from the heap would be one reason.
	for (;;);
	
}
