#include "Reg.h"
#include "DIO.h"
#include "Types.h"
#include "PLL.h"
#include "UART.h"
/* FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"

#define SWITCHTASKSTACKSIZE        128

uint32 x = 0 , y = 0;
volatile uint32 data = 0;

void Task2(void * para)
{

	while(1)
	{

		if(x != y)
		{
			UART0_SendString("Shared data problem :3");
			UART0_Println();
		}
		vTaskDelay(47);
	}

}
void Task1(void * para)
{
	while(1)
	{
		taskENTER_CRITICAL();
		 x ++;
		 //shared data problem happens here
		 y ++;
		  taskEXIT_CRITICAL();
	}
}

int main(void) {
	PLL_Set80();
	UART0_Init(115200,80000000);
	DIO_PortInit(PortF, Pin0|Pin1|Pin2|Pin3|Pin4 , Pin0|Pin4);
	DIO_PortDirection(PortF , Pin1|Pin2|Pin3, DIO_OUTPUT);
	DIO_PortDirection(PortF , Pin0|Pin4, DIO_INPUT);
	TaskHandle_t  First_handle,Second_handle;
	xTaskCreate(Task1, "Task1",SWITCHTASKSTACKSIZE, NULL,1, &First_handle);
	xTaskCreate(Task2, "Task2",SWITCHTASKSTACKSIZE, NULL,2, &Second_handle);
	vTaskStartScheduler();
	return 0;
}
