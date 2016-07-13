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
#define SWITCHTASKSTACKSIZE        256
#define Water_condition (H_count >= 2) && (O_count >= 1)


SemaphoreHandle_t Mutex1;
volatile u8 data1 = 0,data2 = 0 ;
static  char  O_count, H_count  ;


void O_TASK(void * para)
{
	Mutex1 = xSemaphoreCreateMutex();

		u8 flag_low = Pin4 ; //to work on falling edge
			while(1)
			{
				DIO_PortRead(PortF,Pin4,&data2);
				xSemaphoreTake(Mutex1,(TickType_t)portMAX_DELAY);
				if((data2 == DIO_LOW) && (flag_low == Pin4)) //active low , if button is pressed , and last time was high
				{
					O_count++;
					UART0_SendString("O is pressed!");
					UART0_SendInt(O_count);
					UART0_Println();
				}
				while(Water_condition)
				{
					H_count -= 2;
					O_count --;
					UART0_SendString("Water YAAAAAY!! Remaning H = ");
					UART0_SendInt(H_count);
					UART0_SendString(" O  =  ");
					UART0_SendInt(O_count);

					UART0_Println();
				}
				flag_low = data2;
				xSemaphoreGive(Mutex1);
				vTaskDelay(1);
			}
}

void H_TASK(void * para)
{

		u8 flag_low = Pin0 ; //to work on falling edge
			while(1)
			{
				DIO_PortRead(PortF,Pin0,&data1);
				xSemaphoreTake(Mutex1,(TickType_t)portMAX_DELAY);
				if((data1 == DIO_LOW) && (flag_low == Pin0)) //active low , if button is pressed , and last time was high
				{
					H_count++;

					UART0_SendString("H is pressed!");
					UART0_SendInt(H_count);
					UART0_Println();

				}
				while(Water_condition)
				{
					H_count -= 2;
					O_count --;
					UART0_SendString("Water YAAAAAY!! Remaning H = ");
					UART0_SendInt(H_count);
					UART0_SendString(" O  =  ");
					UART0_SendInt(O_count);
					UART0_Println();
				}
				flag_low = data1;
				xSemaphoreGive(Mutex1);
				vTaskDelay(1);
			}
}

int main(void) {
	O_count = 0 ;
	H_count =  0 ;
	PLL_Set80();
	UART0_Init(115200,80000000);
	DIO_PortInit(PortF, Pin0|Pin1|Pin2|Pin3|Pin4 , Pin0|Pin4);
	DIO_PortDirection(PortF , Pin1|Pin2|Pin3, DIO_OUTPUT);
	DIO_PortDirection(PortF , Pin0|Pin4, DIO_INPUT);
	TaskHandle_t  First_handle,Second_handle;
	xTaskCreate(O_TASK, "O_TASK",SWITCHTASKSTACKSIZE, NULL,2, &First_handle);
	xTaskCreate(H_TASK, "H_TASK",SWITCHTASKSTACKSIZE, NULL,1, &Second_handle);
	vTaskStartScheduler();
	return 0;
}
