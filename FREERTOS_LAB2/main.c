#include "Reg.h"
#include "DIO.h"
#include "Types.h"
#include "PLL.h"
#include "UART.h"
/* FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"

#define SWITCHTASKSTACKSIZE        128
struct Two_handle{
	TaskHandle_t first_task;
	TaskHandle_t second_task;
}handles;

u8 speed = 1; /*shared global variable !!, may cause problems (not our scope in this lab)
Probably the worst way ever to share data*/
volatile uint32 data = 0;

void button(void * para)
{

	u8 flag_low = Pin0 ; //to work on falling edge
	while(1)
	{
		DIO_PortRead(PortF,Pin0,&data);
		if((data == DIO_LOW) && (flag_low == Pin0)) //active low , if button is pressed , and last time was high
		{
			speed += 2 ;
			speed = (speed > 10) ? 1 :speed;
		}
		flag_low = data;
		vTaskDelay(25); //ever 25 tick, as 25 ms
	}

}
void led(void * para)
{

	u8 state = DIO_LOW;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime, 100*speed);
		DIO_PortWrite(PortF,CYAN,state);
		state ^= 0xFF;
	}
}
void TaskState(void *para)
{
	TaskHandle_t state1 =  ((struct Two_handle *)para)->first_task; //task 1 handle
	TaskHandle_t state2 =  ((struct Two_handle *)para)->second_task; //task 2 handle
	TaskStatus_t Details1,Details2; // 2 structs for task1 and 2
	TaskStatus_t *pxTaskStatusArray;
	volatile UBaseType_t number,x;
	unsigned long ulTotalRunTime;
	number =uxTaskGetNumberOfTasks();
	pxTaskStatusArray = pvPortMalloc( number * sizeof( TaskStatus_t ) );
	uxTaskGetSystemState( pxTaskStatusArray,number,&ulTotalRunTime );
    UART0_SendString("Number of tasks = ");
    UART0_SendInt(number);
    UART0_Println();
	for(x = 0 ; x < number ; x ++ )   //To print tasks names
	{
		UART0_SendString(pxTaskStatusArray[x].pcTaskName);
	    UART0_Println();
	}

	while(1)
	{
		vTaskGetInfo(state1,&Details1, pdTRUE,eInvalid );
		vTaskGetInfo(state2,&Details2, pdTRUE,eInvalid );
	    UART0_SendString(Details1.pcTaskName);
	    UART0_Println();
	    UART0_SendInt(Details1.eCurrentState);
	    UART0_Println();
	    UART0_SendString(Details2.pcTaskName);
	    UART0_Println();
	    UART0_SendInt(Details2.eCurrentState);
	    UART0_Println();
		vTaskDelay(1000); //1 second
	}
}

 int main(void) {
	PLL_Set80();
	UART0_Init(115200,80000000);
	DIO_PortInit(PortF, Pin0|Pin1|Pin2|Pin3|Pin4 , Pin0|Pin4);
	DIO_PortDirection(PortF , Pin1|Pin2|Pin3, DIO_OUTPUT);
	DIO_PortDirection(PortF , Pin0|Pin4, DIO_INPUT);


	TaskHandle_t  First_handle,Second_handle,Third_handle;
	xTaskCreate(led, "LED",SWITCHTASKSTACKSIZE, NULL,1, &First_handle);
	xTaskCreate(button, "Button",SWITCHTASKSTACKSIZE, NULL,2, &Second_handle);
	handles.first_task = First_handle;
	handles.second_task = Second_handle;
	xTaskCreate(TaskState, "Statistics",SWITCHTASKSTACKSIZE, (void * )(&handles),3, &Third_handle);

	vTaskStartScheduler();
	return 0;
}
