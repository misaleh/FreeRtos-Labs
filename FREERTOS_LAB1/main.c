#include "Reg.h"
#include "DIO.h"
#include "Types.h"
#include "PLL.h"
/* FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"
#define SWITCHTASKSTACKSIZE        128

void LED1(void *pvParameters)
{
	while(1)
	{
		DIO_PortWrite(PortF,CYAN,DIO_HIGH);
		vTaskDelay( 100 );
		DIO_PortWrite(PortF,CYAN,DIO_LOW);
		vTaskDelay( 100 );

	}

}
void LED2(void *pvParameters)
{
	u8 state = DIO_LOW;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		DIO_PortWrite(PortB,Pin0,state);
		state ^= 0xFF;
		vTaskDelayUntil( &xLastWakeTime, 1000);

	}
}
int main(void) {
	PLL_Set80();
	DIO_PortInit(PortF,Pin1|Pin2|Pin3, 0);
	DIO_PortDirection(PortF , Pin1|Pin2|Pin3, DIO_OUTPUT);
	DIO_PortInit(PortB, Pin0 , 0);
	DIO_PortDirection(PortB , Pin0, DIO_OUTPUT);
	TaskHandle_t  First_handle,Second_handle;
	xTaskCreate(LED1, "LED1",SWITCHTASKSTACKSIZE, NULL,1, &First_handle);
	xTaskCreate(LED2, "LED2",SWITCHTASKSTACKSIZE, NULL,2, &Second_handle);
    vTaskStartScheduler();
    while(1)
    {


    }
	return 0;
}
