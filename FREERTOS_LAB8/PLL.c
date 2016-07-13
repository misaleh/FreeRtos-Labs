#include "Reg.h"
#include "Types.h"
#include "PLL.h"


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
