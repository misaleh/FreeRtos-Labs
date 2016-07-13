#include "Reg.h"
#include "DIO.h"
#include "Types.h"
#include "PLL.h"
#include "UART.h"
/* FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#define SWITCHTASKSTACKSIZE        256


TimerHandle_t Timer_Function1;
void MyTimer( TimerHandle_t Timer_Function1 )
{
	static u8 state = DIO_LOW;
	DIO_PortWrite(PortF,YELLOW,state);
	state ^= 0xFF;
}
void Task1(void* para)
{
	char in;
	uint32 period = 100; //initial timer period
	while(1)
	{
		in = UART0_ReadChr();  //not good if there is other tasks in system, use interrupt better
		UART0_SendChr(in);
		UART0_Println();
		if(in == 's')
		{
			xTimerStop( Timer_Function1 ,1000 );
		}
		else if(in == 'r' )
		{
			xTimerReset( Timer_Function1, 1000 );
		}
		else if(in == 'd' )
		{
			period = period * 2 ;
			xTimerChangePeriod( Timer_Function1, period, 1000 );
		}
		else if(in == 'i' )
		{
			period = period / 2 ;
			xTimerChangePeriod( Timer_Function1, period, 1000 );
		}

	}
}
int main(void) {
	PLL_Set80();
	UART0_Init(115200,80000000);
	DIO_PortInit(PortF,Pin1|Pin2|Pin3 , 0);
	DIO_PortDirection(PortF , Pin1|Pin2|Pin3, DIO_OUTPUT);
	TaskHandle_t  First_handle;
	Timer_Function1= xTimerCreate(  "MyTimer",100, pdTRUE,( void * ) 0, MyTimer);
    xTimerStart( Timer_Function1, 0 );
	xTaskCreate(Task1, "Task1",SWITCHTASKSTACKSIZE, NULL,1, &First_handle);
	vTaskStartScheduler();
	return 0;
}
