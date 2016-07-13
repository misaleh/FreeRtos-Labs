#include "Reg.h"
#include "DIO.h"
#include "Types.h"
void DIO_PortInit(uint32 port, uint32 pins, uint32 Pullup) /*mask specifies pins used */
{
	volatile unsigned long int delay;
	switch(port)
	{
	case PortA:
		 /*to waste from 3 to 5 cylces to make the system stable  */
		SYSCTL_RCGC2_R |= 0x0000001;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTA_CR_R |= pins;           // allow changes
		GPIO_PORTA_AMSEL_R &= ~pins;        // disable analog
		GPIO_PORTA_PCTL_R &= ~pins;   //
		GPIO_PORTA_AFSEL_R &= ~pins;        //  disable alt funct
		GPIO_PORTA_PUR_R |= Pullup;          //  pull-up
		GPIO_PORTA_DEN_R |= pins;          // enable digital I/O
		break;

	case PortB:
		SYSCTL_RCGC2_R |= 0x0000002;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTB_CR_R |= pins;
		GPIO_PORTB_AMSEL_R &= ~pins;
		GPIO_PORTB_PCTL_R &= ~pins;
		GPIO_PORTB_AFSEL_R &= ~ pins;
		GPIO_PORTB_PUR_R |= Pullup;
		GPIO_PORTB_DEN_R |= pins;
		break;

	case PortC:
		SYSCTL_RCGC2_R |= 0x0000004;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTC_LOCK_R = 0x4C4F434B;
		GPIO_PORTC_CR_R |= pins;
		GPIO_PORTC_AMSEL_R &= ~pins;
		GPIO_PORTC_PCTL_R &= ~pins;
		GPIO_PORTC_AFSEL_R &= ~pins;
		GPIO_PORTC_PUR_R |= Pullup;
		GPIO_PORTC_DEN_R |= pins;
		break;

	case PortD:
		SYSCTL_RCGC2_R |= 0x0000008;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTD_LOCK_R = 0x4C4F434B;
		GPIO_PORTD_CR_R |= pins;
		GPIO_PORTD_AMSEL_R &= ~pins;
		GPIO_PORTD_PCTL_R &= ~pins;
		GPIO_PORTD_AFSEL_R &= ~pins;
		GPIO_PORTD_PUR_R |= Pullup;
		GPIO_PORTD_DEN_R |= pins;
		break;

	case PortE:
		SYSCTL_RCGC2_R |= 0x0000010;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTE_CR_R |= pins;
		GPIO_PORTE_AMSEL_R &= ~pins;
		GPIO_PORTE_PCTL_R &= ~pins;
		GPIO_PORTE_AFSEL_R &= ~pins;
		GPIO_PORTE_PUR_R |= Pullup;
		GPIO_PORTE_DEN_R |= pins;
		break;

	case PortF:
		SYSCTL_RCGC2_R |= 0x00000020;
		delay = SYSCTL_RCGC2_R;
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R |= pins;
		GPIO_PORTF_AMSEL_R &= ~pins;
		GPIO_PORTF_PCTL_R &= ~pins;
		GPIO_PORTF_AFSEL_R &= ~pins;
		GPIO_PORTF_PUR_R |= Pullup;
		GPIO_PORTF_DEN_R |= pins;
		break;
	}


}
void DIO_PortRead(uint32 port , uint32 mask, puint32 data)
{
	switch (port)
		{
		case PortA:
			*data = GET_REG(GPIO_PORTA_DATA_R,mask);
			break;

		case PortB:
			*data =GET_REG(GPIO_PORTB_DATA_R,mask);
			break;

		case PortC:
			*data =GET_REG(GPIO_PORTC_DATA_R,mask);
			break;

		case PortD:
			*data =GET_REG(GPIO_PORTD_DATA_R,mask);
			break;

		case PortE:
			*data =GET_REG(GPIO_PORTE_DATA_R,mask);
			break;

		case PortF:
			*data = GET_REG(GPIO_PORTF_DATA_R,mask);
			break;
		}


}
void DIO_PortWrite(uint32 port, uint32 mask, uint32 value)
{
	switch (port)
	{
	case PortA:
		SET_REG(GPIO_PORTA_DATA_R,value,mask);
		break;

	case PortB:
		SET_REG(GPIO_PORTB_DATA_R,value,mask);
		break;

	case PortC:
		SET_REG(GPIO_PORTC_DATA_R,value,mask);
		break;

	case PortD:
		SET_REG(GPIO_PORTD_DATA_R,value,mask);
		break;

	case PortE:
		SET_REG(GPIO_PORTE_DATA_R,value,mask);
		break;

	case PortF:
		SET_REG(GPIO_PORTF_DATA_R,value,mask);
		break;
	}
}
void DIO_PortDirection(uint32 port, uint32 mask, uint32 value)
{
	switch (port)
	{
	case PortA:
		SET_REG(GPIO_PORTA_DIR_R,value,mask);
		break;

	case PortB:
		SET_REG(GPIO_PORTB_DIR_R,value,mask);
		break;

	case PortC:
		SET_REG(GPIO_PORTC_DIR_R,value,mask);
		break;

	case PortD:
		SET_REG(GPIO_PORTD_DIR_R,value,mask);
		break;

	case PortE:
		SET_REG(GPIO_PORTE_DIR_R,value,mask);
		break;

	case PortF:
		SET_REG(GPIO_PORTF_DIR_R,value,mask);
		break;
}


}
