#include "UART.h"
#include "Reg.h"
#include "Types.h"
void UART0_Init(int baud_rate,int clock)
{
	  float temp;
	  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; //enable uart
	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; //enable clock to the GPIO
	  GPIO_PORTA_AFSEL_R |= 0x03;          //alternative
	  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;

	  UART0_CTL_R &= ~UART_CTL_UARTEN;
	 // O = (clock / 16 br)
	  temp = (clock/(float)(16*baud_rate)) - (int)(clock/(16*baud_rate));
	  UART0_IBRD_R =    (int)(clock/(16*baud_rate));;            //  = int(O)

	  UART0_FBRD_R =    (int)(64 * temp + 0.5);;               // =int((decimal)*64 + 0.5)
	                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
	  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
	  UART0_CTL_R |= UART_CTL_UARTEN;

	  GPIO_PORTA_DEN_R |= 0x03;
	  GPIO_PORTA_AMSEL_R &= ~0x03;
}
void UART0_SendString(char * str)
{
	uint32 i = 0 ;
 	 while(str[i] != 0)
 		UART0_SendChr(str[i++]);
}
/*it does not send the integer as it is
 * it convertes the integer to equivlalent chars
 * send each data
 * this is not usefuk for serial communication
 * used for debugging purpose to print on screen
 */
void UART0_SendInt(int out)
{
	char c[10] = {0} ;
	char m;
	int32 i = 0 ;

	if(out == 0)
	{
		c[0] = 48;
		i = 0 ;
	}
	while(out)
	{
		m = (char)(out%10);
		c[i++] = m + 48;
		out = out/10;
	}
	//c[i] = 48 ;
	while(i != -1)
	{
		UART0_SendChr(c[i--]);
	}

}

void UART0_SendChr(char chr)
{
	  while((UART0_FR_R&UART_FR_TXFF) != 0);
	  UART0_DR_R = chr;
}

char UART0_ReadChr(void)
{
	  while((UART0_FR_R&UART_FR_RXFE) != 0);
	  return((char)(UART0_DR_R&0xFF));
}
void UART0_ReadString(char* str)
{
	char c =1;
	int32 i = 0;
	while(c != (char)TERMINATE_STRING)
	{
		c = UART0_ReadChr();
		str[i++] = c;
	}
	str[i] = 0 ;
}
