#include "Reg.h"
#include "Types.h"
#include "PLL.h"

void PLL_Init(void)
{
	RCC2 |= USERCC2;  //use rcc2 reg
	RCC2 |= BYPASS;  //use output of ocillator
	RCC2 &= ~0x00000070 ;//use main ocillator
	RCC2 &= ~PLLNormal; //pll operate in normal mode
	RCC2 |= NoDiv; //do not divide by 2

}
void PLL_SetClock(uint32 clock)
{
	RCC &= ~XTAL;
	RCC  |= PLL_16MHZ;
	RCC2 |= (RCC2&~ 0x1FC00000) + (4 << 22);
	  while((RIS & PLLIRS)==0);   //wait until pll is stable
	  RCC2&= ~BYPASS; //clear bypass to let the pll operate

}
void PLL_Set80(void)
{
	  RCC2 |= 0x80000000;
	  RCC2 |= 0x00000800;
	  RCC &= ~0x000007C0;
	  RCC += 0x00000540;
	  RCC2 &= ~0x00000070;
	  RCC2 += 0x00000000;
	  RCC2 &= ~0x00002000;
	  RCC2 |= 0x40000000;
	  RCC2 = (RCC2&~0x1FC00000)
	                  + (4<<22);
	  while((RIS&0x00000040)==0){};
	  RCC2 &= ~0x00000800;
}
// 4 -> 80
// 5-> 66.6
// 6 -> 57.14
// 7 ->

